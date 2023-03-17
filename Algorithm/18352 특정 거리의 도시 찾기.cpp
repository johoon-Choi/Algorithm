#include <iostream>
#include <vector>
#include <queue>
#define N 300'111
#define NOVAL -1

using namespace std;

struct s {
	int city;
	int dist;
};

struct comp {
	bool operator()(s& a, s& b) {
		return a.dist > b.dist;
	}
};

int v, e, k, sp;
vector<int> adj[N];

void solve() {
	vector<int> dist_to(v + 1, NOVAL);
	priority_queue<s, vector<s>, comp> pq;

	dist_to[sp] = 0;
	pq.push({ sp, 0 });

	while (!pq.empty()) {
		int curCity = pq.top().city;
		int curDist = pq.top().dist;

		pq.pop();

		if (dist_to[curCity] < curDist) continue;

		for (int nxt : adj[curCity]) {
			int nxtCity = nxt;
			int nxtDist = curDist + 1;

			if (dist_to[nxtCity] == NOVAL || nxtDist < dist_to[nxtCity]) {
				dist_to[nxtCity] = nxtDist;
				pq.push({ nxtCity, nxtDist });
			}
		}
	}

	vector<int> ans;
	for (int i = 1; i <= v; i++)
		if (dist_to[i] == k)
			ans.push_back(i);
	if (ans.size())
		for (int city : ans) cout << city << '\n';
	else cout << -1;
}

int main() {
	cin >> v >> e >> k >> sp;
	int a, b;
	for (int i = 0; i < e; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
	}
	solve();
}