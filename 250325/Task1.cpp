#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

void solve() {
	int n;
	cin >> n;
	std::vector<vector<int> > v(n, vector<int>(n));
	for (int row = 0; row < n; row++)
		for (int col = 0; col <= row; col++)
			cin >> v[row][col];

	for (int row = n - 2; row >= 0; row--)
		for (int col = 0; col <= row; col++)
			v[row][col] += min(v[row + 1][col], v[row + 1][col + 1]);

	cout << v[0][0] << endl;
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