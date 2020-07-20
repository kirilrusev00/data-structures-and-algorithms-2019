#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

template <typename T = less<unsigned int>>
struct heap {
    vector<unsigned int> data;
    
    void push(const unsigned int& newValue) {
        data.push_back(newValue);
        push_heap(data.begin(), data.end(), T{});
    }
    
    unsigned int pop() {
        pop_heap(data.begin(), data.end(), T{});
        int last = data.back();
        data.pop_back();
        return last;
    }
    
    unsigned int top() {
        return data.front();
    }
    
    unsigned int size() {
        return data.size();
    }
    
    bool empty() {
        return size() == 0;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int n;
    cin >> n;
    
    heap<less<unsigned int>> minHeap;
    heap<greater<unsigned int>> maxHeap;
    
    for (int i = 0; i < n; i++) {
        unsigned int a;
        cin >> a;
        
        double median;
        
        if (minHeap.empty() || a <= minHeap.top()) {
            minHeap.push(a);
            while (minHeap.size() > maxHeap.size() + 1) {
                unsigned int popValue = minHeap.pop();
                maxHeap.push(popValue);
            }
        }
        else {
            maxHeap.push(a);
            while (maxHeap.size() > minHeap.size() + 1) {
                unsigned int popValue = maxHeap.pop();
                minHeap.push(popValue);
            }
        }
        
        if (maxHeap.size() == minHeap.size()) {
            median = (maxHeap.top() + minHeap.top()) / 2.0;
        }
        else if (maxHeap.size() < minHeap.size()){
            median = minHeap.top();
        } else median = maxHeap.top();
        
        printf("%.1lf\n", median);
    }
    
    
    return 0;
}
