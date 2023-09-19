#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>

#define MAX_RC 101
#define MAX_N 100

#define MINERAL 'x'

using namespace std;

char arr[MAX_RC][MAX_RC];
int iarr[MAX_RC][MAX_RC];
int R, C, n;

const int dr[4] = { 0, 0, 1, -1 };
const int dc[4] = { 1, -1 , 0, 0};

bool isSafe(int r, int c) {
	return r && c && r <= R && c <= C;
}

typedef struct pos {
	int r, c;
} pos;

typedef struct dropPos {
	int r, c;
	int cnt;
} dropPos;

bool visit[MAX_RC][MAX_RC];
int areaNum = 1;
queue<pos> q;

bool setArea(int sr, int sc, int num) {
	visit[sr][sc] = true;
	iarr[sr][sc] = num;
	q.push({ sr, sc });
	
	bool ret = false;

	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		if (cur.r == 1) ret = true;

		for (int d = 0; d < 4; d++) {
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];

			if (isSafe(nr, nc) && !visit[nr][nc] && arr[nr][nc] == MINERAL) {
				q.push({ nr, nc });
				iarr[nr][nc] = num;
				visit[nr][nc] = true;
			}
		}
	}

	return ret;
}

void init() {
	//for (int i = 1; i <= R; i++) {
	//	for (int j = 1; j <= C; j++) {
	//		if (arr[i][j] == MINERAL && !visit[i][j]) {
	//			setArea(i, j, ::areaNum++);
	//			break;
	//		}
	//	}
	//}
}

void letsDrop(int tarGroup) {
	queue<dropPos> q;

	// 아래부터 떨어지게끔 q에 삽입
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (iarr[i][j] == tarGroup) {
				q.push({ i, j, 0 });
			}
		}
	}

	int curDropCnt = 0;
	bool dropFinish = false;
	int changedGroup = tarGroup;
	dropPos cur = q.front();
 	while (!dropFinish) {
		while (curDropCnt == q.front().cnt) {
			cur = q.front(); q.pop();
			iarr[cur.r][cur.c] = 0;
			arr[cur.r][cur.c] = '.';
			iarr[cur.r - 1][cur.c] = tarGroup;
			arr[cur.c][cur.c] = MINERAL;
			if (cur.r - 2 == 1 || iarr[cur.r - 2][cur.c] != 0) {
				dropFinish = true;
				if (iarr[cur.r - 2][cur.c] != 0)
					changedGroup = iarr[cur.r - 2][cur.c];
			}
			q.push({ cur.r, cur.c, cur.cnt + 1 });
		} curDropCnt++;
	}
	if (changedGroup != tarGroup) {

	}
}

void solve(int attackRow, bool isLeftTurn) {
	pos target = { 0, 0 };
	for (int c = 1; c <= C; c++) {
		if ((isLeftTurn ? arr[attackRow][c] : arr[attackRow][C + 1 - c]) == MINERAL) {
			target = { attackRow, c };
			break;
		}
	}

	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			iarr[i][j] = 0;

	vector<int> isGround;
	vector<int> overGround;
	int groundCnt = 0;

	int num = 0;

	if (target.r) {
		arr[target.r][target.c] = '.';
		// target 블럭이 없어지면서, 네 방향을 조사한다.
		for (int d = 0; d < 4; d++) {
			int nr = target.r + dr[d];
			int nc = target.c + dc[d];

			// 미네랄이면서, 아직 방문하지 않은 미네랄 인 경우
			if (isSafe(nr, nc) && arr[nr][nc] == MINERAL && !iarr[nr][nc]) {
				if (setArea(nr, nc, ++num))
					isGround.push_back(num);
				else overGround.push_back(num);
			}
		}
	}

	cout << "\n\n before\n";
	for (int i = R; i; i--) {
		for (int j = 1; j <= C; j++) {
			cout << setw(3) << iarr[i][j];
		} cout << '\n';
	}

	if (overGround.size()) {	// 떨어질 Mineral 존재함
								// -> 떨어져야 하는 미네랄 블록 번호가 들어있다. (iarr 과 매핑)
		for (int i = 0; i < overGround.size(); i++) {
			letsDrop(overGround[i]);
		}
	}

	cout << "\n\n afgter\n";
	for (int i = R; i; i--) {
		for (int j = 1; j <= C; j++) {
			cout << setw(3) << iarr[i][j];
		} cout << '\n';
	}
}

int main() {
	cin >> R >> C;
	string row;
	for (int i = R; i; i--) {
		cin >> row;
		for (int j = 0; j < C; j++) {
			arr[i][j + 1] = row[j];
		}
	}

	init();

	cin >> n; 
	int input;
	bool isLeftTurn = true;
	for (int i = 1; i <= n; i++) {
		cin >> input;
		solve(input, isLeftTurn);
		isLeftTurn != isLeftTurn;
	}
}