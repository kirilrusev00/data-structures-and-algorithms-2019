#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

class Apartment {
private:
    long long x;
    long long y;

public:
    Apartment(long long x, long long y) {
        this->x = x;
        this->y = y;
    }

    double distance() const {
        return sqrt(x * x + y * y);
    }

    bool operator<(const Apartment& rhs) const {
        if (this->distance() < rhs.distance()) {
            return true;
        }
        if (this->distance() == rhs.distance() && this->x < rhs.x) {
            return true;
        }
        if (this->distance() == rhs.distance() && this->x == rhs.x && this->y < rhs.y) {
            return true;
        }
        return false;
    }
    
    bool operator>(const Apartment& rhs) const {
        if (this->distance() > rhs.distance()) {
            return true;
        }
        if (this->distance() == rhs.distance() && this->x > rhs.x) {
            return true;
        }
        if (this->distance() == rhs.distance() && this->x == rhs.x && this->y > rhs.y) {
            return true;
        }
        return false;
    }
    
    friend ostream& operator<<(ostream& output, const Apartment& ap) {
        output << ap.x << " " << ap.y;
        return output;
    }
};

class MinHeap {
private:
    vector<Apartment> data;
    long long maxSize;

public:
    MinHeap(long long maxSize) {
        this->maxSize = maxSize;
    }

    void push(const long long& x, const long long& y) {
        if (size() < maxSize) {
            data.emplace_back(x, y);
            push_heap(data.begin(), data.end());
        }
        else if (Apartment(x, y) < peek()) {
            pop();
            data.emplace_back(x, y);
            push_heap(data.begin(), data.end());
        }
    }

    Apartment& peek() {
        return data.front();
    }
    
    void pop() {
        pop_heap(data.begin(), data.end());
        data.pop_back();
    }
    
    void print() {
        sort_heap(data.begin(), data.end(), less<Apartment>());
        for (long long i = 0; i < size(); i++) {
            cout << data[i] << endl;
        }
    }

    long long size() {
        return data.size();
    }

    bool empty() {
        return size() == 0;
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    long long n;
    long long k;
    cin >> n;
    cin >> k;
    MinHeap minHeap(k);
    for (long long i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        minHeap.push(x, y);
    }
    minHeap.print();

    return 0;
}
