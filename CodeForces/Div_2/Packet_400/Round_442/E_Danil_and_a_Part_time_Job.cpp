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
    int N, root, timer, diameter;
    vector<vector<int>> adj;
    vector<int> tour, in, out;
    vector<int> sub, depth, parent;

    FT(int n) : N(n), in(N), out(N), sub(N, 1),
                adj(N), depth(N), parent(N) {}

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

    int find_diameter() {
        for(int u = 1; u < N; u++)
            if(depth[diameter] < depth[u])
                diameter = u;
        
        vector<int> d(N, 0);

        function<void(int, int)> explore = [&](int u, int p) -> int {
            if(p != -1) d[u] = d[p] + 1;

            for(const int& v : adj[u])
                if(v != p) explore(v, u);
        };

        explore(diameter, -1);

        for(int u = 1; u < N; u++)
            if(d[diameter] < d[u])  
                diameter = u;
        
        diameter = depth[diameter];
        return diameter;
    }

    int& operator[](int u) {
        return tour[u];
    }
};

struct SegTree {
    int N;
    vector<int> arr, lamp, tree, lz;

    SegTree(const vector<int> &A) : N(A.size()), arr(A), lamp(N), 
                                    tree(4 * N), lz(4 * N, 0) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = lamp[arr[l]];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void propagate(int x, int l, int r) {
        if(!lz[x])
            return;

        tree[x] = (r - l + 1) - tree[x];

        if(l != r){
            lz[2 * x + 1] ^= 1;
            lz[2 * x + 2] ^= 1;
        }

        lz[x] = 0;
    }

    void update(int l, int r) {
        modify(0, 0, N - 1, l, r);
    }

    void modify(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            lz[x] = 1;
            propagate(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify(2 * x + 1, l, m, ql, qr);
        modify(2 * x + 2, m + 1, r, ql, qr);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    int calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
    }

    int process(int x, int l, int r, int ql, int qr) {
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
    int n; cin >> n;
    FT tree(n);

    for(int u = 1, v; u < n; u++){
        cin >> v, v--;
        tree.add_edge(u, v);
    }

    tree.build();

    SegTree seg(tree.tour);
    for(int &a : seg.lamp)
        cin >> a;
    seg.build(0, 0, n - 1);

    int q, v; cin >> q;
    string op;
    while(q--){
        cin >> op >> v, v--;

        if(op[0] == 'g')
            cout << seg.calc(tree.in[v], tree.out[v]) << '\n';
        else 
            seg.update(tree.in[v], tree.out[v]);
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
