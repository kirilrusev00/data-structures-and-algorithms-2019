#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

/*
 * For the weighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
 *
 */

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

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {
    int g_edges = g_from.size();
    vector<Edge> edges(g_edges);
    //vector<Edge> subtree(g_nodes);
    int total = 0;
    
    /*int max_vertex = 0;
    for (int i = 0; i < g_nodes; i++) {
        if (g_from[i] > max_vertex) {
            max_vertex = g_from[i];
        }
        if (g_to[i] > max_vertex) {
            max_vertex = g_to[i];
        }
    }*/
    vector<int> parent(g_nodes);
    for (int i = 0; i < g_nodes; i++) {
        parent[i] = i;
    }
    
    for (int i = 0; i < g_edges; i++) {
        edges[i] = Edge(g_from[i] - 1, g_to[i] - 1, g_weight[i]);
    }
    
    sort(edges.begin(), edges.end());
    
    for(Edge edge : edges) {
        if (parent[edge.from] != parent[edge.to]) {
            total += edge.weight;
            //subtree.push_back(edge);
            
            int old_parent = parent[edge.from];
            int new_parent = parent[edge.to];
            
            for (int i = 0; i < g_nodes; i++) {
                if (parent[i] == old_parent) {
                    parent[i] = new_parent;
                }
            }
        }
    }
    
    return total;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    // Write your code here.
    fout << res << endl;

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
