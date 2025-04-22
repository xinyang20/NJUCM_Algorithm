// 在n×n格的棋盘上放置彼此不受攻击的n个皇后。
// 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
// 		n皇后问题等价于在n×n格的棋盘上放置n个皇后，任何两个皇后不放在同一行
// 		或同一列或同一斜线上。
// 编程要求：找出一个n×n格的棋盘上放置n个皇后并使其不能互相攻击的所有方案。

// encoding:utf-8

#include <bits/stdc++.h>
#define endl '\n'

typedef long long ll;


std::vector<ll> loc;
std::vector<bool> col;
ll n, ans;

bool check() {
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= n; j++) {
			if (i == j)
				continue;
			if (abs(i - j) == abs(loc[i] - loc[j]))
				return false;
		}
	}
	return true;
}

void dfs(ll pos) {
	if (pos > n && check()) {
		for (ll i = 1; i <= n; i++)
			std::cout << loc[i] << " ";
		std::cout << endl;
		ans++;
		return;
	}

	for (ll i = 1; i <= n; i++) {
		bool k = true;
		for (ll j = 1; j < pos; j++)
			if (abs(pos - j) == abs(i - loc[j])){
				k = false;
				break;
			}
		if (!col[i] && k) {
			col[i] = true;
			loc[pos] = i;
			dfs(pos + 1);
			col[i] = false;
		}
	}
}

void solve() {
	std::cin >> n;

	loc.assign(n + 1, 0);
	col.assign(n + 1, false);
	ans = 0;

	dfs(1);

	std::cout << "Total:" << ans << endl;

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
Example Input:
5

Example Output:
1 3 5 2 4
1 4 2 5 3
2 4 1 3 5
2 5 3 1 4
3 1 4 2 5
3 5 2 4 1
4 1 3 5 2
4 2 5 3 1
5 2 4 1 3
5 3 1 4 2
Total=10
*/