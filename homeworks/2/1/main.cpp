#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void isPermutation(const string& word1, const string& word2, const int& length)
{
	int countLetters[26];
	for (int i = 0; i < 26; i++)
	{
		countLetters[i] = 0;
	}
	for (int i = 0; i < length; i++)
	{
		int intLetterInWord1 = (int)word1[i];
		int intLetterInWord2 = (int)word2[i];

		if (intLetterInWord1 != intLetterInWord2)
		{
			countLetters[intLetterInWord1 - 97]++;
			countLetters[intLetterInWord2 - 97]--;
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (countLetters[i] != 0)
		{
			cout << "no" << endl;
			return;
		}
	}
	cout << "yes" << endl;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	int n;
	string word1, word2;
	cin >> n;
	cin >> word1;
	cin >> word2;
	isPermutation(word1, word2, n);
	return 0;
}