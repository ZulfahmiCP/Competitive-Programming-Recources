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

struct LCA {
    int N, K, timer;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> parent, mx; 
    vector<int> depth;

    LCA(int n = 0) : N(n), K(log2(N) + 1), depth(N), adj(N),
                     parent(N, vector<int>(K, -1)), mx(N, vector<int>(K, 0)) {}

    void add_edge(int u, int v, int w) {
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    void build() {
        for(int u = 0; u < N; u++) if(parent[u][0] == -1) {
            depth[u] = 0;
            parent[u][0] = u;
            dfs(u);
        }

        for(int d = 1; d < K; d++){
            for(int u = 0, v; u < N; u++){
                v = parent[u][d - 1];
                if(v == -1) continue;
                parent[u][d] = parent[v][d - 1];
                mx[u][d] = max(mx[u][d - 1], mx[v][d - 1]);
            }
        }
    }

    void dfs(int u) {
        for(const auto &[v, w] : adj[u]){
            eliminate(adj[v], make_pair(u, w));
            mx[v][0] = w;
            parent[v][0] = u;
            depth[v] = depth[u] + 1;
            dfs(v);
        }
    }

    int lca(int u, int v) {
        if(depth[u] < depth[v]) 
            swap(u, v); 

        int goal = depth[u] - depth[v];

        for(int d = 0; d < K; d++) 
            if((goal >> d) & 1)
                u = parent[u][d];

        if(u == v) 
            return u;

        for(int d = K - 1; d >= 0; d--) 
            if(parent[u][d] != parent[v][d])
                u = parent[u][d], v = parent[v][d];

        return parent[u][0]; 
    }

    int dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    int calc(int u, int v) {
        int l = lca(u, v), res = 0;

        for(int x : {u, v}){
            if(x == l) continue;
            for(int d = K - 1; d >= 0; d--){
                if(depth[x] - (1 << d) >= depth[l]){
                    res = max(res, mx[x][d]);
                    x = parent[x][d];
                }
            }
        }

        return res;
    }
};

struct DSU {
    int N;
    vector<int> parent, size;

    DSU(int n) : N(n), parent(N), size(N, 1) {
        iota(all(parent), 0);
    }

    int find(int x) {
        return (x == parent[x]) ? x : (parent[x] = find(parent[x]));
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);

        if(x == y)
            return 0;

        if(size[x] < size[y])
            swap(x, y);
        
        parent[y] = x;
        size[x] += size[y];

        return 1;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main(){
 
    FastIO();
    int n,m,q; cin >> n >> m >> q;
    LCA tree(n);
    DSU dsu(n);

    for(int t = 1, u, v; t <= m; t++){
        cin >> u >> v, u--, v--;
        if(dsu.unite(u, v))
            tree.add_edge(u, v, t);
    }

    tree.build();

    for(int i = 0, u, v; i < q; i++){
        cin >> u >> v, u--, v--;
        cout << (dsu.same(u, v) ? tree.calc(u, v) : -1) << '\n';
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
