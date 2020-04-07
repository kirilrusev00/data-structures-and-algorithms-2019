#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void mergeTwoParts(int* originalArray, int* mergeArray, int start, int mid, int end)
{
	int left = start;
	int right = mid + 1;

	for (int i = start; i <= end; i++)
	{
		if (left <= mid && (right > end || originalArray[left] <= originalArray[right]))
		{
			mergeArray[i] = originalArray[left];
			left++;
		}
		else
		{
			mergeArray[i] = originalArray[right];
			right++;
		}
	}
	for (int i = start; i <= end; i++)
	{
		originalArray[i] = mergeArray[i];
	}
}

void mergeRecursion(int* originalArray, int* mergeArray, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;

		mergeRecursion(originalArray, mergeArray, start, mid);
		mergeRecursion(originalArray, mergeArray, mid + 1, end);

		mergeTwoParts(originalArray, mergeArray, start, mid, end);
	}
}

void mergeSort(int* array, int length)
{
	int* mergeArray = new int[length];
	mergeRecursion(array, mergeArray, 0, length - 1);
	delete[] mergeArray;
}

void selectionSort(int* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < length; j++)
		{
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			int temp = array[minIndex];
			array[minIndex] = array[i];
			array[i] = temp;
		}
	}
}

//Each shot of the blaster should be at the furthest monster (the monster on maxPosition)
int minShots(int* posOfMonsters, int numMonsters, int powerOfShot)
{
	int counter = 0;
	for (int i = numMonsters - 1; i >= 0 && (posOfMonsters[i] - counter * powerOfShot) > 0;)
	{
		int posOfShot = posOfMonsters[i] - counter * powerOfShot;
		while (i >= 0 && (posOfMonsters[i] - counter * powerOfShot) == posOfShot)
		{
			posOfMonsters[i] = 0;//the monster is dead
			i--;
		}
		counter++;
	}
	return counter;
}

int main() {
	int n, x;
	cin >> n;
	cin >> x;
	int* s = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	mergeSort(s, n);
	cout << minShots(s, n, x) << endl;
	delete[] s;
	return 0;
}
