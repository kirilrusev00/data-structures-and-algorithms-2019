#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
using namespace std;


class Graph {
private:
	vector<vector<int>> adj;
	int n;
	int m;

	int k;
	vector<int> path;

	vector<bool> attractionNotToVisitYet;

	void input() {
		cin >> n;
		cin >> m;
		adj.resize(n);
		for (int i = 0; i < m; i++) {
			int from, to;
			cin >> from >> to;
			adj[from].push_back(to);
		}
		attractionNotToVisitYet.resize(n, false);
		cin >> k;
		path.resize(k);
		for (int i = 0; i < k; i++) {
			cin >> path[i];
			attractionNotToVisitYet[path[i]] = true;
		}
	}

public:
	Graph() {
		input();
	}

	int bfs() {
		int result = 0;
		attractionNotToVisitYet[path[0]] = false;
		for (int i = 0; i < k - 1; i++) {
			attractionNotToVisitYet[path[i + 1]] = false;
			vector<bool> visited(n, false);
			queue<pair<int, int>> q;
			q.emplace(0, path[i]);
			visited[path[i]] = true;
			int dist = -1;
			while (!q.empty()) {
				pair<int, int> top = q.front();
				q.pop();
				//visited[top.second] = true;
				if (top.second == path[i + 1]) {
					dist = top.first;
					break;
				}
				for (int j = 0; j < adj[top.second].size(); j++) {
					if (!visited[adj[top.second][j]] && !attractionNotToVisitYet[adj[top.second][j]]) {
						q.emplace(top.first + 1, adj[top.second][j]);
						visited[adj[top.second][j]] = true;
					}
				}
			}
			if (dist == -1) {
				return -1;
			}
			else result += dist;
		}
		return result;
	}
};



int main() {
	Graph gr;
	cout << gr.bfs() << " ";

	return 0;
}
