#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Truck {
	long long place;//k
	long long monsters;//m
};

void merge(Truck* trucks, Truck* mergeTrucks, long long start, long long middle, long long end)
{
	long long left = start;
	long long right = middle + 1;
	long long k = start;
	while (left <= middle && right <= end)
	{
		if (trucks[left].place <= trucks[right].place)
		{
			mergeTrucks[k] = trucks[left];
			left++;
		}
		else
		{
			mergeTrucks[k] = trucks[right];
			right++;
		}
		k++;
	}
	while (left <= middle)
	{
		mergeTrucks[k++] = trucks[left++];
	}
	while (right <= end)
	{
		mergeTrucks[k++] = trucks[right++];
	}
	for (long long i = start; i <= end; i++)
	{
		trucks[i] = mergeTrucks[i];
	}
}

void mergeRecursion(Truck* trucks, Truck* mergeTrucks, long long left, long long right)
{
	if (left < right)
	{
		long long middle = left + (right - left) / 2;
		mergeRecursion(trucks, mergeTrucks, left, middle);
		mergeRecursion(trucks, mergeTrucks, middle + 1, right);
		merge(trucks, mergeTrucks, left, middle, right);
	}
}

void mergeSort(Truck* trucks, long long length)
{
	Truck* mergeTrucks = new Truck[length];
	mergeRecursion(trucks, mergeTrucks, 0, length - 1);
	delete[] mergeTrucks;
}

long long min_sum_monsters(Truck* trucks, long long length)
{

	long long leftAmountOfMonstersForOneCm = 0;
	long long rightAmountOfMonstersForOneCm = 0;

	long long minSum = 0;
	for (long long i = 1; i < length; i++)
	{
		rightAmountOfMonstersForOneCm += trucks[i].monsters;
		minSum += (trucks[i].place - trucks[0].place) * trucks[i].monsters;
	}

	long long sum = minSum;
	for (long long i = 1; i < length; i++)
	{
		leftAmountOfMonstersForOneCm += trucks[i - 1].monsters;
		sum += (trucks[i].place - trucks[i - 1].place) * leftAmountOfMonstersForOneCm;

		sum -= (trucks[i].place - trucks[i - 1].place) * rightAmountOfMonstersForOneCm;
		rightAmountOfMonstersForOneCm -= trucks[i].monsters;

		if (sum < minSum)
		{
			minSum = sum;
		}
	}
	return minSum;
}

int main() {
	long long n;
	cin >> n;
	Truck* trucks = new Truck[n];
	for (long long i = 0; i < n; i++)
	{
		cin >> trucks[i].place >> trucks[i].monsters;
	}
	mergeSort(trucks, n);
	cout << min_sum_monsters(trucks, n);

	delete[] trucks;
	return 0;
}