// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

struct Node
{
	ll idx;
	ll c;
	ll v;
};

bool cmp(Node a, Node b) {
	if (a.v * 1.0 / a.c > b.v * 1.0 / b.c)
		return true;
	return false;
}

void solve() {
	ll mc, n;
	cin >> mc >> n;
	vector<Node> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].c >> arr[i].v;
		arr[i].idx = i + 1;
	}
	sort(arr.begin(), arr.end(), cmp);
	vector<ll> ans;
	ll i = 0;
	double mv = 0;
	bool tag = false;
	while (mc > 0 && i < n) {
		if (arr[i].c <= mc) {
			ans.push_back(arr[i].idx);
			mc -= arr[i].c;
			mv += arr[i].v;
		} else {
			ans.push_back(arr[i].idx);
			tag = true;
			mv += arr[i].v * 1.0 / arr[i].c * mc;
			mc = 0;
		}
		i++;
	}
	cout << "MAX Value:" << mv << "\n";
	cout << ans[0];
	for (ll i = 1; i < ans.size(); i++)
		cout << " " << ans[i];
	if (tag)
		cout << "*\n";
}

int main() {
	int T;
	// cin >> T;
	T = 1;
	while (T--) {
		solve();
	}
	return 0;
}
/*
Example Input:
30
10
4 2
2 8
9 18
5 6
5 8
8 20
5 5
4 6
5 7
5 15
*/