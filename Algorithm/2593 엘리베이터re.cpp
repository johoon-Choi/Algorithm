#include <iostream>
#include <vector>
#include <queue>
#define N 100'111
#define M 111

using namespace std;

typedef struct elv {
	int s, d;
} elv;
typedef vector<int> vi;

int n, m, s, e;
elv elvs[M];
vi adj[M];
bool hasStart[M];
bool hasEnd[M];
int beforeElv[M];

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

	if (as < bs) {
		swap(as, bs);
		swap(ad, bd);
	}
	
	int an = (::n - as) / ad;
	int bn = (::n - bs) / bd;
	as -= bs;
	bs = 0;

	for (int ak = 0; ak <= an; ak++)
		if ((as + ad * ak) % bd == 0 && (as + ad * ak) / bd <= bn)
				return true;
	return false;
}

void solve() {
	queue<int> q;
	for (int i = 1; i <= m; i++)
		if (::hasStart[i])
			q.push(i);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		if (::hasEnd[cur]) {
			vi ans;
			ans.push_back(cur);
			while (!hasStart[cur])
				ans.push_back(cur = beforeElv[cur]);

			cout << ans.size() << '\n';
			for (int i = ans.size() - 1; i >= 0; i--) {
				cout << ans[i] << '\n';
			}
			return;
		}

		for (int i = 0; i < adj[cur].size(); i++) {
			int nxt = adj[cur][i];
			if (beforeElv[nxt]) continue; // 이미 더 가까운 엘베에서 방문 한 경우
			beforeElv[nxt] = cur;
			q.push(nxt);
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
			if (isConnected(i, j)) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
	}

	cin >> s >> e;

	for (int i = 1; i <= m; i++) {
		if (hasFloor(i, s)) ::hasStart[i] = true;
		if (hasFloor(i, e)) ::hasEnd[i] = true;
	}

	solve();
}