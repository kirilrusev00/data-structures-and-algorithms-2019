#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
private:
    int n; // vertices
    int m; // edges
    unordered_map<int, int> placeInAdj;
    vector<unordered_set<int>> adj;
    int maxNumberOfColors;
    int adjSize = 0;

    void dfsHelper(int s, vector<bool>& visited) {
        visited[s] = true;
        for (auto it : adj[s]) {
            if (visited[placeInAdj[it]] == false) {
                dfsHelper(placeInAdj[it], visited);
            }
        }
    }

    void dfs() {
        vector<bool> visited(adjSize, false);
        for (int i = 0; i < adjSize; i++) {
            if (visited[i] == false) {
                maxNumberOfColors++;
                dfsHelper(i, visited);
            }
        }
    }

public:
    Graph() {
        input();
    }

    void input() {
        cin >> n;
        cin >> m;
        for (int i = 0; i < m; i++) {
            int x;
            int y;
            cin >> x;
            cin >> y;
            auto it = placeInAdj.find(x);
            if (it == placeInAdj.end()) {
                placeInAdj.emplace(x, adjSize);
                adj.emplace_back(unordered_set<int> ({y}));
                adjSize++;
            }
            else {
                adj[it->second].emplace(y);
            }
            it = placeInAdj.find(y);
            if (it == placeInAdj.end()) {
                placeInAdj.emplace(y, adjSize);
                adj.emplace_back(unordered_set<int> ({x}));
                adjSize++;
            }
            else {
                adj[it->second].emplace(x);
            }
            //adj.emplace(x, y);
            //adj.emplace(y, x);
        }
        maxNumberOfColors = n - adj.size();
        if (maxNumberOfColors < 0) {
            maxNumberOfColors = 0;
        }
    }

    int getMaxNumberOfColors() {
        dfs();
        return maxNumberOfColors;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Graph gr;
    cout << gr.getMaxNumberOfColors();
    //gr.print();

    return 0;
}
