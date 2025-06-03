#include <iostream>
#include <vector>
#include <queue>      // For std::priority_queue
#include <algorithm>  // For std::sort

// 物品结构体
struct Item_BnB {
    int id;
    int value;
    int weight;
    double density; // 价值密度

    Item_BnB(int i, int v, int w) : id(i), value(v), weight(w) {
        if (weight > 0) {
            density = static_cast<double>(value) / weight;
        } else {
            density = 0; // Or handle as per problem spec for zero weight items
        }
    }
};

// 比较函数，用于按价值密度降序排序物品
bool compareItems_BnB(const Item_BnB& a, const Item_BnB& b) {
    return a.density > b.density;
}

// 状态空间树中的节点结构体
struct Node_BnB {
    int level;          // 当前决策到哪个物品 (物品索引 + 1)
    int current_value;  // 当前路径已获得的总价值
    int current_weight; // 当前路径已占用的总重量
    double upper_bound; // 该节点的上界 (通过分数背包计算)

    // 为了优先队列（最大堆），我们需要重载 < 操作符
    // 或者提供一个比较器，使得上界大的节点优先级高
    bool operator<(const Node_BnB& other) const {
        return upper_bound < other.upper_bound; // 小于号实现最大堆
    }
};

// 限界函数：计算从当前节点出发可能达到的最大价值上界
// items_sorted: 按价值密度排序后的物品列表
// W_capacity: 背包总容量
// node: 当前节点
double calculate_upper_bound(const std::vector<Item_BnB>& items_sorted, int W_capacity, const Node_BnB& node) {
    if (node.current_weight > W_capacity) {
        return 0; // 不可行，上界为0 (或负无穷)
    }

    double bound = node.current_value;
    int weight_so_far = node.current_weight;
    int num_items = items_sorted.size();

    // 从当前节点的下一层开始考虑剩余物品 (分数背包)
    for (int i = node.level; i < num_items; ++i) {
        if (weight_so_far + items_sorted[i].weight <= W_capacity) {
            // 如果整个物品可以放入
            weight_so_far += items_sorted[i].weight;
            bound += items_sorted[i].value;
        } else {
            // 如果只能放入一部分
            int remaining_capacity = W_capacity - weight_so_far;
            bound += items_sorted[i].density * remaining_capacity;
            break; // 背包已满
        }
    }
    return bound;
}

// 函数用于解决0/1背包问题 (分支限界法 - LCFS)
// W_capacity: 背包的总容量
// items_vec: 包含物品信息的向量 (将被内部排序)
int knapsack_01_branch_and_bound(int W_capacity, std::vector<Item_BnB>& items_vec) {
    if (items_vec.empty()) return 0;

    // 1. 按价值密度对物品进行降序排序
    std::sort(items_vec.begin(), items_vec.end(), compareItems_BnB);

    // 2. 初始化优先队列 (最大堆，按upper_bound排序)
    std::priority_queue<Node_BnB> pq;

    // 3. 创建根节点
    Node_BnB root_node = {0, 0, 0, 0.0}; // level 0: 考虑第0个物品之前
    root_node.upper_bound = calculate_upper_bound(items_vec, W_capacity, root_node);
    pq.push(root_node);

    int max_profit_found = 0; // 当前找到的最大利润 (下界)
    int num_items = items_vec.size();

    // 4. 循环直到优先队列为空
    while (!pq.empty()) {
        Node_BnB current_node = pq.top();
        pq.pop();

        // 剪枝1: 如果当前节点的上界不大于已找到的最大利润，则剪枝
        if (current_node.upper_bound <= max_profit_found) {
            continue;
        }

        // 如果已考虑完所有物品
        if (current_node.level == num_items) {
            // 如果这是一个可行的叶节点，并且价值更高，则更新max_profit_found
            // (实际上，上界计算已包含此逻辑，这里主要是检查是否到达末端)
            if (current_node.current_value > max_profit_found) {
                 max_profit_found = current_node.current_value;
            }
            continue;
        }

        // 获取当前层级的物品
        const Item_BnB& current_item = items_vec[current_node.level];

        // 分支1: 包含当前物品 (如果可行)
        Node_BnB node_with_item = current_node;
        node_with_item.level++; // 移动到下一个物品决策层
        if (current_node.current_weight + current_item.weight <= W_capacity) {
            node_with_item.current_weight += current_item.weight;
            node_with_item.current_value += current_item.value;
            
            // 更新当前找到的最大利润 (如果这是一个可行解)
            if (node_with_item.current_value > max_profit_found) {
                max_profit_found = node_with_item.current_value;
            }
            
            node_with_item.upper_bound = calculate_upper_bound(items_vec, W_capacity, node_with_item);
            
            // 剪枝2: 只有当包含物品后的上界仍可能超过当前最大利润时才加入队列
            if (node_with_item.upper_bound > max_profit_found) {
                pq.push(node_with_item);
            }
        }


        // 分支2: 不包含当前物品
        Node_BnB node_without_item = current_node;
        node_without_item.level++; // 移动到下一个物品决策层
        // current_value 和 current_weight 保持不变
        node_without_item.upper_bound = calculate_upper_bound(items_vec, W_capacity, node_without_item);

        // 剪枝3: 只有当不包含物品后的上界仍可能超过当前最大利润时才加入队列
        if (node_without_item.upper_bound > max_profit_found) {
            pq.push(node_without_item);
        }
    }

    return max_profit_found;
}


int main() {
    std::vector<Item_BnB> items;
    items.emplace_back(1, 60, 10);
    items.emplace_back(2, 100, 20);
    items.emplace_back(3, 120, 30);
    int W = 50;
    std::cout << "0/1背包问题的最大价值 (分支限界法): " << knapsack_01_branch_and_bound(W, items) << std::endl; // 输出: 240

    std::vector<Item_BnB> items2;
    items2.emplace_back(1, 10, 2);  // d=5
    items2.emplace_back(2, 10, 4);  // d=2.5
    items2.emplace_back(3, 12, 6);  // d=2
    items2.emplace_back(4, 18, 9);  // d=2
    int W2 = 15;
    // Sorted: (10,2), (10,4), (12,6), (18,9) or (10,2), (10,4), (18,9), (12,6)
    // Optimal: (10,2) + (10,4) + (18,9) -> v=38, w=15
    std::cout << "0/1背包问题的最大价值 [35]: " << knapsack_01_branch_and_bound(W2, items2) << std::endl; // 应该是38
    return 0;
}