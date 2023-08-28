#include <iostream>
#include <queue>
#include <set>
#define row first
#define col second
#define M 1'111

using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int L, m;		//    0
int dir = 1;	// 3     1
pii pos;		//    2
int len = 0;
int moveCnt = 0;
int ans = 0;

typedef struct path {
	pii pos;
	int t;
	int dir;
} path;
path snake[M];

const int dr[4] = { 1, 0, -1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

inline bool isBodyCrashed(int& t) {
	path cur = { pos, t, dir };
	pii curEnd = { pos.row + t * dr[dir], pos.col + t * dc[dir] };
	for (int i = 0; i < moveCnt; i++) {
		path check = snake[i];
		pii checkEnd = { check.pos.row + check.t * dr[check.dir], check.pos.col + check.t * dc[check.dir] };
		int checkMinRow = min(check.pos.row, checkEnd.row);
		int checkMaxRow = max(check.pos.row, checkEnd.row);
		int checkMinCol = min(check.pos.col, checkEnd.col);
		int checkMaxCol = max(check.pos.col, checkEnd.col);
		// ��ġ�� ������ �ִ��� Ȯ�� start
		if (check.dir % 2 == dir % 2) { // ������ ���� ��
			if (check.dir % 2) {		// - ���ι���
				if (check.pos.row != pos.row) return false;
				else if (check.pos.col <= curEnd.col && curEnd.col <= checkEnd.col) {
					if (dir == 1) ans += ll(t - (curEnd.col - checkMinCol - 1));
					else ans += ll(t - (checkMaxCol - curEnd.col));
					return true;
				}
			}
			else {						// - ���ι���
				if (check.pos.col != pos.col) return false;
				else if (check.pos.row <= curEnd.row && curEnd.row <= checkEnd.row) {
					if (dir == 0) ans += ll(t - (curEnd.row - checkMinRow - 1));
					else ans += ll(t - (checkMaxRow - curEnd.row));
					return true;
				}
			}
		}
		else {							// ������ �ٸ� ��
			if (check.dir % 2) {		// - ���� ���� ����� ����
				//int minColOfCheck = min(check.pos.col, checkEnd.col);
				//int maxColOfCheck = max(check.pos.col, checkEnd.col);
				//int minRowOfCur = min(cur.pos.row, curEnd.row);
				//int maxRowOfCur = max(cur.pos.row, curEnd.row);
				//if (minColOfCheck <= cur.pos.col && cur.pos.col <= maxColOfCheck
				//	&& minRowOfCur < check.pos.row && check.pos.row <= maxRowOfCur) {
				//	if (dir == 0) ans += ll(curEnd.row - check.pos.row - 1);
				//	else ans += ll(check.pos.row - curEnd.row - 1);
				//	return true;
				//}
			}
			else {						// - ���� ���� ����� ����
				//int minRowOfCheck = min(check.pos.col, checkEnd.col);
				//int maxRowOfCheck = max(check.pos.col, checkEnd.col);
				//int minColOfCur = min(cur.pos.row, curEnd.row);
				//int maxColOfCur = max(cur.pos.row, curEnd.row);
				//if (minRowOfCheck <= cur.pos.row && cur.pos.row <= maxRowOfCheck
				//	&& minColOfCur < check.pos.col && check.pos.col <= maxColOfCur) {
				//	if (dir == 1) ans += ll(curEnd.col - check.pos.col - 1);
				//	else ans += ll(check.pos.col - curEnd.col - 1);
				//	return true;
				//}
			}
		}
		// ��ġ�� ������ �ִ��� Ȯ�� end
	}
	return false;
}

inline void turnLeft() {
	dir = (dir + 3) % 4;
}

inline void turnRight() {
	dir = (dir + 1) % 4;
}

bool isSafe(int& t, char& d) {
	int nr = pos.row + t * dr[dir];
	int nc = pos.col + t * dc[dir];

	bool ret = 0 < nr && 0 < nc && nr <= len && nc <= len;
	if (!ret) {
		if (nr <= 0) ll(ans += t + nr + 1);
		else if (nc <= 0) ll(ans += t + nc + 1);
		else if (len < nr) ll(ans += t - (nr - len - 1));
		else if (len < nc) ll(ans += t - (nc - len - 1));
		return false;
	}
	ret = !isBodyCrashed(t);
	return ret;
}

int main() {
	cin >> L >> m;
	pos = pii{ L + 1, L + 1 };
	len = (L << 1) + 1;
	int t;
	char d;
	bool needCheck = true;

	for (; moveCnt < m; moveCnt++) {
		cin >> t >> d;
		if (needCheck && isSafe(t, d)) {
			snake[moveCnt] = { pos, t, dir };
			::ans += ll(t);

			pos = { pos.row + t * dr[dir], pos.col + t * dc[dir] };
			d == 'L' ? turnLeft() : turnRight();
		}
		else needCheck = false;
	}
	
	cout << ans;
}

/*
	queue�� time ���� �� ������.. MLE
	m �� 1000 ������ ���� �������.
*/