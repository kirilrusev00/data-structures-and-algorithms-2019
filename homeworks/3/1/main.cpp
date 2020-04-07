#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Cup {
	long long firstInd;
	long long lastInd;
};

void limits_cups(Cup* cups, long long* numberOfStrawberriesInCups, long long numberOfCups)
{
	long long sum = 1;
	for (long long i = 0; i < numberOfCups; i++)
	{
		cups[i].firstInd = sum;
		//cout << cups[i].firstInd << " ";
		sum += numberOfStrawberriesInCups[i] - 1;
		cups[i].lastInd = sum;
		//cout << cups[i].lastInd << endl;
		sum++;
	}
}

long long binary_search(Cup* cups, long long left, long long right, long long x)
{
	if (right >= left)
	{
		long long middle = left + (right - left) / 2;
		if (cups[middle].firstInd <= x && cups[middle].lastInd >= x)
		{
			return middle + 1;
		}
		if (cups[middle].lastInd < x)
		{
			return binary_search(cups, middle + 1, right, x);
		}
		else return binary_search(cups, 0, middle - 1, x);
	}
	return -1;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	long long n, m;
	cin >> n;
	long long* a = new long long[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cin >> m;
	long long* q = new long long[m];
	for (long long i = 0; i < m; i++)
	{
		cin >> q[i];
	}
	Cup* cups = new Cup[n];

	limits_cups(cups, a, n);
	long long* results = new long long[m];
	for (long long i = 0; i < m; i++)
	{
		results[i] = binary_search(cups, 0, n - 1, q[i]);
		cout << results[i] << endl;
	}

	delete[] a;
	delete[] q;
	delete[] results;
	return 0;
}
