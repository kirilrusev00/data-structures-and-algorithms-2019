#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string canIvanPass(vector<long> grades, long passGrade)
{
	long sum = 0;
	long gradeIvan = 0;
	int len = grades.size();
	for (int i = 0; i < len; i++)
	{
		if (grades[i] < 0)
		{
			gradeIvan = grades[i];
		}
		else
		{
			sum = sum + (grades[i] - passGrade);
		}
	}
	long passIvan = passGrade - gradeIvan;
	if (sum >= passIvan)
	{
		return "yes";
	}
	else
	{
		return "no";
	}
}

int main() {
	long M;
	int N;
	cin >> M;
	cin >> N;
	vector<long> grades;
	for (int i = 0; i < N; i++)
	{
		long x;
		cin >> x;
		grades.push_back(x);
	}
	cout << canIvanPass(grades, M) << endl;
	return 0;
}
