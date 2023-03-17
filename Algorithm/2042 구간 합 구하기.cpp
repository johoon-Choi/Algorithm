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

ll prefixSum(int node, int s, int e, int l, int r) // ���۳��, start, end, left, right
{
    if (e < l || r < s) return 0; // ã�ƾ��ϴ� ����(l~r)�� ���� ����(s~e)�� ���Ե��� ������
    if (l <= s && e <= r) return seg[node]; // ã�ƾ��ϴ� ����(l~r)���� ���� ����(s~e)�� ���Ե� ��
    int mid = (s + e) / 2;
    // ã�ƾ��ϴ� ����(l~r)�� ���� ����(s~e)�� ���Եǰų�, �κ������� ��ġ�� ���
    return prefixSum(2 * node, s, mid, l, r) + prefixSum(2 * node + 1, mid + 1, e, l, r);
}

void changeNum(int node, int s, int e, int index, ll diff) {// ���۳��, start, end, ã�ƾ��ϴ� ��(index), ��ȭ��(diff)
    if (e < index || index < s) return; // ã�ƾ��ϴ� ��(index)�� ���� ����(s~e)�� ���Ե��� ������
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

    init(1, 1, N); // ���׸�Ʈ Ʈ�� ����

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