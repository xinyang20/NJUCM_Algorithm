#include <iostream>



using namespace std;



typedef long long ll;



void solve() {

	ll v[55 + 5];

	v[1] = 1;

	v[2] = 2;

	v[3] = 3;

	for (int i = 4; i < 55 + 1; ++i)

		v[i] = v[i - 3] + v[i - 1];

	int n;

	while (cin >> n) {

		if (n == 0)break;

		cout << v[n] << endl;

	}

// 	for (int i = 1; i < 55 + 1; ++i)

// 		cout << i << " " << v[i] << endl;

}



int main() {

	int T;

// cin>>T;

	T = 1;

	while (T--) {

		solve();

	}

	return 0;

}