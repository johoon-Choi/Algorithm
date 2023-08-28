#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#define N 100'111
#define M 111

using namespace std;

typedef struct elv {
	int s, d;
} elv;
typedef vector<int> vi;
typedef unordered_set<int> usi;

int n, m;
int s, e;
elv elvs[M];
bool adj[M][M];

inline bool hasFloor(int& node, int& tar) {
	return elvs[node].s <= tar 
		&& (tar - elvs[node].s) % elvs[node].d == 0;
}

inline void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

inline bool isConnected(int nodeA, int nodeB) {
	int as = elvs[nodeA].s;
	int ad = elvs[nodeA].d;
	int bs = elvs[nodeB].s;
	int bd = elvs[nodeB].d;

	if (as == bs)
		return true;
	else if (ad == bd) {
		if (as < bs)
			return (bs - as) % ad == 0;
		else return (as - bs) % ad == 0;
	}
	else {
		if (as < bs) {
			swap(as, bs);
			swap(ad, bd);
		}
		int an = (::n - as) / ad;
		int bn = (::n - bs) / bd;
		as -= bs;
		bs = 0;
		for (int ak = 0; ak <= an; ak++) {
			if ((as + ad * ak) % bd == 0) {
				if ((as + ad * ak) / bd <= bn)
					return true;
			}
		}
	}
	return false;
}

bool notExist(vector<int>& v, int& tar) {
	int size = v.size();
	for (int i = 0; i < size; i++) {
		if (v[i] == tar) return false;
	} return true;
}

void solve() {
	// init
	queue<vi> q;
	for (int i = 1; i <= m; i++) {
		if (hasFloor(i, s)) {
			if (hasFloor(i, e)) {
				cout << 1 << '\n' << i;
				return;
			}
			vi route;
			route.push_back(i);
			q.push(route);
		}
	} // start floor ÀÇ ¸ðÀÓ

	while (!q.empty()) {	
		vi cur = q.front(); q.pop();
		int curNode = cur[cur.size() - 1];

		for (int i = 1; i <= m; i++) {
			if (curNode == i) continue;
			if (notExist(cur, i) && adj[curNode][i]) {
				vi cur2 = cur;
				cur2.push_back(i);
				q.push(cur2);

				if (hasFloor(i, e)) {
					cout << cur2.size() << '\n';
					for (int i = 0; i < cur2.size(); i++)
						cout << cur2[i] << '\n';
					return;
				}
				else if (cur2.size() == m) {
					cout << -1;
					return;
				}
			}
		}
	}
	cout << -1;
	return;
}

FILE* input;

int main() {
	//freopen_s(&input, "2593testcase.txt", "r", stdin);
	cin >> n >> m;
	int a, b;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		elvs[i] = elv{ a, b };
		for (int j = 1; j < i; j++)
			if (isConnected(i, j))
				adj[i][j] = adj[j][i] = true;
	}

	cin >> s >> e;

	solve();
}