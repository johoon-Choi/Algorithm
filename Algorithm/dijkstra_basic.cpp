#include <iostream>
#include <vector>
#include <queue>
#define N 300'111
#define NOVAL -1

using namespace std;

struct s {
	int node;
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
		int curNode = pq.top().node;
		int curDist = pq.top().dist;

		pq.pop();

		if (dist_to[curNode] < curDist) continue;

		for (int nxt : adj[curNode]) {
			int nxtNode = nxt;
			int nxtDist = curDist + 1;

			if (dist_to[nxtNode] == NOVAL || nxtDist < dist_to[nxtNode]) {
				dist_to[nxtNode] = nxtDist;
				pq.push({ nxtNode, nxtDist });
			}
		}
	}
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