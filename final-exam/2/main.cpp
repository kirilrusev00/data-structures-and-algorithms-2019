#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int binary_search(vector<int>& arr, int left, int right, int k) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == k) {
			return mid;
		}
		if (arr[mid] > k) {
			return binary_search(arr, left, mid - 1, k);
		}
		if (arr[mid] < k) {
			return binary_search(arr, mid + 1, right, k);
		}
	}
	return left;
}

int main() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int q;
	cin >> q;
	vector<int> queries(q);
	for (int i = 0; i < q; i++) {
		cin >> queries[i];
	}

	//int already_added = 0;

	for (int i = 0; i < q; i++) {
		int ind = binary_search(arr, 0, n - 1, queries[i]);
		if (arr[ind] != queries[i]) {

			if (ind == n - 1 && arr[ind] < queries[i]) {
				cout << n << endl;
			}
			else if (ind == 0 && arr[ind] > queries[i]) {
				cout << 0 << endl;
			}
			else if (arr[ind] < queries[i] && arr[ind + 1] > queries[i]) {
				cout << ind + 1 << endl;
			}
			else if (arr[ind - 1] < queries[i] && arr[ind] > queries[i]) {
				cout << ind << endl;
			}
			else cout << ind << endl;
			//already_added ++;
			continue;
		}
		else {
			int first_ind = ind;
			int last_ind = ind;
			for (int j = ind - 1; j >= 0; j--) {
				if (arr[j] == queries[i]) {
					first_ind = j;
				}
				else break;
			}
			for (int j = ind + 1; j < n; j++) {
				if (arr[j] == queries[i]) {
					last_ind = j;
				}
				else break;
			}
			cout << first_ind << " " << last_ind;
			cout << endl;
		}

	}

	return 0;
}
