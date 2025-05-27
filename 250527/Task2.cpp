// encoding:utf-8

#include <bits/stdc++.h>

#define makep std::make_pair
#define get std::cin
#define put std::cout
#define endl '\n'

using ll = long long;
using paii = std::pair<int, int>;
using pall = std::pair<long long , long long>;
using vpii = std::vector<std::pair<int, int> >;
using vint = std::vector<int>;
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
T tmin(T a, T b) {
	return a < b ? a : b;
}

template <class T>
T tmax(T a, T b) {
	return a > b ? a : b;
}



ll n, m, k, minc = LLONG_MAX;
vpii best;
vint node;
vll2 graph;

ll findx(vint& node, ll a) {
	while (node[a] != a)
		a = node[a];
	return a;
}

void merge(vint& node, ll a, ll b) {
	ll finda = findx(node, a);
	ll findb = findx(node, b);
	if (finda != findb)
		node[finda] = findb;
}

ll count(vint& node) {
	ll cnt = 0;
	for (int i = 1; i <= n; i++)
		if (node[i] == i)
			cnt++;
	return cnt;
}

void bfs(int cnt, int currc, int currecnt, vint prew_node, vpii curr) {
	if (cnt == 1) {
		if (currc < minc && currecnt <= k) {
			minc = currc;
			best = curr;
		}
		return;
	}

	if (currc > minc || currecnt > k)
		return;

	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (graph[i][j] && findx(prew_node, i) != findx(prew_node, j)) {
				vint new_prew = prew_node;
				merge(new_prew, i, j);
				curr.push_back(makep(i, j));
				bfs(count(new_prew), currc + graph[i][j], currecnt + 1, new_prew, curr);
				curr.pop_back();
			}
		}
	}
}

void solve() {
	get >> n >> m >> k;
	node.assign(n + 3, -1);
	graph.assign(n + 3, vll(n + 3, -1));
	for (int i = 1; i <= n; i++)
		node[i] = i;

	ll s, e, v;
	for (int i = 0; i < m; i++) {
		get >> s >> e >> v;
		graph[s][e] = v;
		graph[e][s] = v;
	}

	vint new_node = node;
	vpii curr;

	bfs(count(new_node), 0, 0, new_node, curr);

	put << minc << endl;
	for (int i = 0; i < best.size(); i++)
		put << "( " << best[i].first << " , " << best[i].second << " )";
	put << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int T;
	T = 1;
	// std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}