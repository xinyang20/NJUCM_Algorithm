// 棋盘上A点有一个过河卒，需要走到目标B点。卒行走的规则：可以向下、或者向右。
//		同时在棋盘上C点有一个对方的马，该马所在的点和所有跳跃一步可达的点称
//		为对方马的控制点。因此称之为“马拦过河卒”。
// 棋盘用坐标表示，A点(0, 0)、B点(n, m)(n, m为不超过15的整数)，同样马的
//		位置坐标是需要给出的。现在要求你计算出卒从A点能够到达B点的路径的条数，
//		假设马的位置是固定不动的，并不是卒走一步马走一步。
// 输入:
//	一行四个数据，分别表示B点坐标和马的坐标。
// 输出：
//	一个数据，表示所有的路径条数。

// encoding:utf-8

#include <bits/stdc++.h>

#define endl '\n'

typedef long long ll;

std::vector<std::vector<ll> > mp;
ll bx, by, cx, cy, ans;
int xto[2] = {1, 0};
int yto[2] = {0, 1};

int clocx[9] = {0, 1,  2,  2, 1, -1, -2, -2, -1};
int clocy[9] = {0, -2, -1, 1, 2, 2,  1,  -1, -2};

ll max(ll a, ll b) {
	return a > b ? a : b;
}

void dfs(ll x,ll y){
	if(mp[y][x]||(y>max(cy + 2, by)||x>max(cx + 2, bx)))
		return;
	if(x==bx&&y==by)
		ans++;
	for(int i=0;i<2;i++)
		dfs(x+xto[i],y+yto[i]);
}

void solve() {
	std::cin >> bx >> by >> cx >> cy;
	ans = 0;
	mp.assign(max(cy + 2, by)+2, std::vector<ll>(max(cx + 2, bx)+2, 0));
	for(int i=0;i<9;i++)
		mp[cy+clocy[i]][cx+clocx[i]]=1;
	
	dfs(0,0);

	std::cout<<ans<<endl;
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
Example Input:
6 6 3 3

Example Output:
6
*/