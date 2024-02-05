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
    vector<ll> tree, lazy;

    SegTree(int n) : N(n) {
        tree.resize(4 * N, 0);
        lazy.resize(4 * N, -1);
    }

    void single(int x, int v) {
        lazy[2 * x + 1] = v;
        lazy[2 * x + 2] = v;
    }

    void propagate(int x, int l, int r) {
        if(lazy[x] == -1)
            return;

        tree[x] = lazy[x] * (r - l + 1);

        if(l != r)
            single(x, lazy[x]);

        lazy[x] = -1;
    }

    void update(int l, int r, int v) {
        update(0, 0, N - 1, l, r, v);
    }

    void update(int x, int l, int r, int ql, int qr, int v) {
        propagate(x, l, r);

        if(qr < l || ql > r)
            return;

        if(ql <= l && r <= qr){
            tree[x] = 1LL * v * (r - l + 1);

            if(l != r)
                single(x, v);

            return;
        }

        int m = (l + r) >> 1;

        update(2 * x + 1, l, m, ql, qr, v);
        update(2 * x + 2, m + 1, r, ql, qr, v);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    ll val(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }

    ll query(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if (l > qr || ql > r)
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
        cin >> t >> l >> r, r--;

        if(t == 1){
            cin >> v;
            seg.update(l, r, v);
        } else 
            cout << seg.val(l, r) << '\n';
    }

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
