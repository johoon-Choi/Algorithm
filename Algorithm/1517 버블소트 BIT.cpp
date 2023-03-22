#include <iostream>
#include <vector>
#include <algorithm>

#define N 500'555

using namespace std;
typedef long long ll;

struct Array {
	int val;
	int rank;
};

struct s {
	int val;
	int idx;
};

bool comp(s& a, s& b) {
	if (a.val != b.val)
		return a.val < b.val;
	else return a.idx < b.idx;
}

vector<Array> arr(N, { 0, 0 });
vector<s> arr_sort;
ll tree[N];
int n;

ll sum(int idx) {
	ll ret = 0;

	while (idx) {
		ret += tree[idx];
		idx -= (idx & -idx);
	}
	return ret;
}

void update(int idx) {
	while (idx <= n) {
		tree[idx]++;
		idx += (idx & -idx);
	}
}

ll solve() {
	ll ans = 0;

	for (int i = 1; i <= n; i++) {
		update(arr[i].rank);
		ans += sum(arr[i].rank - 1);
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	arr_sort.assign(n, { 0, 0 });

	for (int i = n; i; i--) {
		cin >> arr[i].val;
		arr_sort[i - 1] = { arr[i].val, i };
	}

	sort(arr_sort.begin(), arr_sort.end(), comp);

	int diff = 0;
	int curValue = arr_sort[0].val;

	for (int i = 0; i < n; i++) {
		if (i) {
			if (curValue == arr_sort[i].val) diff++;
			curValue = arr_sort[i].val;
		}

		arr[arr_sort[i].idx].rank = i + 1 - diff;
	}

	cout << solve();
}


/*
 *	5 3 2 9 8 3 4
 *          ^
 *     보다 작은게 왼쪽에 몇 개 있는지
 */