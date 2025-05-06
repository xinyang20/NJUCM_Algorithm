// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#define endl '\n'

typedef long long ll;

struct cmp
{
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    }
};

const int N = 25;
int map[N][N];
int noden, edgen;
ll Min_cost = INT_MAX;
std::vector<int> best_path;

void dfs(int cur_node, ll cur_cost, std::vector<int>& path, std::vector<bool>& visited, int start_node) {
    if (path.size() == noden) {
    	// Back
        if (map[cur_node][start_node] != -1) {
            ll total_cost = cur_cost + map[cur_node][start_node];
            if (total_cost < Min_cost) {
                Min_cost = total_cost;
                best_path = path;
            }
        }
        // Not Back
        // if (cur_cost < Min_cost) {
        //     Min_cost = cur_cost;
        //     best_path = path;
        // }
        return;
    }

    if (cur_cost >= Min_cost)
        return;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> q;
    for (int i = 1; i <= noden; i++) {
        if (!visited[i] && map[cur_node][i] != -1) {
            q.push(std::make_pair(i, map[cur_node][i]));
        }
    }

    while (!q.empty()) {
        std::pair<int, int> next_pair = q.top();
        q.pop();
        int next_node = next_pair.first;
        int edge_cost = next_pair.second;

        if (!visited[next_node]) {
            visited[next_node] = true;
            path.push_back(next_node);
            dfs(next_node, cur_cost + edge_cost, path, visited, start_node);
            path.pop_back();
            visited[next_node] = false;
        }
    }
}


void TSP() {
    std::vector<int> path;
    std::vector<bool> visited(noden + 1, false);
    int start_node = 1;

    path.push_back(start_node);
    visited[start_node] = true;

    dfs(start_node, 0, path, visited, start_node);

    std::cout << Min_cost << endl;
    if (best_path.size() != 0){
        std::cout << start_node;
        for (int i = 1; i < best_path.size(); i++)
            std::cout << "->" << best_path[i];
           // std::cout << "->" << start_node;
        std::cout << endl;
    }
}


void solve() {
    std::cin >> noden >> edgen;
    int from, to, dist;
    for (int i = 0; i <= noden; i++)
        for (int j = 0; j <= noden; j++)
            map[i][j] = -1;

    for (int i = 0; i < edgen; i++) {
        std::cin >> from >> to >> dist;
        map[from][to] = dist;
        map[to][from] = dist;
    }
    TSP();
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int T;
    T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

/*
Example Input
5 9
1 2 3
1 4 8
1 5 7
2 3 3
2 4 10
2 5 5
3 4 4
3 5 3
4 5 20

Example Output
23
1 4 3 5 2
*/