#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Row
{
	long int copies;
	long int originals;
};

bool check(Row num)
{
	if (num.originals == 1 && num.copies == 0)
	{
		return true;
	}
	if (num.originals <= 1)
	{
		return false;
	}
	if (num.copies % 2 == 1 && num.originals % 2 == 0 && (num.originals - num.copies) <= 1)
	{
		return true;
	}
	if (num.copies % 2 == 0 && num.originals % 2 == 1 && (num.originals - num.copies) <= 1)
	{
		return true;
	}
	return false;
}

int main() {
	int T;
	cin >> T;
	vector<Row> numbers;
	for (int i = 0; i < T; i++)
	{
		long int N, M;
		cin >> N;
		cin >> M;
		Row input;
		input.copies = N;
		input.originals = M;
		numbers.push_back(input);
	}
	for (int i = 0; i < T; i++)
	{
		if (check(numbers[i]) == true)
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}
	return 0;
}
