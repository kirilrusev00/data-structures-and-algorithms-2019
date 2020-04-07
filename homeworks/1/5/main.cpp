#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int oneThrow(int points)
{
	if (points == 50 || (points % 2 == 0 && points / 2 >= 1 && points / 2 <= 20))
	{
		return 1;
	}
	return 0;
}

int twoThrows(int points)
{
	int counter = 0;
	if (oneThrow(points - 0) == 1)
	{
		counter++;
	}
	if (oneThrow(points - 25) == 1)
	{
		counter++;
	}
	if (oneThrow(points - 50) == 1)
	{
		counter++;
	}
	for (int i = 1; i <= 20; i++)
	{
		if (oneThrow(points - i) == 1)
		{
			counter++;
		}
		if (oneThrow(points - i * 2) == 1)
		{
			counter++;
		}
		if (oneThrow(points - i * 3) == 1)
		{
			counter++;
		}
	}
	return counter;
}

int threeThrows(int points)
{
	int counter = 0;
	counter += twoThrows(points - 0);
	counter += twoThrows(points - 25);
	counter += twoThrows(points - 50);
	for (int i = 1; i <= 20; i++)
	{
		counter += twoThrows(points - i);
		counter += twoThrows(points - i * 2);
		counter += twoThrows(points - i * 3);
	}
	return counter;
}

int main() {
	int num;
	cin >> num;
	cout << oneThrow(num) + twoThrows(num) + threeThrows(num) << endl;
	return 0;
}
