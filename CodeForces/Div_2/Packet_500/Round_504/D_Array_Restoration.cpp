#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <cstring>
#include <numeric>
#include <vector>
#include <string>
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>
#define fi first 
#define se second 
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define Int unsigned int 
#define Long unsigned long long int
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()
#define newl cerr << '\n'

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void prd(const T& x);
template <typename T, typename U>
    void prd(const pair<T, U>& value);
template <typename T, typename... Args>
    void prd(const T& value, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& cont);
template <typename T>
    void debug(const set<T>& cont);
template <typename T>
    void debug(const vector<T>& cont);
template <typename T>
    void debug(const vector<vector<T>> &cont);

const int MOD = 1e9 + 7;
const int mod = 998244353;

void FastIO();
void FreeOpen();

struct SegTree {
    int N;
    vector<int> tree;

    SegTree(int n) : N(n), tree(4 * N, 0) {}

    int combine(int a, int b) {
        return b == 0 ? a : b;
    }

    void apply_combine(int &a, int b) {
        a = combine(a, b);
    }

    void propagate(int x, int l, int r) {
        if(l == r)
            return;

        apply_combine(tree[2 * x + 1], tree[x]);
        apply_combine(tree[2 * x + 2], tree[x]);

        tree[x] = 0;
    }

    void update(int l, int r, int v) {
        update(0, 0, N - 1, l, r, v);
    }

    void update(int x, int l, int r, int ql, int qr, int v) {
        propagate(x, l, r);

        if(ql > r || qr < l)
            return;

        if(ql <= l && r <= qr){
            apply_combine(tree[x], v);
            return;
        }

        int m = (l + r) / 2;
        update(2 * x + 1, l, m, ql, qr, v);
        update(2 * x + 2, m + 1, r, ql, qr, v);
    }

    int val(int j) {
        return query(0, 0, N - 1, j);
    }

    int query(int x, int l, int r, int j) {
        propagate(x, l, r);

        if(l == r)
            return tree[x];

        int m = (l + r) / 2;
        int res = (j <= m ? query(2 * x + 1, l, m, j)
                          : query(2 * x + 2, m + 1, r, j));
        return combine(res, tree[x]);
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    vector<int> A(n), L(m + 1, -1), R(m + 1, -1);

    for(int &a : A)
        cin >> a;

    for(int i = 0; i < n; i++)
        R[A[i]] = i;
    for(int i = n - 1; i >= 0; i--)
        L[A[i]] = i;

    if(L[m] == -1){
        for(int i = 0; i < n; i++)
            if(!A[i]) 
                L[m] = R[m] = i;
    }

    if(L[m] == -1){
        cout << "NO\n";
        return 0;
    }

    SegTree seg(n);
    for(int i = 1; i <= m; i++){
        if(L[i] == -1 || R[i] == -1)
            continue;
        seg.update(L[i], R[i], i);
    }

    for(int i = 0, a; i < n; i++){
        a = seg.val(i);

        if(A[i] != a && A[i] != 0){
            cout << "NO\n";
            return 0;
        }

        A[i] = a;
    }

    for(int i = 1; i < n; i++)
        if(!A[i]) 
            A[i] = A[i - 1];
    for(int i = n - 2; i >= 0; i--)
        if(!A[i]) 
            A[i] = A[i + 1];

    cout << "YES\n";
    for(int i = 0; i < n; i++)
        cout << A[i] << " \n"[i == n - 1];

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
