#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;

class Graph {
private:
    int n; // vertices
    int m; // edges
    vector<list<int>> adj;
    vector<bool> visited;
    
    vector<int> order;

public:
    Graph() {
        input();
    }

    void input() {
        cin >> n;
        cin >> m;
        adj = vector<list<int>>(n);
        for (int i = 0; i < m; i++) {
            int x;
            int y;
            cin >> x;
            cin >> y;
            x--;
            y--;
            adj[x].push_back(y);
        }
        visited = vector<bool>(n, false);
    }
    
    void topologicalSort() {
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfsUtil(i);
            }
        }
        reverse(order.begin(), order.end());
    }

    void dfsUtil(int start) {
        visited[start] = true;
        for (auto it : adj[start]) {
            if (visited[it] == false) {
                dfsUtil(it);
            }
        }
        order.push_back(start);
    }

    int getWays(int from, int to) {
        from--;
        to--;
        topologicalSort();
        
        vector<int> ways(n, 0);
        
        ways[to] = 1;
        
        for (int i = order.size() - 1; i >= 0; i--) { 
            for (auto it : adj[order[i]]) { 
                ways[order[i]] = (ways[order[i]] + ways[it]) % 1000000007; 
            } 
        } 

        return ways[from];
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Graph gr;
    int start, end;
    cin >> start >> end;
    cout << gr.getWays(start, end);

    return 0;
}
