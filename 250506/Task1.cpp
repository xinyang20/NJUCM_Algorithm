// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <bits/stdc++.h>

#define endl '\n'

typedef long long ll;

struct cmp
{
	bool operator()(const std::pair<ll, ll>& a, const std::pair<ll, ll>& b) {
		return a.second > b.second;
	}
};

const int N = 1e5 + 3;
int map[N][N];
bool visited[N];
std::priority_queue <
std::pair<ll, ll>,
    std::vector<std::pair<ll, ll>>,
    cmp > q;
ll noden, edgen;
ll Min_cost = INT_MAX;
std::vector

void dfs(ll cur_cost, std::string path) {
	if (q.empty() && Min_cost > cur_cost) {
		Min_cost = cur_cost;
		ans = path;
		return;
	}

	if (cur_cost >= Min_cost)
		return;

	ll cur_p = path[path.length() - 1];
	for (int i = 1; i <= noden; i++) {
		if (!visited[i] && map[cur_p][i] != -1) {
			std::string add = "";
			add += (i + "0");
			visited[i] = true;
			dfs(cur_cost + map[cur_p][i], path + add);
			visited[i] = false;
		}
	}
}

void TSP() {
	for (int i = 1; i <= noden; i++)
		visited[i] = false;
	q.push(std::pair<ll, ll>(1, 0));
	std::string path = "1";
	dfs(0, path);

	std::cout << Min_cost << endl;
	if (path.length() != 0)
		std::cout << path[0];
	for (int i = 1; i < path.length(); i++)
		std::cout << "->" << path[i];
	std::cout << endl;
}

void TSP_back() {
	for (int i = 1; i <= noden; i++)
		visited[i] = false;
}

void solve() {
	for (int i = 1; i <= noden; i++)
		visited[i] = false;
	ll from, to, dist;
	for (int i = 0; i <= noden; i++)
		for (int j = 0; j <= noden; j++)
			map[i][j] = -1;

	for (int i = 0; i < edgen; i++) {
		std::cin >> from >> to >> dist;
		map[from][to] = dist;
		map[to][from] = dist;
	}

	TSP();
	TSP_back();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;
	T = 1;
	// cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

/*
Example Input
5 9
1 2 3
1 4 8
1 5 7
2 3 3
2 4 10
2 5 5
3 4 4
3 5 3
4 5 20

Example Output
23
1 4 3 5 2
*/