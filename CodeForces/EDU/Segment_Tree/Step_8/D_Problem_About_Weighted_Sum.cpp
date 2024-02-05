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

struct SegTree {
    int N;
    vector<int> arr;
    vector<ll> tree, treeW, lz;

    SegTree(int n) : N(n), arr(N), tree(4 * N), treeW(4 * N), lz(4 * N, 0) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l];
            treeW[x] = (l + 1) * arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        treeW[x] = treeW[2 * x + 1] + treeW[2 * x + 2];
    }

    void propagate(int x, int l, int r) {
        if(!lz[x])
            return;

        tree[x] += lz[x] * (r - l + 1);
        treeW[x] += lz[x] * (r + l + 2) * (r - l + 1) >> 1;

        if(l != r){
            lz[2 * x + 1] += lz[x];
            lz[2 * x + 2] += lz[x];
        }

        lz[x] = 0;
    }

    void update(int l, int r, int v) {
        modify(0, 0, N - 1, l, r, v);
    }

    void modify(int x, int l, int r, int ql, int qr, int v) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            lz[x] = v;
            propagate(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify(2 * x + 1, l, m, ql, qr, v);
        modify(2 * x + 2, m + 1, r, ql, qr, v);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        treeW[x] = treeW[2 * x + 1] + treeW[2 * x + 2];
    }

    ll calc(int l, int r) {
        return processW(0, 0, N - 1, l, r) - process(0, 0, N - 1, l, r) * l;
    }

    ll processW(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return treeW[x];

        int m = (l + r) >> 1;

        return processW(2 * x + 1, l, m, ql, qr) +
               processW(2 * x + 2, m + 1, r, ql, qr);
    }

    ll process(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x];

        int m = (l + r) >> 1;

        return process(2 * x + 1, l, m, ql, qr) +
               process(2 * x + 2, m + 1, r, ql, qr);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int &a : seg.arr)
        cin >> a;
    seg.build(0, 0, n - 1);

    for(int i = 0, t,l,r,v; i < q; i++){
        cin >> t >> l >> r, l--, r--;

        if(t == 1){
            cin >> v;
            seg.update(l, r, v);
        } else 
            cout << seg.calc(l, r) << '\n';
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
