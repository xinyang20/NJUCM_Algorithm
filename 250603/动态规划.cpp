#include <iostream>
#include <vector>
#include <algorithm> // Required for std::max

// 函数用于解决0/1背包问题
// W: 背包的总容量
// wt: 包含n个物品重量的向量
// val: 包含n个物品价值的向量
// n: 物品的数量
int knapsack_01_dp(int W, const std::vector<int>& wt, const std::vector<int>& val, int n) {
    // 创建一个二维dp表，dp[i][j]将存储
    // 使用前i个物品（物品索引从1到i）且背包容量为j时的最大价值
    // 表的大小为 (n+1) x (W+1) 以处理0个物品或0容量的情况
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    // 填充dp表
    for (int i = 0; i <= n; ++i) { // 遍历物品 (i代表考虑了前i个物品)
        for (int j = 0; j <= W; ++j) { // 遍历背包容量
            if (i == 0 |
| j == 0) {
                // 基本情况：如果没有物品或背包容量为0，则最大价值为0
                dp[i][j] = 0;
            } else if (wt[i - 1] <= j) {
                // 如果当前物品 (wt[i-1]) 的重量小于等于当前容量j
                // 我们可以选择：
                // 1. 不放入当前物品：价值为 dp[i-1][j]
                // 2. 放入当前物品：价值为 val[i-1] + dp[i-1][j - wt[i-1]]
                // 取两者中的最大值
                dp[i][j] = std::max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
            } else {
                // 如果当前物品的重量大于当前容量j，则不能放入当前物品
                // 最大价值与不考虑当前物品时相同
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // dp[n][W] 存储了使用所有n个物品，在容量为W的背包中所能获得的最大价值
    return dp[n][W];
}

int main() {
    std::vector<int> val = {60, 100, 120};
    std::vector<int> wt = {10, 20, 30};
    int W = 50;
    int n = val.size();
    std::cout << "0/1背包问题的最大价值 (动态规划): " << knapsack_01_dp(W, wt, val, n) << std::endl; // 输出: 240

    std::vector<int> val2 = {1, 2, 3};
    std::vector<int> wt2 = {4, 5, 1};
    int W2 = 4;
    int n2 = val2.size();
    std::cout << "0/1背包问题的最大价值 (动态规划): " << knapsack_01_dp(W2, wt2, val2, n2) << std::endl; // 输出: 3
    return 0;
}