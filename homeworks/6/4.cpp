#include <bits/stdc++.h>
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> students;
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        students.push_back(x);
    }
    
    vector<pair<int, int>> stops;
    
    for (int i = 0; i < m; i++) {
        int position, time;
        cin >> position >> time;
        int intervalOfStopStart = position - time;
        int intervalOfStopEnd = position + time;
        stops.emplace_back(intervalOfStopStart, intervalOfStopEnd);
    }
    
    sort(students.begin(), students.end());
    sort(stops.begin(), stops.end());
    
    priority_queue<int, vector<int>, greater<int>> queue;
    int j = 0;
    int counter = 0;
    
    for (int i = 0; i < n; i++) {
        while (j < m && students[i] >= stops[j].first) {
            queue.push(stops[j].second);
            j++;
        }
        
        while(!queue.empty() && queue.top() < students[i]) {
            queue.pop();
        }
        
        if (!queue.empty()) {
            queue.pop();
            counter++;
        }
    }
    
    cout << counter;
    
    return 0;
}
