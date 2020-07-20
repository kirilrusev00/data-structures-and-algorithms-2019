#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Interval {
    long long startIndex;
    long long maxIndex;
    long long maxValue;
    long long minIndex;
    long long minValue;
    
    Interval(long long index, long long value) {
        startIndex = index;
        maxIndex = index;
        maxValue = value;
        minIndex = index;
        minValue = value;
    }
};

long long sumIntervals(vector<long long> values, long long n, long long k) {
    long long sum = 0;
    Interval interval(0, values[0]);
    for (long long i = 0; i < n; i++) {
        while(interval.maxValue - interval.minValue <= k) {
            i++;
            if (i == n) {
                break;
            }
            if (values[i] > interval.maxValue) {
                interval.maxValue = values[i];
                interval.maxIndex = i;
            }
            if (values[i] < interval.minValue) {
                interval.minValue = values[i];
                interval.minIndex = i;
            }
        }
        long long lenOfInterval = i - interval.startIndex;
        long long startOfNextInterval = min(interval.minIndex, interval.maxIndex) + 1;
        sum += lenOfInterval * (lenOfInterval + 1) / 2;
        sum -= (i - startOfNextInterval) * (i - startOfNextInterval + 1) / 2;
        i = startOfNextInterval;
        interval.startIndex = i;
        interval.maxIndex = i;
        interval.maxValue = values[i];
        interval.minIndex = i;
        interval.minValue = values[i];
        i--;
    }
    return sum;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    long long n, k;
    cin >> n;
    cin >> k;
    vector<long long> a;
    for (long long i = 0; i < n; i++) {
        long long x;
        cin >> x;
        a.push_back(x);
    }
    cout << sumIntervals(a, n, k);
    
    return 0;
}
