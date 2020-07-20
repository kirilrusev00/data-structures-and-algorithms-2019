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
    
    Edge(int from, int to) {
        this->from = from;
        this->to = to;
    }
};

struct Call {
    int type;
    int from;
    int to;
    
    Call(int type, int from, int to) {
        this->type = type;
        this->from = from;
        this->to = to;
    }
};

class Graph {
private:
    int n;
    vector<int> parent;
    vector<Edge> edges;
    int q;
    vector<Call> calls;

    void input() {
        int m;
        cin >> n >> m;
        parent.resize(n);
        for (int i = 0; i < m; i++) {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            edges.emplace_back(from, to);
        }
        cin >> q;
        for (int i = 0; i < q; i++) {
            int type, from, to;
            cin >> type >> from >> to;
            from--;
            to--;
            calls.emplace_back(type, from, to);
        }
    }

    void kruskal() {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        for (Edge edge : edges) {
            if (parent[edge.from] != parent[edge.to]) {

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
public:
    Graph() {
        input();
        kruskal();
    }
    
    void output() {
        for (int i = 0; i < q; i++) {
            if(calls[i].type == 1) {
                if (parent[calls[i].from] == parent[calls[i].to]) {
                    cout << 1;
                }
                else {
                    cout << 0;
                }
            } else {
                if (parent[calls[i].from] != parent[calls[i].to]) {
                    int old_parent = parent[calls[i].from];
                    int new_parent = parent[calls[i].to];
                    for (int i = 0; i < n; i++) {
                        if (parent[i] == old_parent) {
                            parent[i] = new_parent;
                        }
                    }
                }
            }
        }
    }
};

int main() {
    
    Graph gr;
    gr.output();
    
    return 0;
}

