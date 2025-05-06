// encoding:utf-8

// 题目描述：
// 几十年前全世界就流行一种数字游戏，至今仍有人乐此不疲．
//	在中国我们把这种游戏称为“算24点”。您作为游戏者将得到4个1~9之间的自然数作为
//	操作数，而您的任务是对这4个操作数进行适当的算术运算，要求运算结果等于24。
// 您可以使用的运算只有：+，-，*，/，您还可以使用（）来改变运算顺序。
//	注意：所有的中间结果须是整数，所以一些除法运算是不允许的
//	（例如，(2*2)/4是合法的，2*(2/4)是不合法的）。
//	下面我们给出一个游戏的具体例子：
// 若给出的4个操作数是：1、2、3、7，则一种可能的解答是1+2+3*7=24。

// 输入描述:
// 只有一行，四个1到9之间的自然数。
// 输出描述:
// 如果有解的话，只要输出一个解，输出的是三行数据，分别表示运算的步骤。
//	其中第一行是输入的两个数和一个运算符和运算后的结果，
//	第二行是第一行的结果和一个输入的数据、运算符、运算后的结果；
//	第三行是第二行的结果和输入的一个数、运算符和“=24”。
//	如果两个操作数有大小的话则先输出大的。
// 如果没有解则输出“No answer!”。


#include <bits/stdc++.h>

#define endl '\n'

typedef long long ll;

class step {
public:
	int num1;
	int num2;
	char op;
	int ans;
	void show() {
		std::cout << num1 << " " << op << " " << num2 << " = " << ans << endl;
	}
};

int num[4];
char op[4] = {'+', '-', '*', '/'};

// int max(int a, int b) {
// 	return a > b ? a : b;
// }

// int min(int a, int b) {
// 	return a < b ? a : b;
// }

bool cmp(int a, int b) {
	return a > b ? true : false;
}


int sss = 0;
void dfs(int num[], int len, std::vector<step> &path) {

	std::cout << "----------------------\n";
	std::cout << "step " << sss++ << ":\n";
	for (int i = 0; i < path.size(); i++)
		path[i].show();
	for(int i=0;i<4;i++)
		std::cout<<num[i]<<" ";
	std::cout<<endl;


	bool exisit=false;
	for(int i=0;i<4;i++)
		if(num[i]==24){
			exisit=true;
			break;
		}
	if (len == 1 && exisit) {
		return;
	}

	if (num[0] > 24)
		return;

	for (int n1 = 0; n1 < len; n1++) {
		if (num[n1] == -1)continue;
		for (int n2 = 0; n2 < len; n2++) {
			if (n1 == n2)continue;
			if (num[n2] == -1)continue;
			if(num[n2]>num[n1])continue;
			int nn1 = num[n1], nn2 = num[n2];
			step s;
			for (int o = 0; o < 4; o++) {
				int ans;
				if (o == 0)
					ans = num[n1] + num[n2];
				if (o == 1)
					ans = num[n1] - num[n2];
				if (o == 2)
					ans = num[n1] * num[n2];
				if (o == 3) {
					if (num[n1]%num[n2]== 0)
						ans = num[n1]/num[n2];
					else continue;
				}
				s.num1 = num[n1];
				s.num2 = num[n2];
				s.op = op[o];
				s.ans = ans;
				num[n1] = s.ans; num[n2] = -1;
				path.push_back(s);
				dfs(num, len - 1, path);
				path.pop_back();
				num[n1] = nn1; num[n2] = nn2;
			}

		}
	}
}

void solve() {
	for (int i = 0; i < 4; i++)
		std::cin >> num[i];
	std::vector<step> path;
	dfs(num, 4, path);

	std::sort(num, num + 4, cmp);
	if (num[0] == 24) {
		for (int i = 0; i < 3; i++)
			path[i].show();
	} else {
		std::cout << "No answer!\n";
	}

}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int T;
	T = 1;
	while (T--) {
		solve();
	}
	return 0;
}

/*
Example Input
1 2 3 7

Example Output
2+1=3
7*3=21
21+3=24
*/