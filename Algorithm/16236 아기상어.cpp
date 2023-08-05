#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>
#define N 21

using namespace std;
typedef pair<int, int> pii;

typedef struct sPos{
	pii pos;
	int dist;
} sPos;

typedef struct comp {
	bool operator()(sPos& a, sPos& b) {
		if (a.dist != b.dist)
			return a.dist > b.dist;
		else if (a.pos.first != b.pos.first)
			return a.pos.first > b.pos.first;
		else return a.pos.second > b.pos.second;
	}
} comp;

int n;
int arr[N][N] = {};
int shark = 2;
int eatLeft = 0;
pii pos;

int dr[4] = { -1, 0, 0, 1 };
int dc[4] = { 0, -1, 1, 0 };

bool isSafe(int& r, int& c) {
	return 0 <= r && 0 <= c && r < n && c < n;
}

int solve() {
	bool visit[N][N] = { false, };
	int dist[N][N] = { 0, };
	int befRet = 0;
	int ret = 0;
	int eatCnt = 0;
	::eatLeft++;

	while (--::eatLeft) {
		befRet = ret;
		for (int i = 0; i < n; i++) {
			memset(visit[i], 0, sizeof(bool) * n);
			for (int j = 0; j < n; j++)
				dist[i][j] = -1;
		}
		visit[pos.first][pos.second] = true;
		dist[pos.first][pos.second] = 0;

		priority_queue<sPos, vector<sPos>, comp> s;
		s.push({ pos, 0});

		while (!s.empty()) {
			sPos cur = s.top(); s.pop();
			if (arr[cur.pos.first][cur.pos.second] && arr[cur.pos.first][cur.pos.second] < shark) {
				// eat fish
				if (++eatCnt == shark) {
					shark++;
					eatCnt = 0;
				}
				pos = pii{ cur.pos.first, cur.pos.second };
				arr[pos.first][pos.second] = 0;
				ret += cur.dist;
				break;
			}

			for (int d = 0; d < 4; d++) {
				int nr = cur.pos.first + dr[d];
				int nc = cur.pos.second + dc[d];
				if (isSafe(nr, nc) && arr[nr][nc] <= shark) {
					if (!visit[nr][nc]) {
						s.push({ {nr, nc}, cur.dist + 1});
						visit[nr][nc] = true;
					}
				}
			}
		}
	}

	if (::eatLeft)	return befRet;
	else			return ret;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 9) {
				::pos = pii{ i, j };
				::arr[i][j] = 0;
			}
			else if (arr[i][j])
				::eatLeft++;
		}
	}

	cout << solve();
}