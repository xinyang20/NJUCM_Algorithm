#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

void solve() {
	string x, y;
	cin >> x >> y;
	std::vector<vector<int> > v(x.length() + 3, vector<int>(y.length() + 3, 0));
	std::vector<vector<int> > m(x.length() + 3, vector<int>(y.length() + 3, 0));
	for (int i = 0; i < x.length() + 3; ++i) v[i][0] = 0;
	for (int i = 0; i < y.length() + 3; ++i) v[0][i] = 0;

	for (int i = 1; i <= x.length(); ++i) {
		for (int j = 1; j <= y.length(); ++j) {
			if (x[i] == y[j]) {
				m[i][j] = 1;
				v[i][j] = v[i - 1][j - 1] + 1;
			}
			else if (v[i - 1][j] > v[i][j - 1]) {
				v[i][j] = v[i - 1][j];
				m[i][j] = 2;
			} else {
				v[i][j] = v[i][j - 1];
				m[i][j] = 3;
			}
		}
	}

	// cout << "v[][]:\n";
	// for (int i = 1; i <= x.length(); ++i) {
	// 	for (int j = 1; j <= y.length(); ++j)
	// 		cout << v[i][j] << " ";
	// 	cout << endl;
	// }
	// cout << "v.end\nm[][]:\n";
	// for (int i = 1; i <= x.length(); ++i) {
	// 	for (int j = 1; j <= y.length(); ++j)
	// 		cout << m[i][j] << " ";
	// 	cout << endl;
	// }

	cout << v[x.length()][y.length()] << endl;

	string str;

	int row = x.length(), col = y.length();
	while (1) {
		if (row == 0 || col == 0) 
			break;
		if (str.length() == v[x.length()][y.length()]) {
			cout << str << endl;
			return;
		}
		if (m[row][col] == 1) {
			str = str + x[row - 2];
			row--;
			col--;
		}
		else if (m[row][col] == 2) {
			row--;
		} else if (m[row][col] == 3) {
			col--;
		}
		// cout << endl;
	}
	for(int i=str.length()-1;i>=0;i--)
		cout << str[i];
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