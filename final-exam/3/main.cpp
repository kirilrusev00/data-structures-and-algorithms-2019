#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <stack>
using namespace std;


class Graph {
private:
	vector<set<int>> adj;
	int n;
	int m;
	vector<bool> visited;

	void input() {
		cin >> n;
		cin >> m;
		adj.resize(n);
		for (int i = 0; i < m; i++) {
			int from, to;
			cin >> from >> to;
			adj[from].emplace(to);
			adj[to].emplace(from);
		}
		visited.resize(n, false);
	}

public:
	Graph() {
		input();
	}

	void dfsUtil(int s) {


	}

	int dfs() {
		int counter = 0;
		stack<int> st;
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				counter++;
				visited[i] = true;
				st.push(i);
				while (!st.empty()) {
					int s = st.top();
					st.pop();
					for (auto it : adj[s]) {
						if (!visited[it]) {
							visited[it] = true;
							st.push(it);
						}
					}
				}
			}
		}
		return counter;
	}
};



int main() {
	std::cin.tie(NULL);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		Graph gr;
		cout << gr.dfs() << " ";
	}

	return 0;
}