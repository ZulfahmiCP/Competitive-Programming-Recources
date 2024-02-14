#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
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
#define eliminate(x, y) (x).erase(remove(all(x), (y)), (x).end())
#define make_unique(x) (x).erase(unique(all(x)), (x).end());
#define all_range(x) (x).begin(), (x).begin()
#define All(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)x.size()
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
const int INF = 2e9 + 7;
const ll INFL = 9e18 + 7;
const double EPS = 1e-9;

void FastIO();

struct SegTree {
    int N;
    vector<int> arr, dep;
    vector<ll> tree, lz, depth;

    SegTree(int n) : N(n), arr(N), dep(N), tree(4 * N, 0), 
                     depth(4 * N), lz(4 * N, 0) {
        build(0, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l];
            depth[x] = dep[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        depth[x] = depth[2 * x + 1] + depth[2 * x + 2];
    }

    void propagate(int x, int l, int r) {
        if(!lz[x])
            return;

        tree[x] += lz[x] * depth[x];

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
        depth[x] = depth[2 * x + 1] + depth[2 * x + 2];
    }

    ll calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
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

struct FT {
    int N, root;
    vector<vector<int>> adj;
    vector<int> tour, in, out, val;
    vector<int> sub, depth, parent;
    SegTree seg;

    FT(int n) : N(n), in(N), out(N), adj(N), seg(N),
                depth(N), parent(N), sub(N, 1), val(N) {}

    void build(int rt = 0) {
        root = rt;  
        depth[root] = 0;
        parent[root] = -1;
        dfs(root);

        for(int u = 0; u < N; u++){
            seg.arr[in[u]] = val[u];
            seg.dep[in[u]] = (depth[u] & 1  ? -1 : 1);
        }

        seg.build(0, 0, N - 1);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int dfs(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            if(v == parent[u]) continue;
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs(v);
        }

        out[u] = sz(tour) - 1;
        return sub[u];
    }

    void update(int u, int x) {
        seg.update(in[u], out[u], (depth[u] & 1 ? -x : x));
    }

    ll calc(int u) {
        return seg.calc(in[u], in[u]);
    }

    int& operator[](int u) {
        return tour[u];
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    FT tree(n);

    for(int &a : tree.val)
        cin >> a;

    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();
    
    for(int i = 0, t, u, x; i < q; i++){
        cin >> t >> u, u--;

        if(t == 1){
            cin >> x;
            tree.update(u, x);
        } else 
            cout << tree.calc(u) << '\n';
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
