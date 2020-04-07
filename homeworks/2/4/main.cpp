#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void merge(int* originalArray, int* mergeArray, int* otherArray, int* mergeOtherArray, int start, int middle, int end)
{
	int left = start;
	int right = middle + 1;
	int k = start;
	while (left <= middle && right <= end)
	{
		if (originalArray[left] <= originalArray[right])
		{
			mergeArray[k] = originalArray[left];
			mergeOtherArray[k] = otherArray[left];
			left++;
		}
		else
		{
			mergeArray[k] = originalArray[right];
			mergeOtherArray[k] = otherArray[right];
			right++;
		}
		k++;
	}
	while (left <= middle)
	{
		mergeArray[k] = originalArray[left];
		mergeOtherArray[k] = otherArray[left];
		left++;
		k++;
	}
	while (right <= end)
	{
		mergeArray[k] = originalArray[right];
		mergeOtherArray[k] = otherArray[right];
		right++;
		k++;
	}
	for (int i = start; i <= end; i++)
	{
		originalArray[i] = mergeArray[i];
		otherArray[i] = mergeOtherArray[i];
	}
}

void mergeRecursion(int* originalArray, int* mergeArray, int* otherArray, int* mergeOtherArray, int left, int right)
{
	if (left < right)
	{
		int middle = (left + right) / 2;
		mergeRecursion(originalArray, mergeArray, otherArray, mergeOtherArray, left, middle);
		mergeRecursion(originalArray, mergeArray, otherArray, mergeOtherArray, middle + 1, right);
		merge(originalArray, mergeArray, otherArray, mergeOtherArray, left, middle, right);
	}
}

void mergeSort(int* originalArray, int* otherArray, int length)
{
	int* mergeArray = new int[length];
	int* mergeOtherArray = new int[length];
	mergeRecursion(originalArray, mergeArray, otherArray, mergeOtherArray, 0, length - 1);
	delete[] mergeArray;
	delete[] mergeOtherArray;
}

int maxEvents(int* beginEvent, int* endEvent, int numEvents)
{
	int visitedEvents = 0;
	int currentTime = 0;
	for (int i = 0; i < numEvents; i++)
	{
		if (currentTime <= beginEvent[i])
		{
			visitedEvents++;
			currentTime = endEvent[i];
		}
	}
	return visitedEvents;
}

int main() {
	int n;
	cin >> n;
	int* b = new int[n];
	int* t = new int[n];
	int* endEvent = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> b[i] >> t[i];
		endEvent[i] = b[i] + t[i];
	}
	mergeSort(endEvent, b, n);
	cout << maxEvents(b, endEvent, n);
	delete[] b;
	delete[] t;
	return 0;
}
