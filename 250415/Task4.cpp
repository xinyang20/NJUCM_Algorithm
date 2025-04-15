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

	while (n >= 4) {
		ll sum1 = 2 * v[0] + v[n - 1] + v[n - 2];
		ll sum2 = 2 * v[1] + v[0] + v[n - 1];
		if (sum1 > sum2)
			sum += sum2;
		else
			sum += sum1;
		n -= 2;
	}
	if (n == 3)
		sum += v[0] + v[1] + v[2];
	else if (n == 2)
		sum += v[1];
	else if (n == 1)
		sum += v[0];

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