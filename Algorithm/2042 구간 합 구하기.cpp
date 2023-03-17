#include<iostream>

using namespace std;

typedef long long ll;

int N, M, K, a, b;
ll c;
ll arr[1 << 20];
ll seg[1 << 21];

ll init(int node, int s, int e)
{
    if (s == e) return seg[node] = arr[s];
    int mid = (s + e) / 2;
    return seg[node] = init(node << 1, s, mid) + init((node << 1) + 1, mid + 1, e);
}

ll prefixSum(int node, int s, int e, int l, int r) // 시작노드, start, end, left, right
{
    if (e < l || r < s) return 0; // 찾아야하는 구간(l~r)과 현재 구간(s~e)이 포함되지 않을때
    if (l <= s && e <= r) return seg[node]; // 찾아야하는 구간(l~r)내에 현재 구간(s~e)이 포함될 때
    int mid = (s + e) / 2;
    // 찾아야하는 구간(l~r)이 현재 구간(s~e)에 포함되거나, 부분적으로 겹치는 경우
    return prefixSum(2 * node, s, mid, l, r) + prefixSum(2 * node + 1, mid + 1, e, l, r);
}

void changeNum(int node, int s, int e, int index, ll diff) {// 시작노드, start, end, 찾아야하는 곳(index), 변화량(diff)
    if (e < index || index < s) return; // 찾아야하는 곳(index)과 현재 구간(s~e)이 포함되지 않을때
    seg[node] += diff;
    if (s != e) {
        int mid = (s + e) / 2;
        changeNum(2 * node, s, mid, index, diff);
        changeNum(2 * node + 1, mid + 1, e, index, diff);
    }
}

int main()
{
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++)
        cin >> arr[i];

    init(1, 1, N); // 세그먼트 트리 생성

    for (int i = 0; i < M + K; i++)
    {
        cin >> a >> b >> c;
        ll diff = 0;
        switch (a) {
        case 1:
            diff = c - arr[b];
            arr[b] = c;
            changeNum(1, 1, N, b, diff);
            break;
        case 2:
            cout << prefixSum(1, 1, N, b, c) << '\n';
            break;
        default:
            break;
        }
    }
}