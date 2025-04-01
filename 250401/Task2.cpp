// encoding:utf-8

#include <bits/stdc++.h>

using namespace std;

// 2、最大子段和
// 问题描述：
// 输入一个整形数组，数组里有正数也有负数，数组中连续的一个或多个整数
// 组成一个子数组，每个子数组都有一个和，求所有子数组的和的最大值。
// 要求时间复杂度为O(n)。
// 输入样例
// 8
// 1 -2 3 10 -4 7 2 -5
// 1,-2,3,10，-4,7,2，-5
// 输出样例
// 和最大子数组为3,10，-4,7,2,对应数组和为18。

void solve() {
	int n;
	cin >> n;
	std::vector<int> v(n);
	std::vector<int> pre(n + 1, 0);
	int max = -1, maxi = -1, nsi = -1, maxsi = -1;
	for (int i = 0; i < n; i++)
		cin >> v[i];
	for (int i = 1; i <= n; i++) {
		if (pre[i - 1] < 0) {
			nsi = i;
			pre[i] = v[i - 1];
		}
		else
			pre[i] = pre[i - 1] + v[i - 1];

		if (pre[i] > max) {
			max = pre[i];
			maxi = i;
			maxsi = nsi;
		}
	}
	cout << "max:" << max << endl;
	cout << "way:";
	for (int i = maxsi; i <= maxi; i++)
		cout << v[i - 1] << " ";

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