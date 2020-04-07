#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string encodePassword(const string& pass)
{
	int len = pass.length();
	string result;
	char letter = pass[0];
	int counter = 1;
	for (int i = 1; i < len; i++)
	{
		if (pass[i] == pass[i - 1])
		{
			counter++;
		}
		else
		{
			result += to_string(counter);
			result += letter;
			counter = 1;
			letter = pass[i];
		}
	}
	result += to_string(counter);
	result += letter;
	return result;
}

int main() {
	string str;
	cin >> str;
	cout << encodePassword(str) << endl;
	return 0;
}
