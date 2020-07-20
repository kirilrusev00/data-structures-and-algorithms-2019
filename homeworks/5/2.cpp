#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

struct PlaceOfApple {
    int row;
    int column;
    int dist;

    PlaceOfApple(int row, int column, int dist = 0) {
        this->row = row;
        this->column = column;
        this->dist = dist;
    }
};

void rotApples(bool** isRotten, queue<PlaceOfApple> apples, int n, int m, int t) {
    if (n == 0 || m == 0) {
        return;
    }
    while (apples.front().dist < t) {
        PlaceOfApple frontApple = apples.front();
        if (frontApple.row > 0 && !isRotten[frontApple.row - 1][frontApple.column]) {
            PlaceOfApple nextApple(frontApple.row - 1, frontApple.column, frontApple.dist + 1);
            isRotten[frontApple.row - 1][frontApple.column] = true;
            apples.push(nextApple);
        }
        if (frontApple.row < n - 1 && !isRotten[frontApple.row + 1][frontApple.column]) {
            PlaceOfApple nextApple(frontApple.row + 1, frontApple.column, frontApple.dist + 1);
            isRotten[frontApple.row + 1][frontApple.column] = true;
            apples.push(nextApple);
        }
        if (frontApple.column > 0 && !isRotten[frontApple.row][frontApple.column - 1]) {
            PlaceOfApple nextApple(frontApple.row, frontApple.column - 1, frontApple.dist + 1);
            isRotten[frontApple.row][frontApple.column - 1] = true;
            apples.push(nextApple);
        }
        if (frontApple.column < m - 1 && !isRotten[frontApple.row][frontApple.column + 1]) {
            PlaceOfApple nextApple(frontApple.row, frontApple.column + 1, frontApple.dist + 1);
            isRotten[frontApple.row][frontApple.column + 1] = true;
            apples.push(nextApple);
        }
        apples.pop();
    }
}

long long getFreshApples(bool** isRotten, int n, int m) {
    long long counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!isRotten[i][j]) {
                counter++;
            }
        }
    }
    return counter;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, m, t;
    cin >> n;
    cin >> m;
    cin >> t;

    bool** isRotten = new bool* [n];
    for (int i = 0; i < n; i++) {
        isRotten[i] = new bool[m];
        for (int j = 0; j < m; j++) {
            isRotten[i][j] = false;
        }
    }
    
    int n1, m1;
    cin >> n1 >> m1;
    int n2 = -1, m2 = -1;
    cin >> n2 >> m2;
    queue<PlaceOfApple> rottenApples;
    //Rows are from 1 to n and columns from 1 to m
    if (n2 == -1 && m2 == -1) {
        PlaceOfApple apple1(n1 - 1, m1 - 1);
        isRotten[n1 - 1][m1 - 1] = true;
        rottenApples.push(apple1);
        rotApples(isRotten, rottenApples, n, m, t);
    }
    else {
        PlaceOfApple apple1(n1 - 1, m1 - 1);
        PlaceOfApple apple2(n2 - 1, m2 - 1);
        isRotten[n1 - 1][m1 - 1] = true;
        isRotten[n2 - 1][m2 - 1] = true;
        rottenApples.push(apple1);
        rottenApples.push(apple2);
        rotApples(isRotten, rottenApples, n, m, t);
    }
    cout << getFreshApples(isRotten, n, m);

    for (int i = 0; i < n; i++) {
        delete[] isRotten[i];
    }
    delete[] isRotten;

    return 0;
}
