#include <bits/stdc++.h>



using namespace std;



typedef long long ll;



const int N = 1e5;



ll steps[N];



void solve() {

	// 1 or 2

	steps[0] = 1;

	steps[1] = 1;

	steps[2] = 2;

	steps[3] = steps[3 - 2] + steps[3 - 1];

	int n;

	cin >> n;

	for (int i = 4; i <= n; i++) {

		steps[i] = steps[i - 2] + steps[i - 1];

	}

	cout << steps[n] << endl;



	// 1...n

	// steps[0] = 0;

	// int step_n;//最高可跳n级

	// cin >> step_n;

	// for (int i = 1; i <= step_n; i++)

	// 	steps[i] = steps[i - 1] + 1;

	// int n;

	// cin >> n;

	// for (int i = step_n + 1; i <= n; i++) {

	// 	steps[i] = 0;

	// 	for (int j = 1; j <= step_n; j++)

	// 		steps[i] += steps[i - j];

	// }

	// cout << steps[n] << endl;

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