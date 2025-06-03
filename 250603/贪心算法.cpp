#include <iostream>
#include <vector>
#include <algorithm>

// 物品结构体
struct Item {
    int id;
    int value;
    int weight;
    double density; // 价值密度 (value/weight)

    Item(int i, int v, int w) : id(i), value(v), weight(w) {
        if (weight > 0) {
            density = static_cast<double>(value) / weight;
        } else {
            density = 0; // 或者根据情况处理重量为0的物品
        }
    }
};

// 比较函数，用于按价值密度降序排序物品
bool compareItems(const Item& a, const Item& b) {
    return a.density > b.density;
}

// 函数用于解决分数背包问题
// W: 背包的总容量
// items_vec: 包含物品信息的向量
double fractional_knapsack_greedy(int W, std::vector<Item>& items_vec) {
    // 按价值密度对物品进行降序排序
    std::sort(items_vec.begin(), items_vec.end(), compareItems);

    double total_value_in_knapsack = 0.0;
    int current_weight_in_knapsack = 0;

    // 遍历排序后的物品
    for (const auto& item : items_vec) {
        if (current_weight_in_knapsack == W) {
            break; // 背包已满
        }

        if (item.weight <= (W - current_weight_in_knapsack)) {
            // 如果整个物品可以放入
            current_weight_in_knapsack += item.weight;
            total_value_in_knapsack += item.value;
            // std::cout << "放入物品 " << item.id << " (全部), 重量: " << item.weight << ", 价值: " << item.value << std::endl;
        } else {
            // 如果只能放入物品的一部分
            int remaining_capacity = W - current_weight_in_knapsack;
            double fraction_to_take = static_cast<double>(remaining_capacity) / item.weight;
            total_value_in_knapsack += item.value * fraction_to_take;
            current_weight_in_knapsack += remaining_capacity; // 背包已满
            // std::cout << "放入物品 " << item.id << " (部分: " << fraction_to_take * 100 << "%), 重量: " << remaining_capacity << ", 价值: " << item.value * fraction_to_take << std::endl;
            break; // 背包已满
        }
    }
    return total_value_in_knapsack;
}

int main() {
    std::vector<Item> items;
    items.emplace_back(1, 60, 10);
    items.emplace_back(2, 100, 20);
    items.emplace_back(3, 120, 30);

    int W = 50;
    std::cout << "分数背包问题的最大价值 (贪心算法): " << fractional_knapsack_greedy(W, items) << std::endl; // 输出: 240.0

    std::vector<Item> items2;
    items2.emplace_back(1, 10, 2);
    items2.emplace_back(2, 5, 3);
    items2.emplace_back(3, 15, 5);
    items2.emplace_back(4, 7, 7);
    items2.emplace_back(5, 6, 1);
    items2.emplace_back(6, 18, 4);
    items2.emplace_back(7, 3, 1);
    int W2 = 15;
    // 预期价值: 10(id1) + 6(id5) + 3(id7) + 18(id6) + 7/5*15 (错误，应该是7/7*3=3 from id4, or 15-2-1-1-4=7, 7/3*5 for id2)
    // 排序后密度: id5(6), id1(5), id7(3), id6(4.5), id4(1), id3(3), id2(1.66) -> (id5, id1, id6, id7, id3, id2, id4)
    // id5 (w=1, v=6), W=14, V=6
    // id1 (w=2, v=10), W=12, V=16
    // id6 (w=4, v=18), W=8, V=34
    // id7 (w=1, v=3), W=7, V=37
    // id3 (w=5, v=15), W=2, V=37 + 15*(2/5) = 37 + 6 = 43
    std::cout << "分数背包问题的最大价值 (贪心算法): " << fractional_knapsack_greedy(W2, items2) << std::endl;
    // 应该是 55.333... (10+5+15+7+6+18*(1/4)) -> 55.5 if sorted by value/weight
    // 6/1=6 (item 5), 10/2=5 (item 1), 18/4=4.5 (item 6), 15/5=3 (item 3), 3/1=3 (item 7), 5/3=1.66 (item 2), 7/7=1 (item 4)
    // Take item 5 (w=1, v=6). Rem W=14. Total V=6.
    // Take item 1 (w=2, v=10). Rem W=12. Total V=16.
    // Take item 6 (w=4, v=18). Rem W=8. Total V=34.
    // Take item 3 (w=5, v=15). Rem W=3. Total V=49.
    // Take item 7 (w=1, v=3). Rem W=2. Total V=52.
    // Take item 2 (w=3, v=5). Take 2/3 of item 2. Weight = 2. Value = 5 * (2/3) = 3.333. Rem W=0. Total V = 52 + 3.333 = 55.333
    return 0;
}