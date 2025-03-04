#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void solve() {
	int n;
	cin >> n;
	vector<int> x(n);
	vector<int> y(n);
	for (int i = 0; i < n; i++)
		cin >> x[i] >> y[i];
	sort(x.begin(), x.end());
	sort(y.begin(), y.end());
	for (int i = 0; i < n; i++) 
		x[i] = x[i] - i;
	sort(x.begin(), x.end());
	int xmid = x[n / 2];
	int ymid = y[n / 2];
	int xsum = 0,ysum = 0;
	for (int i = 0; i < n; i++) {
		xsum += abs(x[i] - xmid);
		ysum += abs(y[i] - ymid);
	}
	cout << xsum + ysum << endl;
}

int main() {
	solve();
	return 0;
}