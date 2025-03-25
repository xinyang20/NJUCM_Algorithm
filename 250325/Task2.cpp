#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

void solve() {
	string x, y;
	cin >> x >> y;
	std::vector<vector<int> > v(x.length() + 3, vector<int>(y.length() + 3, 0));
	for (int i = 0; i < x.length() + 3; ++i) v[i][0] = 0;
	for (int i = 0; i < y.length() + 3; ++i) v[0][i] = 0;

	for (int i = 1; i <= x.length(); ++i) {
		for (int j = 1; j <= y.length(); ++j) {
			if (x[i] == y[j])
				v[i][j] = v[i - 1][j - 1] + 1;
			else
				v[i][j] = max(v[i - 1][j], v[i][j - 1]);
		}
	}

	cout << v[x.length()][y.length()] << endl;
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