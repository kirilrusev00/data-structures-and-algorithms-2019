#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Day {
	long long requestedBalloons;
	long long candyCost;
	long long maxUsedCandies;
};

long long getMostCandies(Day* days, const long long& length, long long& numBalloons)
{
	long long low = 0;
	long long high = 0;
	for (long long i = 0; i < length; i++)
	{
		if (days[i].maxUsedCandies > high)
		{
			high = days[i].maxUsedCandies;
		}
	}
	while (low <= high)
	{
		long long mid = low + (high - low) / 2;
		long long usedBalloons = numBalloons;
		for (long long i = 0; i < length; i++)
		{
			if (days[i].maxUsedCandies <= mid) {
				continue;
			}
			else
			{
				long long subtract = days[i].maxUsedCandies - mid;
				long long balloonsToUse;
				if (days[i].candyCost == 0)
				{
					continue;
				}
				else balloonsToUse = subtract / days[i].candyCost;
				if (balloonsToUse * days[i].candyCost != subtract)
				{
					balloonsToUse++;
				}
				usedBalloons -= balloonsToUse;
			}
		}
		if (usedBalloons >= 0)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}
	return low;
}

int main() {
	long long n;
	long long m;
	cin >> n >> m;
	Day* days = new Day[n];
	for (long long i = 0; i < n; i++)
	{
		cin >> days[i].requestedBalloons;
	}
	for (long long i = 0; i < n; i++)
	{
		cin >> days[i].candyCost;
		days[i].maxUsedCandies = days[i].requestedBalloons * days[i].candyCost;
	}
	cout << getMostCandies(days, n, m);
	delete[] days;
	return 0;
}
