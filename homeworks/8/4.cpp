#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <climits>
#include <list>
using namespace std;

class Graph {
private:
    int n; // vertices
    int m; // edges
    vector<list<pair<int, int>>> adj;
    int k;
    bool* isDisco;

public:
    Graph() {
        input();
    }

    void input() {
        cin >> n;
        cin >> m;
        adj = vector<list<pair<int, int>>>(n);
        for (int i = 0; i < m; i++) {
            int x;
            int y;
            int distance;
            cin >> x;
            cin >> y;
            cin >> distance;
            adj[x].emplace_back(y, distance);
            adj[y].emplace_back(x, distance);
        }
        isDisco = new bool[n];
        for (auto i = 0; i < n; i++) {
            isDisco[i] = false;
        }
        cin >> k;
        for (int i = 0; i < k; i++) {
            int x;
            cin >> x;
            isDisco[x] = true;
        }
        
    }

    void dijkstra(vector<int>& dist) {
        vector<bool> visited(n, false);
        multiset<pair<int,int>> s;
        for (int i = 0; i < n; i++) {
            if (isDisco[i]) {
                dist[i] = 0;
                s.insert({0, i});
            }
        }
        while(!s.empty()) {
            pair<int , int> p = *s.begin();
            s.erase(s.begin());

            int x = p.second; 
            int weight = p.first;
            if (visited[x]) {
                continue;   
            }
            visited[x] = true;

            for(auto it : adj[x]){
                int edge = it.first; 
                int weight = it.second;
                if (dist[x] + weight < dist[edge]){
                    dist[edge] = dist[x] + weight;
                    s.insert({dist[edge], edge});
                }
            }
        }
    }

    void output() {
        vector<int> dist(n, INT_MAX);
        dijkstra(dist);
        int q;
        cin >> q;
        int query;
        for (int i = 0; i < q; i++) {
            cin >> query;
            cout << dist[query] << endl;
        }
    }

    ~Graph() {
        delete[] isDisco;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Graph gr;
    gr.output();

    return 0;
}
