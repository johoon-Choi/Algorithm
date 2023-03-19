#include <iostream>
#include <vector>
#include <algorithm>

#define N 500'555

using namespace std;

vector<int> arr(N, 0);
vector<int> arr_sort;
vector<int> info;
int n;

int main() {
	cin >> n;
	arr_sort.assign(n + 1, 0);
	info.assign(n + 1, 0);
	for (int i = n; i; i--) {
		cin >> arr[i];
		arr_sort[i - 1] = arr[i];
	}
}