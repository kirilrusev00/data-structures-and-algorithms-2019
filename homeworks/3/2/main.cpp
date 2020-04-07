#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long findMaxDistance(vector<long long> dist, int length, int numOfCows)
{
	if (numOfCows == 2)
	{
		return dist[length - 1] - dist[0];
	}
	long long low = 1;
	long long high = (dist[length - 1] - dist[0]) / (numOfCows - 1) + 1;
	while (low < high)
	{
		long long mid = low + (high - low) / 2;
		int cowsToPlace = numOfCows - 2;
		long long distLastPutCow = dist[0];
		for (int i = 1; i < length - 1; i++)
		{
			if (dist[i] - distLastPutCow >= mid) {
				distLastPutCow = dist[i];
				cowsToPlace--;
				if (cowsToPlace == 0)
				{
					break;
				}
			}
			else
			{
				continue;
			}
		}
		if (cowsToPlace == 0 && dist[length - 1] - distLastPutCow >= mid)
		{
			low = mid + 1;
		}
		else
		{
			high = mid;
		}
	}
	return high - 1;
}

int main() {
	int n, k;
	cin >> n;
	cin >> k;
	vector<long long> dist;
	for (int i = 0; i < n; i++)
	{
		long long x;
		cin >> x;
		dist.push_back(x);
	}
	sort(dist.begin(), dist.end());
	//n=1 -> 0
	cout << findMaxDistance(dist, n, k);
	//delete[] dist;
	return 0;
}
