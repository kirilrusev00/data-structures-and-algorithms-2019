#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int n;
    cin >> n;
    unordered_map<int, int> map;
    
    int* a = new int[n - 1];
    for (auto i = 0; i < n - 1; i++) {
        cin >> a[i];
    }
    
    int counter = 0;
    for (auto i = 0; i < n - 1; i++) {
        unordered_map<int, int>::iterator it = map.find(a[i]);
        if (it == map.end()) {
            map.emplace(a[i], 1);
        }
        else {
            it->second++;
        }
        int b;
        cin >> b;
        it = map.find(b);
        if (it == map.end()) {
            map.emplace(b, 0);
            counter++;
        }
        else {
            it->second--;
            if (it->second < 0) {
                it->second = 0;
                counter++;
            }
        }
    }
    
    cout << counter;
    
    return 0;
}
