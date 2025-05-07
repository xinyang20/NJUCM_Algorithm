#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
typedef long long ll;

struct step {
	int num1;
	int num2;
	char op;
	int ans;
};

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

void show(step s) {
	cout << max(s.num1, s.num2) << " " << s.op << " " << min(s.num1, s.num2) << " = " << s.ans << endl;
}

int Num[4];
vector<step> ans_path;
bool exist;

void dfs(vector<int> num, vector<step> path) {
	int size = num.size();
	if (size == 1 || exist) {
		if (num[0] == 24) {
			ans_path = path;
			exist = true;
		}
		return;
	}


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j)continue;

			vector<int> nnum;
			for (int k = 0; k < size; k++) {
				if (k != i && k != j) {
					nnum.push_back(num[k]);
				}
			}

			step s;
			s.num1 = num[i];
			s.num2 = num[j];

			s.op = '+';
			s.ans = num[i] + num[j];
			nnum.push_back(s.ans);
			path.push_back(s);
			dfs(nnum, path);
			path.pop_back();
			nnum.pop_back();

			s.op = '-';
			s.ans = num[i] - num[j];
			nnum.push_back(s.ans);
			path.push_back(s);
			dfs(nnum, path);
			path.pop_back();
			nnum.pop_back();

			s.op = '*';
			s.ans = num[i] * num[j];
			nnum.push_back(s.ans);
			path.push_back(s);
			dfs(nnum, path);
			path.pop_back();
			nnum.pop_back();

			// Division
			// if (num2 != 0 && num1 % num2 == 0) {
			//     s.op = '/';
			//     s.ans = num1 / num2;
			//     nnum.push_back(s.ans);
			//     path.push_back(s);
			//     dfs(nnum, path);
			//     path.pop_back();
			//     nnum.pop_back();
			// }
			if (num[j] != 0 && num[i] % num[j] == 0) {
			// if (num[i] % num[j] == 0 && num[j] != 0) {
				s.op = '/';
				s.ans = num[i] / num[j];
				nnum.push_back(s.ans);
				path.push_back(s);
				dfs(nnum, path);
				path.pop_back();
				nnum.pop_back();
			}
		}
	}
}





void solve() {
	vector<int> num(4);
	for (int i = 0; i < 4; i++) {
		cin >> num[i];
	}

	exist = false;
	ans_path.clear();
	vector<step> path;

	dfs(num, path);

	if (exist) {
		for (int i = 0; i < ans_path.size(); i++)
			show(ans_path[i]);
	} else {
		cout << "No answer!\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	T = 1;
	while (T--) {
		solve();
	}
	return 0;
}


