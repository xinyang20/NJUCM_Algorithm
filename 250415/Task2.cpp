// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

void solve() {
	ll n, c;
	cin >> n >> c;
	std::vector<ll> v(n);
	std::vector<pair<ll, ll> > ans(n);
	for (ll i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());
	ll l = 0, r = n - 1, min = 0;
	while (l < r) {
		while (v[l] + v[r] > c && l < r) {
			r--;
			ans[min++] = {v[r], -1};
		}
		ans[min++] = {v[l++], v[r]};
	}
	cout << min << "\n";
	for (ll i = 0; i < min; i++) {
		// cout << i + 1 << ":" << ans[i].first << " " << ans[i].second == -1 ? "" : ans[i].second << "\n";
		cout << i + 1 << ":" << ans[i].first;
		if (ans[i].second != -1)
			cout << " " << ans[i].second;
		cout << "\n";
	}
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
4 85
45 65 40 58
*/