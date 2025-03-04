#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int Num;

int sum(int num) {
	int sum = 0;
	for (int i = 1; i < sqrt(num); ++i)
	{
		if (num % i == 0)sum += i + num / i;
		if (sum > Num)return -1;
	}
	return sum;
}

void solve() {
	std::vector<int> v;
	cin >> Num;
	for (int i = 1; i < Num; i++) {
		if (sum(i) == Num)
			v.push_back(i);
	}
	cout << v.size() << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}