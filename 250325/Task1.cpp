#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

void solve() {
	int n;
	cin >> n;
	std::vector<vector<int> > v(n, vector<int>(n));
	std::vector<vector<int> > vv(n, vector<int>(n));
	std::vector<vector<int> > m(n, vector<int>(n, -1));
	std::vector<int> way(n);
	for (int row = 0; row < n; row++)
		for (int col = 0; col <= row; col++) {
			cin >> v[row][col];
			vv[row][col] = v[row][col];
		}

	for (int row = n - 2; row >= 0; row--)
		for (int col = 0; col <= row; col++) {
			if (v[row + 1][col] > v[row + 1][col + 1]) {
				m[row][col] = 1;
				v[row][col] += v[row + 1][col + 1];
			}
			else {
				m[row][col] = 0;
				v[row][col] += v[row + 1][col];
			}
		}

	cout << v[0][0] << endl;

	int pre_col = 0;
	for (int i = 0; i < n; i++) {
		way[n - i - 1] = vv[i][pre_col];
		pre_col += m[i][pre_col];
	}
	for (int i = 0; i < n - 1; i++)
		cout << way[i] << "->";
	cout << way[n - 1] << endl;

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