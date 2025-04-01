// encoding:utf-8

#include <bits/stdc++.h>

using namespace std;

// 3. 最长递增子序列
// 问题描述：
// 给出一个序列a1,a2,a3,a4,a5,a6,a7....an，
// 求它的一个子序列（设为s1,s2,...sn），使得这个子序列满足这样的性质，
// s1<s2<s3<...<sn，并且这个子序列的长度最长。
// 输入
// 7
// 1 7 3 5 9 4 8
// 输出
// 长度为4
// 序列为1 3 5 9和1 3 4 8

struct Node {
	int length;
	int max;
};

void solve() {
	int n;
	cin >> n;
	std::vector<int> v(n);
	std::vector<Node> dp(n + 1);
	for (int i = 0; i < n; i++)
		cin >> v[i];
	dp[0].length = 0;
	dp[0].max = INT_MIN;
	int max = -1;
	for (int i = 1; i <= n; i++) {
		dp[i].length = 1;
		dp[i].max = v[i - 1];
		for (int j = 0; j < i; j++) {
			if (dp[j].max < dp[i].max && dp[j].length + 1 > dp[i].length) {
				dp[i].max = v[i - 1];
				dp[i].length = dp[j].length + 1;
			}
		}

		if (dp[i].length > max)
			max = dp[i].length;
	}
	cout << "max:" << max << endl;
	vector<int> way;
	int i = n, nmax = INT_MAX;
	while (i > 0 && max > 0) {
		if (dp[i].length < nmax) {
			way.push_back(dp[i].max);
			nmax = dp[i].length;
			max--;
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