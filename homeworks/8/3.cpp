#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Place {
    int row;
    int column;
    int dist;
    Place* pred;

    Place(int row = -1, int column = -1, int dist = 0, Place* pred = nullptr) {
        this->row = row;
        this->column = column;
        this->dist = dist;
        this->pred = pred;
    }
    
    Place& operator=(const Place& rhs) {
        if(&rhs != this) {
            this->row = rhs.row;
            this->column = rhs.column;
            this->dist = rhs.dist;
            this->pred = rhs.pred;
        }
            
        return *this;
    }
    
    bool operator==(const Place& rhs) {
        return (this->row == rhs.row && this->column == rhs.column);
    }
};

class Graph {
private:
    int n; // rows
    int m; // columns
    
    Place start;
    Place finish;
    
    char** maze;
    bool** visited;
    
    void input() {
        cin >> n;
        cin >> m;
        
        maze = new char*[n];
        visited = new bool*[n];
        for (int i = 0; i < n; i++) {
            maze[i] = new char[m];
            visited[i] = new bool[m];
            
            for (int j = 0; j < m; j++) {
                char place;
                cin >> place;
                maze[i][j] = place;
                visited[i][j] = false;
                if (place == 'S') {
                    start = Place(i, j);
                }
                if (place == 'F') {
                    finish = Place(i, j);
                }
            }
        }
                
    }
public:
    Graph() {
        input();
    }
    
    int getShortestPath() {
        queue<Place> q;
        visited[start.row][start.column] = true;
        q.push(start);
        while(!q.empty()) {
            Place first = q.front();
            q.pop();
            //cout << first.row << " " << first.column << " " << first.dist << endl;
            if (first == finish) {
                return first.dist;
            }
            
            int row = first.row;
            int col = first.column;
            
            if (row > 0 && !visited[row - 1][col] && maze[row - 1][col] != '#') {
                visited[row - 1][col] = true;
                q.push(Place(row - 1, col, first.dist + 1, &first));
            }
            if (row < n - 1 && !visited[row + 1][col] && maze[row + 1][col] != '#') {
                visited[row + 1][col] = true;
                q.push(Place(row + 1, col, first.dist + 1, &first));
            }
            if (col > 0 && !visited[row][col - 1] && maze[row][col - 1] != '#') {
                visited[row][col - 1] = true;
                q.push(Place(row, col - 1, first.dist + 1, &first));
            }
            if (col < m - 1 && !visited[row][col + 1] && maze[row][col + 1] != '#') {
                visited[row][col + 1] = true;
                q.push(Place(row, col + 1, first.dist + 1, &first));
            }
            
            if ((first.pred != nullptr && row == first.pred->row) || first.pred == nullptr) {
                for (int i = row - 1; i >= 0; i--) {
                    if (maze[i][col] == '#') {
                        if (i != row - 1 && !visited[i + 1][col]) {
                            visited[i + 1][col] = true;
                            q.push(Place(i + 1, col, first.dist + 1, &first));
                        }
                        break;
                    }
                }
                for (int i = row + 1; i < n; i++) {
                    if (maze[i][col] == '#') {
                        if (i != row + 1 && !visited[i - 1][col]) {
                            visited[i - 1][col] = true;
                            q.push(Place(i - 1, col, first.dist + 1, &first));
                        }
                        break;
                    }
                }
            }
            if ((first.pred != nullptr && col == first.pred->column) || first.pred == nullptr) {
                for (int i = col - 1; i >=0; i--) {
                    if (maze[row][i] == '#') {
                        if (i != col - 1 && !visited[row][i + 1]) {
                            visited[row][i + 1] = true;
                            q.push(Place(row, i + 1, first.dist + 1, &first));
                        }
                        break;
                    }
                }
                for (int i = col + 1; i < m; i++) {
                    if (maze[row][i] == '#') {
                        if (i != col + 1 && !visited[row][i - 1]) {
                            visited[row][i - 1] = true;
                            q.push(Place(row, i - 1, first.dist + 1, &first));
                        }
                        break;
                    }
                }
            }
        }
        return -1;
    }
    
    
};

int main() {
    Graph gr;
    cout << gr.getShortestPath();
    return 0;
}
