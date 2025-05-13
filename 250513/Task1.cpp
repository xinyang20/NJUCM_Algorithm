// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <bits/stdc++.h>

#define endl '\n'
#define paii std::pair<int,int>
#define pall std::pair<ll ,ll>
#define vpii std::vector<paii>
#define vll std::vector<ll>
#define vbool std::vector<bool>
#define qll std::queue<ll>
#define makep std::make_pair
#define get std::cin
#define put std::cout

typedef long long ll;

const ll N = 1e3 + 3;

ll graph[N][N];
ll n, a, b;
vll ans;
vbool visited;

void bfs(vll curr, qll nodes) {
	if (nodes.empty() && curr.size() > ans.size()) {
		ans = curr;
		return;
	}

	while (!nodes.empty()) {
		ll curr_node = nodes.front();
		nodes.pop();

		bool insert = true;
		for (ll i = 0; i < curr.size(); i++) {
			if (graph[curr_node][curr[i]] != 1) {
				insert = false;
				break;
			}
		}

		if (insert) {
			curr.push_back(curr_node);
			visited[curr_node] = true;
			qll new_nodes;
			for (ll i = 1; i <= n; i++)
				if (graph[curr_node][i] == 1 && !visited[i])
					new_nodes.push(i);
			bfs(curr, new_nodes);
			visited[curr_node] = false;
			curr.pop_back();
		}
	}
}

void solve() {
	get >> n;
	visited.assign(n + 3, false);
	for (ll i = 1; i <= n; i++)
		for (ll j = 1; j <= n; j++)
			graph[i][j] = 0;

	while (get >> a >> b) {
		if (a == 0 && b == 0)
			break;
		graph[a][b] = 1;
		graph[b][a] = 1;
	}

	vll curr;
	qll nodes;
	for (ll i = 1; i <= n; ++i)
		nodes.push(i);

	bfs(curr, nodes);

	for (ll i = 0; i < ans.size(); i++)
		put << ans[i] << "\t";
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int T;
	T = 1;
	// cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

/*
Example Input:
5
1 2
1 4
1 5
2 3
2 5
3 5
4 5
0 0

Example Output:
1 2 5（或1 4 5 或2 3 5）
*/