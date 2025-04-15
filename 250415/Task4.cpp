// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

void solve() {
	ll n, sum = 0;
	cin >> n;
	std::vector<ll> v(n);
	for (ll i = 0; i < n; i++)
		cin >> v[i];
	sort(v.begin(), v.end());
	for (ll i = 0; i < n / 2; i++){
		sum += v[i] + v[n - i - 1];
		if(n%2==0)
			sum-=v[i];
	}
	if (n % 2 != 0)
		sum += v[n / 2];
	cout << sum << endl;
}

int main() {
	int T;
	cin >> T;
	// T = 1;
	while (T--) {
		solve();
	}
	return 0;
}

/*
Example Input:
1
4
1 2 5 10
*/