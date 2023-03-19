#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<long long> vll;

int n, m, k;

/* (i & -i)
 * : i 의 2진수 값에서 가장 최하위에 있는 1을 나타낸다.
 */

ll sum(vll& tree, int i) {
	ll ret = 0;

	while (0 < i) {
		ret += tree[i];
		i -= (i & -i);
	}

	return ret;
}

void update(vll& tree, int i, ll val) {
	cout << " i : " << i << '\n';
	cout << " val : " << val << '\n';
	while (i <= ::n) {
		tree[i] += val;
		i += (i & -i);
		cout << " ==> i : " << i << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m >> k;

	vll arr(n + 1, 0);	// 펜윅트리는 arr size
	vll tree(n + 1, 0);	//			  == tree size

	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		cout << "update : " << i << ", " << arr[i] << '\n';
		update(tree, i, arr[i]);
	}

	for (int i = 1; i <= n; i++) {
		cout << "tree[" << i << "] = " << tree[i] << '\n';
	}

	m += k;

	int a;
	while (m--) {
		cin >> a;

		if (a & 1) {	// arr[b]를 c로
			int b; ll c;
			cin >> b >> c;
			ll diff = c - arr[b];
			arr[b] = c;
			update(tree, b, diff);
		}
		else {			// SUM[b:c]
			int b, c;
			cin >> b >> c;
			cout << ll(sum(tree, c) - sum(tree, b - 1)) << '\n';
		}
	}
}

/* 
 * +---------------------------------------------------------------+
 * |				            tree[8]				               |
 * +-------------------------------+-------------------------------+
 * |            tree[4]		       |			            	   |
 * +---------------+---------------+---------------+---------------+
 * |    tree[2]    |		       |	tree[6]    |		       |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * |tree[1]|	   |tree[3]|	   |tree[5]|	   |tree[7]|       |
 * +-------+-------+-------+-------+-------+-------+-------+-------+
 * 
 * +---------------------------------------+
 * |				  1000				   |
 * +-------------------+-------------------+
 * |       0100		   |				   |
 * +---------+---------+---------+---------+
 * |  0010   |		   |   0110  |		   |
 * +----+----+----+----+----+----+----+----+
 * |0001|	 |0011|	   |0101|    |0111|    |
 * +----+----+----+----+----+----+----+----+
 * 
 */