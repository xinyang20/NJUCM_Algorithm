// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <bits/stdc++.h>

#define makep std::make_pair
#define get std::cin
#define put std::cout
#define endl '\n'

using ll = long long;
using paii = std::pair<int, int>;
using pall = std::pair<long long , long long>;
using vpii = std::vector<std::pair<int, int> >;
using vll = std::vector<long long>;
using vll2 = std::vector<std::vector<long long> >;
using vbool = std::vector<bool>;
using vbool2 = std::vector<std::vector<bool> >;
using qll = std::queue<long long>;
using mll = std::map<long long, long long>;
using sll = std::set<ll>;

template <class T>
T qpow(T a, ll b) {
	T ans = 1;
	while (b > 0) {
		if (b & 1)
			ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

template <class T>
T min(T a, T b) {
	return a < b ? a : b;
}

template <class T>
T max(T a, T b) {
	return a > b ? a : b;
}

ll goal;
mll t;

void solve() {
	{	/*
		// small data
		get >> goal;
		if (t.count(goal)) {
			if (t[goal] != -1)
				put << t[goal] << endl;
			else
				put << "None" << endl;
		}
		else {
			ll num = goal, MOD = 1;
			while (num) {
				num /= 10;
				MOD *= 10;
			}

			for (ll i = sqrt(goal); i <= 1e5 + 3; i++)
				if ((i * i) % MOD == goal) {
					t[goal] = i;
					break;
				}
			if (t.count(goal)) {
				if (t[goal] != -1)
					put << t[goal] << endl;
				else
					put << "None" << endl;
			}
			else {
				t[goal] = -1;
				put << "None" << endl;
			}
			// put<<"MOD:"<<MOD<<endl;
		}
		*/
	}

	get >> goal;
	if (goal == 0) {
		put << "None" << endl;
		return;
	}
	ll goal_p = goal, zero_num = 0, ans = -1;
	while (goal_p > 0) {
		if (goal_p % 10 == 0)
			zero_num++;
		else
			break;
		goal_p /= 10;
	}
	if (zero_num & 1) {
		if (goal != 0)
			ans = -1;
		else
			ans = 0;
	}
	else {
		if (t.count(goal)) {
			ans = t[goal];
		} else {
			ll num = goal_p, MOD = 1;
			if (num == 0)
				MOD = 10;
			else {
				while (num) {
					num /= 10;
					MOD *= 10;
				}
			}
			ll curr_mod = 1;
			sll curr_solutions;
			curr_solutions.insert(0);
			while (curr_mod < MOD) {
				ll next_mod = curr_mod * 10;
				sll next_solutions;
				for (auto &it : curr_solutions) {
					for (int i = 0; i < 10; i++) {
						ll new_m = it + i * curr_mod;
						if ((new_m * new_m) % next_mod == goal_p % next_mod) {
							next_solutions.insert(new_m);
						}
					}
				}
				curr_solutions = next_solutions;
				curr_mod = next_mod;
				if (next_solutions.empty())
					break;
			}
			if (curr_solutions.empty())
				t[goal] = -1;
			else
				t[goal] = (*curr_solutions.begin()) * qpow(10, zero_num / 2);
			ans = t[goal];
		}
	}


	if (ans != -1)
		put << ans << endl;
	else
		put << "None" << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	int T;
	T = 1;
	std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}