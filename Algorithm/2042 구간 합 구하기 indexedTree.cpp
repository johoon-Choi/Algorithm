#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long ll;

vector<ll> tree;
vector <ll> list;
vector<ll> ans;
int n, s; // s => leaf node 의 시작
int m, k;

ll query(int l, int r) {
	ll ret = 0;

	for (l += s - 1, r += s - 1; l < r; l >>= 1, r >>= 1) {
		if (l & 1) ret += tree[l++];
		if (!(r & 1))ret += tree[r--];
	}

	if (l == r) ret += tree[l];

	return ret;
}

void update(int curNode, const ll diff) {
	while (curNode) {
		if (s <= curNode) tree[curNode] = diff;	// leaf node
		else tree[curNode] = tree[curNode << 1] + tree[(curNode << 1) + 1];

		curNode >>= 1;
	}
}

void init() {
	// 
	for (int i = s; i <= s + n - 1; i++)
		tree[i] = list[i - s + 1];

	int curNode = s >> 1;

	while (curNode) {
		for (int i = curNode; i < (curNode << 1); i++) {
			//	cur = left_child	 + right_child
			tree[i] = tree[(i << 1)] + tree[(i << 1) + 1];
		}

		curNode >>= 1;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> m >> k;

	s = pow(2, ceil(log(n) / log(2.0)));

	tree.assign(2 * s + 1, 0);
	list.assign(n + 1, 0);

	for (int i = 1; i <= n; i++)
		cin >> list[i];

	init();

	int select;
	int a;
	ll b;

	for (int i = 0; i < m + k; i++) {
		cin >> select >> a >> b;

		if (select & 1) { // list[a] ---> b 로 수정
			list[a] = b;

			update(s - 1 + a, b);
		}
		else { // a ~ b 전부 합 출력
			ans.push_back(query(a, b));
		}
	}

	for (auto e : ans) cout << e << '\n';
}