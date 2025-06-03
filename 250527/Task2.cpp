// encoding:utf-8

#include <bits/stdc++.h>

#define makep std::make_pair
#define get std::cin
#define put std::cout
#define endl '\n'

using ll = long long;
using paii = std::pair<int, int>;
using pall = std::pair<long long , long long>;
using vpii = std::vector<std::pair<int, int> >;
using vint = std::vector<int>;
using vll = std::vector<long long>;
using vll2 = std::vector<std::vector<long long> >;
using vbool = std::vector<bool>;
using vbool2 = std::vector<std::vector<bool> >;
using qll = std::queue<long long>;
using mll = std::map<long long, long long>;
using sll = std::set<ll>;

template <class T>
T qpow(T a, ll b) {
	T ans = 1;
	while (b > 0) {
		if (b & 1)
			ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

template <class T>
T tmin(T a, T b) {
	return a < b ? a : b;
}

template <class T>
T tmax(T a, T b) {
	return a > b ? a : b;
}

// --- 全局变量 ---
ll n, m, k, minc = LLONG_MAX; // n:顶点数, m:边数, k:边数限制, minc:最小总权重 (初始化为最大值)
std::vector<paii> best; // 存储最佳选择的边列表

// 边的结构体，方便存储和排序
struct Edge {
    int u, v;
    ll w;
};
std::vector<Edge> all_edges; // 存储所有输入的边

// --- DSU (Disjoint Set Union) 函数 ---
// parent: DSU的父节点数组
// findx: 查找元素a的根节点，并进行路径压缩
int findx(std::vector<int>& parent, int a) {
    if (parent[a] == a)
        return a;
    return parent[a] = findx(parent, parent[a]); // 路径压缩
}

// merge: 合并a和b所在的集合
// 注意：这里没有使用按秩合并或按大小合并，但对于N较小（如20以内）且每次都复制parent数组的场景，影响不大。
void merge(std::vector<int>& parent, int a, int b) {
    int root_a = findx(parent, a);
    int root_b = findx(parent, b);
    if (root_a != root_b)
        parent[root_a] = root_b;
}

// --- 核心递归回溯 (DFS) 函数 ---
// edge_idx: 当前考虑的在 all_edges 数组中的边的索引
// current_cost: 当前已选择边的总权重
// current_edges_count: 当前已选择的边数
// current_parent: DSU的父节点数组的副本（每次递归传值，实现状态回溯）
// current_components: 当前连通分量的数量
// current_path: 存储当前递归路径中选择的边 (通过引用传递，函数内部push_back/pop_back实现回溯)
void dfs_constrained_mst(int edge_idx, ll current_cost, int current_edges_count,
                         std::vector<int> current_parent, int current_components,
                         std::vector<paii>& current_path) {

    // 剪枝 1: 如果当前总权重已经不小于已知最小权重，则没有必要继续探索
    if (current_cost >= minc)
        return;
    // 剪枝 2: 如果已选择的边数超过k，则不符合约束
    if (current_edges_count > k)
        return;

    // 终止条件 1: 所有顶点都已连通 (连通分量数量为1)
    if (current_components == 1) {
        // 找到一个满足条件的方案，检查是否更优
        if (current_cost < minc) {
            minc = current_cost;
            best = current_path; // 更新最佳方案
        }
        return; // 已找到连通解，返回
    }

    // 终止条件 2: 所有边都已考虑完毕，但图仍未完全连通
    if (edge_idx == all_edges.size()) {
        return;
    }

    // 剪枝 3: 优化剪枝 - 如果即使选择所有剩余的最少必需的边也无法在k限制内连通所有顶点
    // 连通 remaining_components 个分量至少需要 remaining_components - 1 条边
    // 这里的 remaining_components 就是 current_components
    // 如果 current_edges_count (已选边数) + (current_components - 1) (还需要的最少边数) > k (总边数限制)
    if (current_edges_count + (current_components - 1) > k) {
        return;
    }


    // --- 递归探索两种情况：不选择当前边 或 选择当前边 ---

    // 情况 1: 不选择当前边 all_edges[edge_idx]
    // DSU状态、总权重、已选边数、连通分量数和路径都保持不变
    dfs_constrained_mst(edge_idx + 1, current_cost, current_edges_count,
                       current_parent, current_components, current_path);

    // 情况 2: 尝试选择当前边 all_edges[edge_idx]
    Edge& edge = all_edges[edge_idx];
    int root_u = findx(current_parent, edge.u);
    int root_v = findx(current_parent, edge.v);

    // 只有当这条边连接了两个不同的连通分量时，才考虑选择它
    // (因为我们的目标是最小权重且 <= k 边，形成环的边不会帮助减少连通分量，只会增加成本和边数)
    if (root_u != root_v) {
        // 创建一个 DSU 状态的副本，以便在这个分支中修改，而不影响其他分支的回溯
        std::vector<int> next_parent = current_parent;
        merge(next_parent, root_u, root_v); // 合并这两个分量

        current_path.push_back({edge.u, edge.v}); // 将当前边加入路径
        dfs_constrained_mst(edge_idx + 1, current_cost + edge.w, current_edges_count + 1,
                           next_parent, current_components - 1, current_path); // 连通分量减1
        current_path.pop_back(); // 回溯：从路径中移除当前边，为其他分支做好准备
    }
}

void solve() {
    std::cin >> n >> m >> k;

    // 读取所有边并存储到 all_edges 中
    for (int i = 0; i < m; i++) {
        ll s, e, v;
        std::cin >> s >> e >> v;
        all_edges.push_back({(int)s, (int)e, v});
    }

    // 对所有边按权重进行排序，这对于剪枝和寻找最小权重非常重要
    std::sort(all_edges.begin(), all_edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    // 初始化 DSU 父节点数组，每个节点都是自己的父节点
    std::vector<int> initial_parent(n + 1);
    std::iota(initial_parent.begin(), initial_parent.end(), 0); // initial_parent[i] = i

    std::vector<paii> current_path; // 用于存储当前递归路径的边

    // 调用 DFS 函数开始搜索
    // 参数：起始边索引0，初始总权重0，初始已选边数0，初始DSU状态，初始连通分量数n，空路径
    dfs_constrained_mst(0, 0, 0, initial_parent, n, current_path);

    // 输出结果
    std::cout << minc << '\n';
    for (size_t i = 0; i < best.size(); i++) {
        std::cout << "(" << best[i].first << "," << best[i].second << ")";
    }
    std::cout << '\n';
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int T;
	T = 1;
	// std::cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}

/* Example
Example Input:
4 5 3
1 2 1
1 3 3
2 3 2
2 4 4
3 4 5

Example Output:
7
(1,2)(2,3)(2,4)
*/