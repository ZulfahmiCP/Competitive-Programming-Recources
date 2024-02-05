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
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()
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

void FastIO();

struct FT {
    int N, root, timer;
    vector<vector<int>> adj;
    vector<int> tour, in, out;
    vector<int> sub, depth, parent;

    FT(int n) : N(n), in(N), out(N), adj(N),
                sub(N, 1), depth(N), parent(N) {}

    void build(int rt = 0) {
        root = rt;
        timer = 0;  
        depth[root] = 0;
        parent[root] = -1;
        dfs(root);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void dfs(int u) {
        in[u] = timer++;
        tour.pb(u);

        for(const int &v : adj[u]){
            if(v == parent[u]) continue;
            parent[v] = u, depth[v] = depth[u] + 1;
            dfs(v);
            sub[v] += sub[u];
        }

        out[u] = timer - 1;
    }

    int& operator[](int u) {
        return tour[u];
    }
};

struct SegTree {
    int N;
    vector<int> arr, color, lz;
    vector<ll> tree;

    SegTree(int n) : N(n), arr(N), color(N), tree(4 * N), lz(4 * N, -1) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = (1LL << color[arr[l]]);
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] | tree[2 * x + 2];
    }

    void propagate(int x, int l, int r) {
        if(lz[x] == -1)
            return;

        tree[x] = (1LL << lz[x]);

        if(l != r)
            lz[2 * x + 1] = lz[2 * x + 2] = lz[x];

        lz[x] = -1;
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

        tree[x] = tree[2 * x + 1] | tree[2 * x + 2];
    }

    int calc(int l, int r) {
        return __builtin_popcountll(process(0, 0, N - 1, l, r));
    }

    ll process(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x];

        int m = (l + r) >> 1;

        return process(2 * x + 1, l, m, ql, qr) |
               process(2 * x + 2, m + 1, r, ql, qr);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);
    FT tree(n);

    for(int &c : seg.color)
        cin >> c, c--;
    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();
    
    for(int i = 0; i < n; i++)
        seg.arr[i] = tree[i];
    seg.build(0, 0, n - 1);

    for(int i = 0, t, v, c; i < q; i++){
        cin >> t >> v, v--;

        if(t == 1){
            cin >> c, c--;
            seg.update(tree.in[v], tree.out[v], c);
        } else 
            cout << seg.calc(tree.in[v], tree.out[v]) << '\n';
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
