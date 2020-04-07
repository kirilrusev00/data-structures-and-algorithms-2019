#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


class Graph {
private:
	vector<map<int, int>> adj;
	int n;
	int m;
	int k;
	vector<int> path;

	void input() {
		cin >> n;
		cin >> m;
		adj.resize(n);
		for (int i = 0; i < m; i++) {
			int from, to, weight;
			cin >> from >> to >> weight;
			adj[from].emplace(to, weight);
			adj[to].emplace(from, weight);
		}
		cin >> k;
		path.resize(k);
		for (int i = 0; i < k; i++) {
			cin >> path[i];
		}
	}

public:
	Graph() {
		input();
	}

	int check() {
		int counter = 0;
		for (int i = 0; i < k - 1; i++) {
			auto it = adj[path[i]].find(path[i + 1]);
			if (it == adj[path[i]].end()) {
				return -1;
			}
			else {
				counter += it->second;
			}
		}
		return counter;
	}
};



int main() {
	Graph gr;
	cout << gr.check();
	return 0;
}
