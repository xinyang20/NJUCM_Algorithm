// encoding:utf-8


//1、0-1背包问题
// 问题描述：
// 给定n种物品和一个背包，物品i的重量是wi，其价值为vi，背包的容量为C。
// 背包问题是如何选择装入背包的物品，使得装入背包中物品的总价值最大。
// 输入内容（格式不限）:
// 5
// 2 5 4 2 3
// 6 3 5 4 6
// 10
//     有5个物品，
// 其体积分别是{2, 5, 4, 2,3}，价值分别为{ 6, 3, 5, 4,6}，
// 背包的容量为10
// 输出格式:
//     放入背包的物品为1,3,5，最大总价值为17。

#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n;
	cin >> n;
	std::vector<int> v(n);
	std::vector<int> c(n);
	int V;
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	for (int i = 0; i < n; ++i)
		cin >> c[i];
	cin >> V;

	vector<vector<int> > dp(n + 1, vector<int>(V + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= V; j++) {
			if (v[i - 1] <= j)
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i - 1]] + c[i - 1]);
			else
				dp[i][j] = dp[i - 1][j];
			// cout << dp[i][j] << "\t";
		}
		// cout << endl;
	}
	cout << "max:" << dp[n][V] << endl;

	vector<int> way;
	int i = n, j = V;
	while (i > 0 && j > 0) {
		if (dp[i][j] != dp[i - 1][j]) {
			way.push_back(i);
			j -= v[i-1];
		}
		i--;
	}
	reverse(way.begin(), way.end());
	cout << "way:";
	for (auto item : way)
		cout << item << " ";
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int T;
	T = 1;
	while (T--) {
		solve();
	}
	return 0;
}