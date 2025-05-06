// encoding:utf-8

// 问题描述：
// 给定n个集装箱要装上一艘载重量为c的轮船，其中集装箱i的重量为wi。
//	集装箱装载问题要求确定在不超过轮船载重量的前提下，将尽可能多的集装箱装上轮船。
// 由于集装箱问题是从n个集装箱里选择一部分集装箱，假设解向量为X(x1, x2, …, xn)，
//	其中xi∈{0, 1}， xi =1表示集装箱i装上轮船， xi =0表示集装箱i不装上轮船。
// 输入：
// 每组测试数据：第1行有2个数C和n。C是轮船的载重量（0＜C＜30000），
// 	n是集装箱的个数（n≤20）。第2行有n个数w1, w2, …, wn，分别表示n个集装箱的重量。
// 输出：
// 对每个测试例，输出两行：第1行是装载到轮船的最大载重量，第2行是集装箱的编号。

#include <bits/stdc++.h>

#define endl '\n'

typedef long long ll;

double C, max_w = -1;
ll n;
std::vector<double> v;
std::vector<int> best_ans;

void dfs(double cur_w, ll cur_i, ll cur_len, std::vector<int> &ans) {
	if (cur_i==n) {
		if (cur_w > max_w) {
			max_w = cur_w;
			best_ans = ans;
		}
		return;
	}

	for (int i = cur_i + 1; i < n; i++) {
		dfs(cur_w, cur_len, i, ans);
	}
	ans.push_back(cur_i);
	for (int i = cur_i + 1; i < n; i++) {
		dfs(cur_w + v[cur_i], cur_len + 1, i, ans);
	}
	ans.pop_back();
}

void solve() {
	std::cin >> C >> n;
	v.resize(n);
	for (int i = 0; i < n; i++)
		std::cin >> v[i];
	// sort(v.begin(), v.end());
	std::vector<int> ans;
	dfs(0, 0, 0, ans);

	std::cout << max_w << endl;
	for (int i = 0; i < best_ans.size(); i++)
		std::cout << best_ans[i]+1 << " ";
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

/*
Example Input
34.1 3
21.1 10.1 5.3

Example Output
31.2
1 2
*/