#include <iostream>
#include <iomanip>
#include <vector>
#include <set>

#define MAX_N 22
#define EMPTY 0
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define NEED_CHECK 5

using namespace std;

typedef struct pos {
	int r, c;
} pos;

typedef struct fan {
	int r, c;
	int dir;
} fan;

const pos windDir[5] = { {0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
const pos sideWindDir[5] = { {0, 0}, {1, 1}, {1, -1}, {-1, 1}, {1, 1} };
const pos sideWindMul[5] = { {0, 0}, {-1, 1}, {-1, 1}, {1, -1}, {1, -1} };

const int dr[4] = { 1, 0, -1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

int map[MAX_N][MAX_N];
int tempValue[MAX_N][MAX_N];

int R, C, tar;
int ans = 0;

vector<pos> checkList;
vector<fan> fanList;
bool hasWall[4][MAX_N][MAX_N];
// hasWall[0][r][c] : (r, c)칸 아래에 벽이 있다.
// hasWall[1][r][c] : (r, c)칸 우측에 벽이 있다.

#define isSafe(r, c) (r && c && r <= R && c <= C)

void temperUp(int r, int c, int dir) {
	// 벽을 고려한 코드
	int windPower = 5;
	if (!hasWall[dir][r][c]) {
		pos cur = { r + windDir[dir].r, c + windDir[dir].c };
		map[cur.r][cur.c] += windPower;

		set<pos> s;
		s.insert({ cur.r + windDir[dir].r, cur.c + windDir[dir].c });
		s.insert({ cur.r + sideWindDir[dir].r, cur.c + sideWindDir[dir].c });
		s.insert({ cur.r + sideWindMul[dir].r * sideWindDir[dir].r, cur.c + sideWindMul[dir].c * sideWindDir[dir].c });

		while (--windPower) {
			
		}
	}

	// 벽을 고려하지 않았던 코드
	//int windPower = 5;
	//pos cur = { r + windDir[dir].r, c + windDir[dir].c };
	//int sideLeftLim = 0;
	//int sideRightLim = 0;
	//while (isSafe(cur.r, cur.c)) {
	//	for (int l = 0; l <= sideLeftLim; l++) {
	//		map[cur.r + l * sideWindDir[dir].r][cur.c + l * sideWindDir[dir].c] += windPower;
	//	}
	//	for (int r = 1; r <= sideRightLim; r++) {
	//		map[cur.r - r * sideWindDir[dir].r][cur.c - r * sideWindDir[dir].c] += windPower;
	//	}
	//	cur.r += windDir[dir].r;
	//	cur.c += windDir[dir].c;

	//	// 조건 넣어줘야 함 
	//	if (isSafe(cur.r + (sideLeftLim + 1) * sideWindDir[dir].r, cur.c + (sideLeftLim + 1) * sideWindDir[dir].c))
	//		sideLeftLim++;
	//	if (isSafe(cur.r - (sideRightLim + 1) * sideWindDir[dir].r, cur.c - (sideRightLim + 1) * sideWindDir[dir].c))
	//		sideRightLim++;
	//	if (windPower) windPower--;
	//}
}

void setWall(int r, int c, int t) {		// (r - 1, c)
	if (!t) {							// ----------
		hasWall[0][r - 1][c] = true;	// (r, c) 
		hasWall[2][r][c] = true;
	}
	else {		// (r, c) | (r, c + 1)
		hasWall[1][r][c] = true;
		hasWall[3][r][c + 1] = true;
	}
}

void tempControl() {
	int diff = 0;

	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			tempValue[i][j] = 0;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			for (int d = 0; d < 4; d++) {
				int checkR = i + dr[d];
				int checkC = j + dc[d];

				if (isSafe(checkR, checkC) && map[checkR][checkC] < map[i][j]) {
					diff = (map[i][j] - map[checkR][checkC]) / 4;
					if (!hasWall[d][i][j]) {
						tempValue[i][j] -= diff;
						tempValue[checkR][checkC] += diff;
					}
				}
			}
		}
	}

	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++)
			map[i][j] += tempValue[i][j];

	cout << " 온도 조절!\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++)
			cout << setw(5) << map[i][j];
		cout << '\n';
	}

	for (int i = 1; i <= R; i++) {
		if (map[i][1]) map[i][1]--;
		if (map[i][C]) map[i][C]--;
	}
	for (int i = 2; i < C; i++) {
		if (map[1][i]) map[1][i]--;
		if (map[R][i]) map[R][i]--;
	}

	cout << " 바깥쪽 -1 !\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++)
			cout << setw(5) << map[i][j];
		cout << '\n';
	}

	::ans++;
}

bool checkTemp() {
	int size = ::checkList.size();
	for (int i = 0; i < size; i++) {
		pos cur = checkList[i];
		if (map[cur.r][cur.c] < ::tar) return false;
	}
	return true;
}

int main() {
	cin >> R >> C >> tar;
	int input;
	for (int i = 1; i <= R; i++)
		for (int j = 1; j <= C; j++) {
			cin >> input;
			if (input == NEED_CHECK)
				checkList.push_back({ i, j });
			else if (input) {
				fanList.push_back({ i, j, input });
			}
		}

	cout << " initial state\n";
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cout << setw(4) << map[i][j];
		}cout << '\n';
	}

	//for (int i = 1; i <= R; i++) {
	//	for (int j = 1; j <= C; j++)
	//		cout << setw(3) << map[i][j];
	//	cout << '\n';
	//} 

	int m, r, c, t;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> r >> c >> t;
		setWall(r, c, t);
	}

	for (int i = 0; i < fanList.size(); i++)
		temperUp(fanList[i].r, fanList[i].c, fanList[i].dir);

	cout << " wall check\n";
	for (int i = 0; i < 2; i++) {
		printf(" i == %d \n", i);
		for (int j = 1; j <= R; j++) {
			for (int k = 1; k <= C; k++) {
				cout << setw(3) << hasWall[i][j][k];
			}
			cout << '\n';
		}
	}
	
	tempControl();
	
	while (!checkTemp()) {
		// 온풍기 바람 나옴
		for (int i = 0; i < fanList.size(); i++)
			temperUp(fanList[i].r, fanList[i].c, fanList[i].dir);
		tempControl();
		if (100 < ::ans) {
			cout << 101;
			return 0;
		}
	}
	cout << ::ans;
}
