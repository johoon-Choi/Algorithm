#include <iostream>
#include <vector>
#include <algorithm>

#define N 75'011
#define x first
#define y second

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

bool compx(pii& a, pii& b) {
	return a.x < b.x;
}

bool compy(pii& a, pii& b) {
	return a.y < b.y;
}

vvi tree;
vvi arr2;
vpii arr;
int tc, n;
int xidx;
int yidx;

int sum(const int& sx, const int& sy) {
	int xidx = sx;
	int yidx = sy;
	int ans = tree[sx][sy];
	xidx -= (xidx & -xidx);
	yidx -= (yidx & -yidx);
	while (xidx) {
		ans += tree[xidx][sy];
		xidx -= (xidx & -xidx);
	}
	while (yidx) {
		ans += tree[sx][yidx];
		yidx -= (yidx & -yidx);
	}
	if (ans) ans--;
	return ans;
}

void updateY(int xidx, int yidx) {
	while (yidx <= ::yidx) {
		tree[xidx][yidx]++;
		yidx += (yidx & -yidx);
	}
}

void update(int xidx, int yidx) {
	while (xidx <= ::xidx) {
		updateY(xidx, yidx);
		xidx += (xidx & -xidx);
	}
}

void init() {
	for (int i = 1; i <= xidx; i++) {
		for (int j = 1; j <= yidx; j++) {
			if (arr2[i][j])
				update(i, j);
		}
	}
}

int solve() {
	int ans = 0;
	
	init();

	for (int i = ::xidx; 0 < i; i--) {
		for (int j = 1; j <= ::yidx; j++) {
			ans += sum(i, j);
		}
	}

	//cout << "arr2" << '\n';
	//for (int i = ::yidx; 0 < i; i--) {
	//	for (int j = 1; j <= ::xidx; j++) {
	//		cout << arr2[j][i] << ' ';
	//	} cout << '\n';
	//}

	//cout << "tree" << '\n';
	//for (int i = ::yidx; 0 < i; i--) {
	//	for (int j = 1; j <= ::xidx; j++) {
	//		cout << tree[j][i] << ' ';
	//	} cout << '\n';
	//}

	return ans;
}

int main() {
	cin >> tc;
	int xinput, yinput;
	while (tc--) {
		arr.clear();
		arr.resize(0);

		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> xinput >> yinput;
			arr.push_back(pii{ xinput, yinput });
		}

		sort(arr.begin(), arr.end(), compx);

		int befx = arr[0].x;
		::xidx = 1;
		arr[0].x = 1;

		for (int i = 1; i < n; i++) {
			int curx = arr[i].x;

			if (befx != curx) {
				befx = curx;	// update
				xidx++;			// idx++
			}

			arr[i].x = xidx;
		}

		sort(arr.begin(), arr.end(), compy);

		int befy = arr[0].y;
		::yidx = 1;
		arr[0].y = 1;

		for (int i = 1; i < n; i++) {
			int cury = arr[i].y;

			if (befy != cury) {
				befy = cury;
				yidx++;
			}

			arr[i].y = yidx;
		}

		// 좌우로
		for (int i = 0; i < n; i++)
			arr[i].x = xidx + 1 - arr[i].x; 

		arr2.clear();
		tree.clear();
		arr2.assign(xidx + 1, vi(yidx + 1, 0));
		tree.assign(xidx + 1, vi(yidx + 1, 0));

		for (int i = 0; i < n; i++)
			arr2[arr[i].x][arr[i].y] = 1;

		// 2차원 arr2 가 정의 되어있다.

		cout << solve() << '\n';
	}
}