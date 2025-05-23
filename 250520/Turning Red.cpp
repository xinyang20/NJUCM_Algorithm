// encoding:utf-8

#include <bits/stdc++.h>

const int INF = 1e9;

struct LightInfo {
	int initial_color; // 0 : R | 1 : G | 2 : B
	std::vector<int> buttons;
};

int l_lights, b_buttons;
std::vector<LightInfo> lights_global;
std::vector<std::vector<std::pair<int, int> > > button_adj_global;
std::vector<int> x_presses_global;
std::vector<bool> is_fixed_global;
std::vector<bool> visited_component_bfs_global;
std::vector<std::vector<int>> button_controls_lights_global;

std::map<char, int> color_to_int_global = {{'R', 0}, {'G', 1}, {'B', 2}};

void find(int start_node_idx, std::vector<int>& component_nodes_list) {
	std::queue<int> q;
	q.push(start_node_idx);
	visited_component_bfs_global[start_node_idx] = true;
	component_nodes_list.push_back(start_node_idx);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (auto& edge : button_adj_global[u]) {
			int v = edge.first;
			if (!is_fixed_global[v] && !visited_component_bfs_global[v]) {
				visited_component_bfs_global[v] = true;
				q.push(v);
				component_nodes_list.push_back(v);
			}
		}
	}
}

bool check(const std::vector<int>& current_x_config) {
	for (int i = 0; i < l_lights; ++i) {
		int current_light_color = lights_global[i].initial_color;
		if (lights_global[i].buttons.empty() && current_light_color != 0) return false;

		for (int button_idx : lights_global[i].buttons) {
			if (button_idx < 0 || button_idx >= b_buttons || current_x_config[button_idx] == -1) {
				return false;
			}
			current_light_color = (current_light_color + current_x_config[button_idx]) % 3;
		}
		if (current_light_color != 0) {
			return false;
		}
	}
	return true;
}


void solve() {
	std::cin >> l_lights >> b_buttons;

	lights_global.assign(l_lights, LightInfo());
	std::string initial_colors_str;
	std::cin >> initial_colors_str;
	for (int i = 0; i < l_lights; ++i) {
		lights_global[i].initial_color = color_to_int_global[initial_colors_str[i]];
	}

	button_adj_global.assign(b_buttons, std::vector<std::pair<int, int> >());
	button_controls_lights_global.assign(b_buttons, std::vector<int>());

	for (int i = 0; i < b_buttons; ++i) {
		int k_count;
		std::cin >> k_count;
		for (int j = 0; j < k_count; ++j) {
			int light_idx;
			std::cin >> light_idx;
			--light_idx; // 0-based
			lights_global[light_idx].buttons.push_back(i);
			button_controls_lights_global[i].push_back(light_idx);
		}
	}

	for (int i = 0; i < l_lights; ++i) {
		if (lights_global[i].buttons.size() == 2) {
			int b1 = lights_global[i].buttons[0];
			int b2 = lights_global[i].buttons[1];
			button_adj_global[b1].push_back(std::make_pair(b2, i));
			button_adj_global[b2].push_back(std::make_pair(b1, i));
		}
	}

	x_presses_global.assign(b_buttons, -1);
	is_fixed_global.assign(b_buttons, false);
	long long total_min_presses = 0;

	for (int i = 0; i < l_lights; ++i) {
		if (lights_global[i].buttons.size() == 1) {
			int button_idx = lights_global[i].buttons[0];
			int required_x = (3 - lights_global[i].initial_color % 3 + 3) % 3;
			if (x_presses_global[button_idx] == -1) {
				x_presses_global[button_idx] = required_x;
				is_fixed_global[button_idx] = true;
			} else if (x_presses_global[button_idx] != required_x) {
				std::cout << "impossible" << '\n';
				return;
			}
		} else if (lights_global[i].buttons.empty()) {
			if (lights_global[i].initial_color != 0) {
				std::cout << "impossible" << '\n';
				return;
			}
		}
	}

	visited_component_bfs_global.assign(b_buttons, false);

	for (int i = 0; i < b_buttons; ++i) {
		if (is_fixed_global[i] && !visited_component_bfs_global[i]) {
			std::queue<int> q_prop;
			q_prop.push(i);
			visited_component_bfs_global[i] = true;
			total_min_presses += x_presses_global[i];

			while (!q_prop.empty()) {
				int u = q_prop.front();
				q_prop.pop();

				for (auto& edge : button_adj_global[u]) {
					int v = edge.first;
					int light_idx = edge.second;

					if (is_fixed_global[v]) {
						if ((lights_global[light_idx].initial_color
						        + x_presses_global[u] + x_presses_global[v]) % 3 != 0) {
							std::cout << "impossible" << '\n'; return;
						}
					} else {
						x_presses_global[v] = (3 - (lights_global[light_idx].initial_color
						                            + x_presses_global[u]) % 3 + 3) % 3;
						is_fixed_global[v] = true;
						total_min_presses += x_presses_global[v];
						if (!visited_component_bfs_global[v]) {
							visited_component_bfs_global[v] = true;
							q_prop.push(v);
						}
					}
				}
			}
		} else if (!is_fixed_global[i] && !visited_component_bfs_global[i]) {
			std::vector<int> component_nodes_list;
			find(i, component_nodes_list);

			if (component_nodes_list.empty()) continue;

			long long current_best_comp_cost = -1;
			std::map<int, int> best_comp_values;

			int start_node = component_nodes_list[0];

			for (int try_x_start = 0; try_x_start < 3; ++try_x_start) {
				std::map<int, int> temp_x_values;
				temp_x_values[start_node] = try_x_start;
				long long current_trial_sum = try_x_start;
				bool possible_this_trial = true;

				std::queue<int> q_trial;
				q_trial.push(start_node);
				std::map<int, bool> visited_in_trial_bfs_map;
				visited_in_trial_bfs_map[start_node] = true;

				while (!q_trial.empty() && possible_this_trial) {
					int u_trial = q_trial.front();
					q_trial.pop();

					for (auto& edge : button_adj_global[u_trial]) {
						int v_trial = edge.first;
						int light_idx_trial = edge.second;

						if (is_fixed_global[v_trial]) {
							if ((lights_global[light_idx_trial].initial_color
							        + temp_x_values[u_trial] + x_presses_global[v_trial]) % 3 != 0) {
								possible_this_trial = false; break;
							}
						} else {
							bool v_in_current_component_nodes = false;
							for (int node_in_c : component_nodes_list)
								if (node_in_c == v_trial)
									v_in_current_component_nodes = true;

							if (!v_in_current_component_nodes) continue;

							if (temp_x_values.count(v_trial)) {
								if ((lights_global[light_idx_trial].initial_color
								        + temp_x_values[u_trial] + temp_x_values[v_trial]) % 3 != 0) {
									possible_this_trial = false; break;
								}
							} else {
								temp_x_values[v_trial] = (
								                             3 - (lights_global[light_idx_trial].initial_color
								                                  + temp_x_values[u_trial]) % 3 + 3) % 3;
								current_trial_sum += temp_x_values[v_trial];
								if (!visited_in_trial_bfs_map.count(v_trial)) {
									visited_in_trial_bfs_map[v_trial] = true;
									q_trial.push(v_trial);
								}
							}
						}
					}
				}

				if (possible_this_trial) {
					if (temp_x_values.size() != component_nodes_list.size()) {
						possible_this_trial = false;
					}
				}

				if (possible_this_trial) {
					for (int node_in_comp : component_nodes_list) {
						for (int l_idx : button_controls_lights_global[node_in_comp]) {
							int sum_effect_val = lights_global[l_idx].initial_color;
							bool verifiable_light = true;
							for (int btn_ctrl_l : lights_global[l_idx].buttons) {
								if (temp_x_values.count(btn_ctrl_l)) {
									sum_effect_val = (sum_effect_val + temp_x_values[btn_ctrl_l]) % 3;
								} else if (is_fixed_global[btn_ctrl_l]) {
									sum_effect_val = (sum_effect_val + x_presses_global[btn_ctrl_l]) % 3;
								} else {
									verifiable_light = false;
									break;
								}
							}

							if (!verifiable_light) {
								possible_this_trial = false;
								break;
							}
							if (sum_effect_val != 0) {
								possible_this_trial = false;
								break;
							}
						}
						if (!possible_this_trial) break;
					}
				}

				if (possible_this_trial) {
					if (current_best_comp_cost == -1 || current_trial_sum < current_best_comp_cost) {
						current_best_comp_cost = current_trial_sum;
						best_comp_values = temp_x_values;
					}
				}
			}

			if (current_best_comp_cost == -1) {
				std::cout << "impossible" << '\n';
				return;
			}
			total_min_presses += current_best_comp_cost;
			for (auto const& [node_idx, val] : best_comp_values) {
				x_presses_global[node_idx] = val;
				is_fixed_global[node_idx] = true;
			}
		}
	}


	if (!check(x_presses_global)) {
		std::cout << "impossible" << '\n';
		return;
	}

	std::cout << total_min_presses << '\n';
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int T;
	T = 1;
	// std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
