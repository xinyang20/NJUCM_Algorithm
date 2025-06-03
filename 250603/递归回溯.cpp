#include <iostream>
#include <vector>
#include <algorithm> // Required for std::max

// 函数用于解决0/1背包问题 (递归回溯)
// W: 当前背包的剩余容量
// wt: 包含n个物品重量的向量
// val: 包含n个物品价值的向量
// n: 当前正在考虑的物品的索引 (从0开始，表示第 n 个物品，或者说，还剩下 items.size() - n 个物品待考虑)
//    或者，也可以理解为还剩下 n 个物品需要考虑，此时物品索引为 items.size() - n
//    为了与常见的 DP 递推 n 表示物品数量对应，这里采用 n 表示剩余待处理物品数量，
//    处理的物品是 wt[items.size() - n]
//    更直观的可能是传递当前物品的索引 current_idx 和总物品数 total_items
int knapsack_01_recursive_internal(int W, const std::vector<int>& wt, const std::vector<int>& val, int current_idx, int total_items) {
    // 基准情况1: 没有剩余容量或所有物品都已考虑完毕
    if (W == 0 |
| current_idx == total_items) {
        return 0;
    }

    // 如果当前物品的重量大于背包剩余容量，则不能选择该物品
    // 直接考虑下一个物品
    if (wt[current_idx] > W) {
        return knapsack_01_recursive_internal(W, wt, val, current_idx + 1, total_items);
    } else {
        // 如果当前物品可以放入，则有两种选择：
        // 1. 不放入当前物品：递归考虑下一个物品，容量不变
        int value_without_current = knapsack_01_recursive_internal(W, wt, val, current_idx + 1, total_items);

        // 2. 放入当前物品：加上当前物品的价值，递归考虑下一个物品，容量减少当前物品的重量
        int value_with_current = val[current_idx] + knapsack_01_recursive_internal(W - wt[current_idx], wt, val, current_idx + 1, total_items);

        // 返回两种选择中的最大价值
        return std::max(value_with_current, value_without_current);
    }
}

// 包装函数，方便调用
int knapsack_01_recursive(int W, const std::vector<int>& wt, const std::vector<int>& val) {
    if (wt.empty() |
| val.empty() |
| wt.size()!= val.size()) {
        return 0; // 或者抛出异常
    }
    return knapsack_01_recursive_internal(W, wt, val, 0, wt.size());
}


int main() {
    std::vector<int> val = {60, 100, 120};
    std::vector<int> wt = {10, 20, 30};
    int W = 50;
    std::cout << "0/1背包问题的最大价值 (递归回溯): " << knapsack_01_recursive(W, wt, val) << std::endl; // 输出: 240

    std::vector<int> val2 = {1, 2, 3};
    std::vector<int> wt2 = {4, 5, 1};
    int W2 = 4;
    std::cout << "0/1背包问题的最大价值 (递归回溯): " << knapsack_01_recursive(W2, wt2, val2) << std::endl; // 输出: 3

    std::vector<int> weight_s39 = { 1, 2, 4, 5 };
    std::vector<int> value_s39 = { 5, 4, 8, 6 };
    int W_s39 = 5;
    std::cout << "0/1背包问题的最大价值 [17]: " << knapsack_01_recursive(W_s39, weight_s39, value_s39) << std::endl; // 输出: 13
    return 0;
}