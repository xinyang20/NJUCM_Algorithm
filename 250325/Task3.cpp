#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

int check(string x, string y) {
	std::vector<vector<int> > v(x.length() + 3, vector<int>(y.length() + 3, 0));
	for (int i = 0; i < x.length() + 3; ++i) v[i][0] = 0;
	for (int i = 0; i < y.length() + 3; ++i) v[0][i] = 0;

	for (int i = 0; i < x.length(); ++i) {
		for (int j = 0; j < y.length(); ++j) {
			if (x[i] == y[j])
				v[i+1][j+1] = v[i][j] + 1;
			else
				v[i+1][j+1] = 0;
		}
	}


	int ans = -1;
	for (int i = 1; i <= y.length(); ++i)
		if (v[x.length()][i] > ans)
			ans = v[x.length()][i];
	return ans;
}

void solve() {
	string x, y, z;
	cin >> x >> y >> z;
	if (check(x, y) > check(x, z))
		cout << y << endl;
	else
		cout << z << endl;
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