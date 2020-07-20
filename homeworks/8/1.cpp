#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

class Graph {
private:
    int n; // vertices
    int m; // edges
    vector<vector<int>> adj;
    map<string, int> citiesToCode;
    map<int, string> codeToCities;
    int code = 0;
    string startDestination;
    int startDestinationCode;
    bool* visited;
    vector<int> cycle;

    void input() {
        cin >> n;
        cin >> m;
        adj = vector<vector<int>>(n);
        for (int i = 0; i < m; i++) {
            string from;
            string to;
            cin >> from;
            cin >> to;
            int fromCode;
            int toCode;
            auto it = citiesToCode.find(from);
            if (it == citiesToCode.end()) {
                fromCode = code;
                citiesToCode.emplace(from, code);
                codeToCities.emplace(code, from);
                code++;
            }
            else {
                fromCode = it->second;
            }
            it = citiesToCode.find(to);
            if (it == citiesToCode.end()) {
                toCode = code;
                citiesToCode.emplace(to, code);
                codeToCities.emplace(code, to);
                code++;
            }
            else {
                toCode = it->second;
            }
            adj[fromCode].push_back(toCode);
        }
        cin >> startDestination;
        auto it = citiesToCode.find(startDestination);
        if (it == citiesToCode.end()) {
            startDestinationCode = -1;
        }
        else {
            startDestinationCode = it->second;
        }
        visited = new bool[n];
        for (auto i = 0; i < n; i++) {
            visited[i] = false;
        }
    }

public:
    Graph() {
        input();
    }

    void bfs() {
        bool isCycle = false;
        queue<int> q;
        visited[startDestinationCode] = true;
        q.push(startDestinationCode);
        int* pred = new int[n];
        for (int i = 0; i < n; i++) {
            pred[i] = -1;
        }
        while (!isCycle && !q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < adj[u].size(); i++) { 
                if (visited[adj[u][i]] == false) {
                    visited[adj[u][i]] = true;
                    pred[adj[u][i]] = u;
                    q.push(adj[u][i]);
                }
                if (adj[u][i] == startDestinationCode) {
                    pred[adj[u][i]] = u;
                    isCycle = true;
                    break;
                }
            }
        }
        if (!isCycle) {
            cout << -1 << endl;
        }
        else {
            vector<string> cycle;
            auto itStart = codeToCities.find(startDestinationCode);
            cycle.push_back(itStart->second);
            int curr = pred[startDestinationCode];
            while (curr != startDestinationCode) {
                auto it = codeToCities.find(curr);
                cycle.push_back(it->second);
                curr = pred[curr];
            }
            cycle.push_back(itStart->second);
            for (int i = cycle.size() - 1; i >= 0; i--) {
                cout << cycle[i] << " ";
            }
        }
    }

    ~Graph() { 
        delete[] visited;
    }
};

int main() {

    Graph gr;
    gr.bfs();

    return 0;
}
