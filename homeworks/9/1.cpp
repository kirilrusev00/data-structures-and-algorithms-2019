#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    
    Edge(int from = 0, int to = 0, int weight = 0) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }
    
    bool operator< (const Edge& rhs) {
        if (weight == rhs. weight) {
            return (from + to + weight) < (rhs.from + rhs.to + rhs.weight);
        }
        return weight < rhs. weight;
    }
};

int n;
int cost = 0;
vector<int> parent;
vector<Edge> edges;

void input() {
    int m;
    cin >> n >> m;
    parent.resize(n);
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges.emplace_back(from, to, weight);
    }
}

void kruskal() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    sort(edges.begin(), edges.end());
    for (Edge edge : edges) {
        if (parent[edge.from] != parent[edge.to]) {
            cost += edge.weight;
            
            int old_parent = parent[edge.from];
            int new_parent = parent[edge.to];
            for (int i = 0; i < n; i++) {
                if (parent[i] == old_parent) {
                    parent[i] = new_parent;
                }
            }
        }
    }
}

int main() {
    
    input();
    kruskal();
    
    cout << cost;
    
    return 0;
}
