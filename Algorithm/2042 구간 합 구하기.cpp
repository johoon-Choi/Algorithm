#include<iostream>

using namespace std;

typedef long long ll;

int N, M, K, a, b;
ll c;
ll arr[1 << 20];
ll seg[1 << 21];

// Full Binary Tree 형태의 Binary Tree 생성
ll init(int node, int s, int e) {
    if (s == e) return seg[node] = arr[s];
    int mid = (s + e) / 2;
    return seg[node] = init(node << 1, s, mid) + init((node << 1) + 1, mid + 1, e);
}

//                     curS   curE   tarL          tarR
ll prefixSum(int node, int s, int e, const int& L, const int& R) {
    if (e < L || R < s) return 0;
    /*      target  :               (L) ================ (R)
     *      cur1    :                                       (s) ===== (e)
     *      cur2    : (s) ===== (e)
     */


    if (L <= s && e <= R) return seg[node];
    /*      target  : (L) ================ (R)
     *      cur     :        (s) ===== (e)
     */

     /*      [Cur status]
      * 
      *      target  :       (L) ================ (R)
      *      cur1    : (s) ========= (e)
      *   or cur2    :                  (s) ======= (e)
      * 
      *   그래서, 다시 반 쪼개서 체크
      */
    int mid = (s + e) / 2;
    
    return   prefixSum(node << 1, s, mid, L, R) 
           + prefixSum((node << 1) + 1, mid + 1, e, L, R);
}

void changeNum(int node, int s, int e, const int& index, ll diff) {
    if (e < index || index < s) return;

    // change 하려는 index 가 포함된 범위의 node 는 전부 diff 를 더해준다.

    seg[node] += diff;

    if (s != e) {
        int mid = (s + e) / 2;
        changeNum(  node << 1,        s,          mid,    index,  diff);
        changeNum(  (node << 1) + 1,  mid + 1,    e,      index,  diff);
    }
}

int main() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++)
        cin >> arr[i];

    init(1, 1, N); // 세그먼트 트리 생성

    for (int i = 0; i < M + K; i++) {
        cin >> a >> b >> c;

        ll diff = 0;

        switch (a) {
        case 1:
            diff = c - arr[b];  // arr[b] + diff == c
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