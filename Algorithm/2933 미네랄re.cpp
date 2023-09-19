#include <iostream>
#include <queue>
#include <stack>

#define MAX_RC 101
#define MAX_ATTACK 100
#define MINERAL 'x'
#define MOVED_MINERAL '*'
#define AIR '.'

using namespace std;

typedef struct pos {
	int r, c;
};

typedef struct dropPos {
	int r, c;
	int cnt;
};

int R, C, attackCnt;
int groupNum = 1;
int turn = 1;
char arr[MAX_RC][MAX_RC];
int arrGroup[MAX_RC][MAX_RC];
int attack[MAX_ATTACK];

void PRINT(string title) {
	cout << " ### " << title << " ###\n";
	for (int i = R; i; i--) {
		for (int j = 1; j <= C; j++)
			cout << arr[i][j];
		cout << '\n';
	}
}

const int dr[4] = { 0, 0, 1, -1 };
const int dc[4] = { 1, -1, 0, 0 };

bool isSafe(int r, int c) {
	return r && c && r <= R && c <= C;
}

void init() {
	cin >> R >> C;
	string row;
	for (int r = R; r; r--) {
		cin >> row;
		for (int c = 1; c <= C; c++) {
			arr[r][c] = row[c - 1];
			if (arr[r][c] == MINERAL)
				arrGroup[r][c] = 1;
		}
	}
	cin >> attackCnt;
	for (int i = 0; i < attackCnt; i++)
		cin >> attack[i];
}

bool visit[MAX_RC][MAX_RC];

bool setAreaAndIsItGround(int r, int c, int gnum) {
	bool ret = false;
	queue<pos> q;
	q.push({ r, c });
	arrGroup[r][c] = gnum;
	visit[r][c] = true;
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		if (cur.r == 1) ret = true;
		for (int d = 0; d < 4; d++) {
			int nr = cur.r + dr[d];
			int nc = cur.c + dc[d];
			if (isSafe(nr, nc) && !visit[nr][nc] && arr[nr][nc] == MINERAL) {
				q.push({ nr, nc });
				arrGroup[nr][nc] = gnum;
				visit[nr][nc] = true;
			}
		}
	}
	return ret;
}

// 만약 현재 클러스터가 떠있게 된다면, target으로부터의 direction을 return 한다.
int findOverMineral(pos target) {
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			visit[i][j] = false;

	int ret = -1;

	for (int d = 0; d < 4; d++) {
		int nr = target.r + dr[d];
		int nc = target.c + dc[d];
		if (isSafe(nr, nc) && !visit[nr][nc] && arr[nr][nc] == MINERAL) {
			if (!setAreaAndIsItGround(nr, nc, ++::groupNum)) {
				ret = d; // 하늘에 떠 있다.
				break;
			}
		}
	}

	return ret;
}

void letsDrop() {
	queue<dropPos> q;
	int dropCnt = 0;
	bool dropFinish = false;

	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			if (arrGroup[r][c] == ::groupNum)
				q.push({ r, c, dropCnt });
		}
	}

	// {sr, sc}가 포함된 클러스터를 떨어뜨려야 한다.
	while (!dropFinish) {
		while (dropCnt == q.front().cnt) {
			dropPos cur = q.front(); q.pop();
			arr[cur.r - 1][cur.c] = MOVED_MINERAL;
			arr[cur.r][cur.c] = AIR;

			if (cur.r == 2 || arr[cur.r - 2][cur.c] == MINERAL)
				dropFinish = true;

			q.push({ cur.r - 1, cur.c, cur.cnt + 1 });
		} dropCnt++;
	}

	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			if (arr[i][j] == MOVED_MINERAL)
				arr[i][j] = MINERAL;
}

void match() {
	for (int cnt = 0; cnt < attackCnt; cnt++) {
		int attackRow = attack[cnt];

		pos target = { 0, 0 };
		bool isLeftTurn = !(cnt & 1);
		for (int c = 1; c <= C; c++) {
			int curC = (isLeftTurn ? c : C + 1 - c);
			if (arr[attackRow][curC] == MINERAL) {
				target = { attackRow, curC };
				arr[attackRow][curC] = AIR;
				break;
			}
		}

		// 파괴되는 미네랄이 있는 경우
		if (target.r) {
			int dir = findOverMineral(target);
			if (0 <= dir) {
				letsDrop();
			}
		}
		// 없는 경우는 아무 일도 일어나지 않았다..
	}
}

int main() {
	init();
	match();

	for (int i = R; i; i--) {
		for (int j = 1; j <= C; j++)
			cout << arr[i][j];
		cout << '\n';
	}
}