#include <bits/stdc++.h>

using namespace std;

class Graph {
private:
    int n;
    int** adj_matrix;
    int q;
    vector<pair<int, int>> queries;
    int maxValue;
    
    void input() {
        int m;
        cin >> n >> m;
        adj_matrix = new int*[n];
        maxValue = 100000000;
        for (int i = 0; i < n; i++) {
            adj_matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                adj_matrix[i][j] = maxValue;
            }
        }
        for (int i = 0; i < m; i++) {
            int from, to, weight;
            cin >> from >> to >> weight;
            from--;
            to--;
            adj_matrix[from][to] = weight;
        }
        cin >> q;
        for(int i = 0; i < q; i++) {
            int from, to;
            cin >> from >> to;
            from--;
            to--;
            queries.emplace_back(from, to);
        }
    }
    
    void FloydWarshall() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adj_matrix[i][j] = min(adj_matrix[i][j], adj_matrix[i][k] + adj_matrix[k][j]);
                }
            }
        }
    }
    
public:
    Graph() {
        input();
    }
    
    void output() {
        FloydWarshall();
        for (int i = 0; i < q; i++) {
            if (queries[i].first == queries[i].second) {
                cout << 0 << endl;
            }
            else if (adj_matrix[queries[i].first][queries[i].second] == maxValue) {
                cout << -1 << endl;
            }
            else {
                cout << adj_matrix[queries[i].first][queries[i].second] << endl;
            }
        }
    }
};

int main()
{
    Graph gr;
    gr.output();

    return 0;
}
