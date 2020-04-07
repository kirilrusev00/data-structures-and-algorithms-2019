#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long maxWater(vector<int> wallsHeight)
{
	long result = 0;
	int len = wallsHeight.size();
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			long water = (j - i) * min(wallsHeight[i], wallsHeight[j]);
			if (water > result)
			{
				result = water;
			}
		}
	}
	return result;
}

int main() {
	int N;
	cin >> N;
	vector<int> walls;
	for (int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		walls.push_back(x);
	}
	cout << maxWater(walls) << endl;
	return 0;
}
