#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <list>
#include <queue>
#include <climits>
using namespace std;

struct Tunnel {
    int to;
    int kg;
    int time;
    
    Tunnel(int to, int kg, int time) {
        this->to = to;
        this->kg = kg;
        this->time = time;
    }
    
    bool operator<(const Tunnel& rhs) const {
        if (this->kg < rhs.kg) {
            return true;
        }
        if (this->kg == rhs.kg && this->time < rhs.time) {
            return true;
        }
        return false;
    }
};

class Graph {
private:
    int n;
    int m;
    vector<set<Tunnel>> adj;
    int maxTime;
    int result;
    
public:
    Graph() {
        input();
    }

    void input() {
        cin >> n;
        cin >> m;
        cin >> maxTime;
        adj.resize(n);
        for (int i = 0; i < m; i++) {
            int u;
            int v;
            int c;
            int t;
            cin >> u;
            cin >> v;
            u--;
            v--;
            cin >> c;
            cin >> t;
            adj[u].emplace(v, c, t);
        }
        result = INT_MAX;
    }

    void findKg(int currNode, int dist, int maxKgEdge, vector<bool>& visited, vector<pair<int, int>>& minRes) {
        if (minRes[currNode].first > dist && minRes[currNode].second > maxKgEdge) {
            minRes[currNode].first = dist;
            minRes[currNode].second = maxKgEdge;
        }
        
        if (minRes[currNode].first < dist && minRes[currNode].second < maxKgEdge) {
            return;
        }
        
        if (dist > maxTime) {
            return;
        }
        
        if (currNode == n - 1) {
            if (maxKgEdge < result) {
                result = maxKgEdge;
            }
            return;
        }
        if (visited[currNode]) {
            return;
        }
        visited[currNode] = true;
        
        for(auto it : adj[currNode]){
            if (it.kg > result) {
                continue;
            }
            
            int to = it.to; 
            int time = it.time;
            
            if (it.kg > maxKgEdge) {
                findKg(to, dist + time, it.kg, visited, minRes);
            }
            else {
                findKg(to, dist + time, maxKgEdge, visited, minRes);
            }
        }
        visited[currNode] = false;
    }

    void output() {
        vector<bool> visited(n, false);
        vector<pair<int, int>> minRes(n, {INT_MAX, INT_MAX});
        
        findKg(0, 0, 0, visited, minRes);
        if (result != INT_MAX) {
            cout << result << endl;
        }
        else cout << -1 << endl;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Graph gr;
    gr.output();
    
    return 0;
}
