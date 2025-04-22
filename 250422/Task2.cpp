// 给定无向连通图G=(V, E)和m种不同的颜色，用这些颜色为图G的各顶点着色，
// 每个顶点着一种颜色。是否有一种着色法使G中相邻的两个顶点有不同的颜色?
// 这个问题是图的m可着色判定问题。若一个图最少需要m种颜色才能使图中每条边连接的
// 		两个顶点着不同颜色，则称这个数m为该图的色数。求一个图的色数m的问题称为
//		图的m可着色优化问题。
// 编程计算：给定图G=(V, E)和m种不同的颜色，找出所有不同的着色法和着色总数。
// 输入：
// 第一行是顶点的个数n（2≤n≤10），颜色数m（1≤m≤n）。
// 接下来是顶点之间的相互关系：a b
// 表示a和b相邻。当a，b同时为0时表示输入结束。
// 输出：
// 输出所有的着色方案，表示某个顶点涂某种颜色号，每个数字的后面有一个空格。
// 		最后一行是着色方案总数。

// encoding:utf-8

#include <bits/stdc++.h>

#define endl '\n'

typedef long long ll;

ll n,m,a,b,ans_count;
std::vector<std::vector<bool> > mp;
std::vector<ll> ans;

void dfs(ll pos){
	if(pos>n){
		for(ll i=1;i<=n;i++)
			std::cout<<ans[i]<<" ";
		std::cout<<"\n";
		ans_count++;
		return;
	}

	for(ll i=1;i<=m;i++){
		bool ok=true;
		for(ll j=1;j<pos;j++)
			if(mp[pos][j]&&ans[j]==i){
				ok=false;
				break;
			}

		if(!ok)
			continue;
		ans[pos]=i;
		dfs(pos+1);
	}
}

void solve() {
	std::cin>>n>>m;

	ans.assign(n+1,-1);
	mp.assign(n+1,std::vector<bool>(n+1,false));
	ans_count=0;

	while(std::cin>>a>>b){
		if(a==0&&b==0)
			break;
		mp[a][b]=true;
		mp[b][a]=true;
	}

	dfs(1);

	std::cout << "Total:" << ans_count << endl;
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
5 4
1 3
1 2
1 4
2 3
2 4
2 5
3 4
4 5
0 0

Example Output:
1 2 3 4 1
1 2 3 4 3
1 2 4 3 1
1 2 4 3 4
1 3 2 4 1
1 3 2 4 2
1 3 4 2 1
...
4 3 2 1 4
Total=48
*/