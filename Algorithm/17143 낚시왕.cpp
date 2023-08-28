#include <iostream>
#include <queue>

#define N 101

using namespace std;

typedef struct shark {
	int r, c, s, d, size;
	int idx;
	bool alive;
} shark;

shark arr[N][N] = {};
bool isSharkAlive[N * N];
shark sharkList[N * N];
int R, C, M;
int manIdx = 0;

int changeDir(int& dir) {
	return dir == 1 ? 2 : (dir == 2 ? 1 : (dir == 3 ? 4 : (dir == 4 ? 3 : 0)));
}

void move() {
	shark cur;
	shark bef;
	int distLeft = 0;
	for (int i = 1; i <= M; i++) {
		cur = sharkList[i];
		bef = cur;

		printf("\n [%d] BEFORE : (%d, %d) 속력: %d, 방향: %d, 사이즈: %d", cur.idx, cur.r, cur.c, cur.s, cur.d, cur.size);

		if (!cur.alive) continue;

		if (cur.d == 1)				// up
			distLeft = cur.r - 1;
		else if (cur.d == 2)		// down
			distLeft = ::R - cur.r;
		else if (cur.d == 3) 		// right
			distLeft = ::C - cur.c;
		else 						// left
			distLeft = cur.c - 1;

		if (cur.s <= distLeft) {	// direction fix
			if (cur.d < 3)
				cur.r = (cur.d == 1 ? cur.r - distLeft : cur.r + distLeft);
			else cur.c = (cur.d == 3 ? cur.c + distLeft : cur.c - distLeft);
			if (cur.d == 1 && cur.r == 1) cur.d = 2;
			else if (cur.d == 2 && cur.r == R) cur.d = 1;
			else if (cur.d == 3 && cur.c == C) cur.d = 4;
			else if (cur.d == 4 && cur.c == 1) cur.d = 3;
		}
		else {						// change direction to 2
			int moveLeft = cur.s - distLeft;
			cur.d = changeDir(cur.d);
			if (cur.d == 1) cur.r = R - moveLeft;
			else if (cur.d == 2) cur.r = moveLeft + 1;
			else if (cur.d == 3) cur.c = moveLeft + 1;
			else cur.c = C - moveLeft;
		}

		shark arrShark = arr[cur.r][cur.c];

		if (arrShark.size) {
			if (arrShark.size < cur.size) {
				sharkList[arrShark.idx].alive = false;
				arr[cur.r][cur.c] = cur;
				sharkList[cur.idx] = cur;
			}
			else sharkList[cur.idx].alive = false;
		}
		else arr[cur.c][cur.c] = cur;
		printf("\n [%d] AFTER : (%d, %d) 속력: %d, 방향: %d, 사이즈: %d", cur.idx, cur.r, cur.c, cur.s, cur.d, cur.size);
		arr[bef.r][bef.c].size = 0;
	}
}

int solve() { 
	int ret = 0;
	while (++::manIdx <= C) {
		for (int r = 1; r <= R; r++) {
			if (arr[r][::manIdx].size) {
				ret += arr[r][::manIdx].size;
				::sharkList[arr[r][::manIdx].idx].alive = false;
				arr[r][::manIdx].size = 0;
				break;
			}
		}
		move();
	}
	return ret;
}

int main() {
	cin >> R >> C >> M;
	memset(isSharkAlive, 1, sizeof(bool) * (M + 1));
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			arr[i][j].size = 0;
	int r, c, s, d, z;
	for (int i = 1; i <= M; i++) {
		cin >> r >> c >> s >> d >> z;
		s %= (d < 3 ? (R - 1) : (C - 1)) << 1;
		::sharkList[i] = shark{ r, c, s, d, z, i, true};
		::arr[r][c] = ::sharkList[i];
	}

	cout << solve();
}