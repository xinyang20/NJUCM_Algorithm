#include <bits/stdc++.h>



using namespace std;



typedef long long ll;



std::vector<int> v;



class R {

private:

	int d1;//买入日期

	int d2;//卖出日期

public:

	int sum;//收益

	R(int date1, int date2, int sum) {d1 = date1; d2 = date2; this->sum = sum;}

	R(const R &other) {d1 = other.d1; d2 = other.d2; sum = other.sum;}

	~R() {}

};



R find(int a, int b) {

	if (a == b)

		return R(a, b, 0);



	int mid = (a + b) / 2;

	R l = find(a, mid);

	R r = find(mid+1, b);



	int min = v[a], max = v[mid];

	int min_d = a, max_d = mid;



	for (int i = a + 1; i <= mid; i++) {

		if (min > v[i])

		{

			min = v[i];

			min_d = i;

		}

	}

	for (int i = mid + 1; i <= b; i++) {

		if (max < v[i])

		{

			max = v[i];

			max_d = i;

		}

	}



	R m(min_d, max_d, max - min);



	if (l.sum > r.sum && l.sum > m.sum)

		return l;

	if (r.sum > l.sum && r.sum > m.sum)

		return r;

	return m;

}



void solve() {

	int n;

	cin >> n;

	v.resize(n + 3);

	for (int i = 0; i <= n; ++i)

		cin >> v[i];

	R ans = find(0, n);

	cout << ans.sum << endl;



	// 线性扫描

	// int n;

	// cin >> n;

	// vector<int> prices(n+3);

	// for (int i = 0; i <= n; ++i)

	//     cin >> prices[i];

	// int minPrice = INT_MAX;

	// int maxProfit = 0;

	// for (int i = 0; i < n; ++i) {

	//     if (prices[i] < minPrice) {

	//         minPrice = prices[i];

	//     } else if (prices[i] - minPrice > maxProfit) {

	//         maxProfit = prices[i] - minPrice;

	//     }

	// }

	// cout << maxProfit << endl;

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