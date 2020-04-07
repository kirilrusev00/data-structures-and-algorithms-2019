#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long merge(int* arr, int temp[], int start, int middle, int end)
{
	long long countInversions = 0;
	int left = start, right = middle + 1, k = start;
	if (arr[middle] <= arr[middle + 1]) {
		return 0;
	}
	while (left <= middle && right <= end)
	{
		if (arr[left] <= arr[right])
		{
			temp[k] = arr[left];
			left++;
		}
		else
		{
			temp[k] = arr[right];
			right++;
			countInversions += (middle + 1) - left;
		}
		k++;
	}
	while (left <= middle)
	{
		temp[k] = arr[left];
		left++;
		k++;
	}
	while (right <= end)
	{
		temp[k] = arr[right];
		right++;
		k++;
	}
	for (int i = start; i <= end; i++)
	{
		arr[i] = temp[i];
	}
	return countInversions;
}

long long mergeRecursion(int* array, int mergeArray[], int left, int right)
{
	long long countInversions = 0;
	if (left < right)
	{
		int middle = (left + right) / 2;
		countInversions += mergeRecursion(array, mergeArray, left, middle);
		countInversions += mergeRecursion(array, mergeArray, middle + 1, right);
		countInversions += merge(array, mergeArray, left, middle, right);
	}
	return countInversions;
}

long long mergeSort(int* array, int length)
{
	int mergeArray[length];
	return mergeRecursion(array, mergeArray, 0, length - 1);
}

int main() {
	int n;
	cin >> n;
	int* h = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> h[i];
	}
	cout << mergeSort(h, n) << endl;
	delete[] h;
	return 0;
}
