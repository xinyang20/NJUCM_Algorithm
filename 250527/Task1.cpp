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

struct Node
{
	ll w;
	ll c;
};

const int N = 1000 + 3;
ll n, m, w, c, maxc, minw = LLONG_MAX;
Node node[N][N];
vll best;
vll min;

void bfs(int curr, ll currc, ll currw, vll prew) {
	if (curr == n + 1) {
		if (currw < minw && currc <= maxc) {
			minw = currw;
			best = prew;
		}
		return;
	}

	ll indexminw = currw;
	for (int i = curr; i <= n; i++)
		indexminw += min[i];
	if (indexminw > minw)
		return;

	if (currc > maxc)
		return;

	for (ll i = 1; i <= node[curr][0].w; i++) {
		prew.push_back(i);
		bfs(curr + 1, currc + node[curr][i].c, currw + node[curr][i].w, prew);
		prew.pop_back();
	}
}

void solve() {
	get >> n >> maxc;
	min.assign(n+3, LLONG_MAX);
	for (int i = 1; i <= n; i++) {
		get >> m;
		node[i][0].w = m;
		node[i][0].c = -1;
		for (int j = 1; j <= m; j++) {
			get >> w >> c;
			node[i][j].w = w;
			node[i][j].c = c;
			if (min[i] > w)
				min[i] = w;
		}
	}

	vll prew;
	prew.push_back(-1);
	bfs(1, 0, 0, prew);

	put << minw << endl;
	for (ll i = 1; i < best.size(); i++)
		put << best[i] << "\t";
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