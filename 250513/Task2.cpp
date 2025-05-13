// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

// 问题描述：
// 布线问题就是在m*n的方格阵列中，指定一个方格的中点a,另一个方格的中点b,问题要求找出a到b的最短布线方案。
//	布线时只能沿直线或直角，不能走斜线。为了避免线路相交，已布过线的方格做了封锁标记(灰色)，其他线路不允许穿过被封锁的方格。

#include <bits/stdc++.h>

#define endl '\n'
#define paii std::pair<int,int>
#define pall std::pair<long long ,long long>
#define vpii std::vector<std::pair<int,int> >
#define vll std::vector<long long>
#define vll2 std::vector<std::vector<long long> >
#define vbool std::vector<bool>
#define vbool2 std::vector<std::vector<bool> >
#define qll std::queue<long long>
#define makep std::make_pair
#define get std::cin
#define put std::cout

typedef long long ll;

vll2 graph;
vbool2 visited;
ll r, c, n, x, y, sr, sc;
vpii ans;
const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};

void bfs(vpii curr_path) {
	pall curr_node = curr_path.back();
	ll curr_r = curr_node.first, curr_c = curr_node.second;
	if (graph[curr_r][curr_c] == 2 && (ans.empty() || ans.size() > curr_path.size())) {
		ans = curr_path;
		return;
	}

	for (int i = 0; i < 4; i++) {
		ll nxtr = curr_r + dr[i], nxtc = curr_c + dc[i];
		if (nxtr > 0 && nxtr <= r && nxtc > 0 && nxtc <= c && graph[nxtr][nxtc] != -1 && !visited[nxtr][nxtc]) {
			curr_path.push_back(makep(nxtr, nxtc));
			visited[nxtr][nxtc] = true;
			bfs(curr_path);
			visited[nxtr][nxtc] = false;
			curr_path.pop_back();
		}
	}
	if (!ans.empty())
		return;
}

void solve() {
	get >> r >> c >> n >> sr >> sc >> x >> y;
	graph.assign(r + 3, vll(c + 3, 0));
	visited.assign(r + 3, vbool(c + 3, false));
	graph[x][y] = 2;	//	end node
	while (n--) {
		get >> x >> y;
		graph[x][y] = -1;
	}

	vpii curr_path;
	curr_path.push_back(makep(sr, sc));
	bfs(curr_path);

	put << ans.size() << endl;
	for (ll i = 0; i < ans.size(); i++)
		put << ans[i].first << "\t" << ans[i].second << endl;
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


/*	Example
Example Input:
5 6 5
2 1 4 6
1 6
2 3
3 4
3 5
4 2

Example Output:
a到b的最短布线方案。（含路径长度和该路径上的坐标点）
*/