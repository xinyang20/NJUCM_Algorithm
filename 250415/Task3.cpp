// -*- coding:utf-8 -*-
// author:xinyang20
// =====================================================

#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;

struct Edge
{
	ll from_node;
	ll end_node;
	ll lenth;
};

void solve() {
	int node_num, edge_num;
	cin >> node_num >> edge_num;
	std::vector<ll> dist(node_num + 1, LLONG_MAX);
	std::vector<ll> pre(node_num + 1, -1);
	std::vector<Edge> edge(edge_num);


	dist[1] = 0;
	for (ll i = 0; i < edge_num; i++)
		cin >> edge[i].from_node >> edge[i].end_node >> edge[i].lenth;

	// queue<ll> q;
	// q.push(1);
	// while (!q.empty()) {
	// 	ll now_node = q.front();
	// 	q.pop();
	// 	for (ll i = 0; i < edge_num; i++)
	// 		if (edge[i].from_node == now_node) {
	// 			if (dist[edge[i].end_node] > dist[edge[i].from_node] + edge[i].lenth) {
	// 				dist[edge[i].end_node] = dist[edge[i].from_node] + edge[i].lenth;
	// 				pre[edge[i].end_node] = edge[i].from_node;
	// 				q.push(edge[i].end_node);
	// 			}
	// 		}
	// }

	// Dijstra
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
	q.push({0, 1});
	while (!q.empty()) {
		ll now_dist = q.top().first, now_node = q.top().second;
		q.pop();
		if (now_dist > dist[now_node]) continue;
		for (ll i = 0; i < edge_num; i++)
			if (edge[i].from_node == now_node) {
				if (dist[edge[i].end_node] > dist[edge[i].from_node] + edge[i].lenth) {
					dist[edge[i].end_node] = dist[edge[i].from_node] + edge[i].lenth;
					pre[edge[i].end_node] = edge[i].from_node;
					q.push({dist[edge[i].end_node], edge[i].end_node});
				}
			}
	}

	cout << "Num:\t";
	for (int i = 1; i <= node_num; i++)
		cout << i << "\t";
	cout << "\nDist:\t";
	for (int i = 1; i <= node_num; i++)
		cout << dist[i] << "\t";
	cout << "\nPre:\t";
	for (int i = 1; i <= node_num; i++)
		cout << pre[i] << "\t";
}

int main() {
	int T;
	// cin >> T;
	T = 1;
	while (T--) {
		solve();
	}
	return 0;
}
/*
Example Input:
5 8
1 2 2
1 3 5
2 3 2
2 4 6
3 4 7
3 5 1
4 3 2
4 5 4
*/