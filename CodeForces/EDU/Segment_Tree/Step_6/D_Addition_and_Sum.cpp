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

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void printDbg(const T& x);
template <typename T, typename U>
    void printDbg(const pair<T, U>& v);
template <typename T, typename... Args>
    void printDbg(const T& v, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& container);
template <typename T>
    void debug(const set<T>& container);
template <typename T>
    void debug(const vector<T>& container);
template <typename T>
    void debug(const vector<vector<T>> &container);

const int MOD = 1e9 + 7;
const int mod = 998244353;

void FastIO();
void FreeOpen();

struct SegTree {
    int N;
    vector<int> A;
    vector<ll> tree, lazy;

    SegTree(int n) : N(n) {
        tree.resize(4 * N, 0);
        lazy.resize(4 * N, 0);
    }

    SegTree(const vector<int> &arr) {
        A = arr, N = A.size();
        tree.resize(4 * N, 0);
        lazy.resize(4 * N, 0);
        build();
    }

    void build() {
        build(0, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if (l == r) {
            tree[x] = A[l];
            return;
        }

        int m = (l + r) >> 1;
        build(2 * x + 2, l, m);
        build(2 * x + 1 + 2, m + 1, r);
    }

    void single(int x, int v) {
        lazy[2 * x + 1] += v;
        lazy[2 * x + 2] += v;
    }

    void propagate(int x, int l, int r) {
        if(!lazy[x])
            return;

        tree[x] += lazy[x] * (r - l + 1);

        if(l != r)
            single(x, lazy[x]);

        lazy[x] = 0;
    }

    void update(int l, int r, int v) {
        update(0, 0, N - 1, l, r, v);
    }

    void update(int x, int l, int r, int ql, int qr, int v) {
        propagate(x, l, r);

        if(qr < l || ql > r)
            return;

        if(ql <= l && r <= qr){
            tree[x] += 1LL * v * (r - l + 1);

            if(l != r)
                single(x, v);

            return;
        }

        int m = (l + r) >> 1;

        update(2 * x + 1, l, m, ql, qr, v);
        update(2 * x + 2, m + 1, r, ql, qr, v);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    ll query(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }

    ll query(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if (qr < l || ql > r)
            return 0;

        if (ql <= l && r <= qr)
            return tree[x];

        int m = (l + r) >> 1;

        return query(2 * x + 1, l, m, ql, qr) +
               query(2 * x + 2, m + 1, r, ql, qr);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int i = 0, t,l,r,v; i < q; i++){
        cin >> t >> l >> r;

        if(t == 1){
            cin >> v;
            seg.update(l, r - 1, v);
        } else 
            cout << seg.query(l, r - 1) << '\n';
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& v){ cerr << "("; printDbg(v.first); cerr << ", "; printDbg(v.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& v, Args... args){printDbg(v); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
