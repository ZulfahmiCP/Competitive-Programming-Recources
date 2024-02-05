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
const int INF = 2e9 + 7;
const ll INFLL = 9e18 + 7;

void FastIO();

struct SCC {
    int N, M;
    vector<vector<int>> adj, revAdj, graph;
    vector<int> parent, order;
    vector<ll> coin, ans;
    vector<bool> vis;

    SCC(int n) : N(n), M(0), coin(N), adj(N), ans(N, 0),
                 revAdj(N), parent(N), vis(N, 0), graph(N) {
        iota(all(parent), 0);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        revAdj[v].pb(u);
    }

    void build() {
        for(int u = 0; u < N; u++)
            if(!vis[u]) dfs(u);

        fill(all(vis), 0);
        reverse(all(order));

        for(const int &u : order){
            if(vis[u]) continue;
            explore(u);
            M++;
        }

        for(int u = 0; u < N; u++)
            for(int v : adj[u])
                if(parent[u] != parent[v])
                    graph[parent[u]].pb(parent[v]);

        for(int u = 0; u < N; u++)
            if(!graph[u].empty())
                graph[u].erase(unique(all(graph[u])), graph[u].end());
    }

    void dfs(int u) {
        vis[u] = 1;
        for(const int &v : adj[u])
            if(!vis[v]) dfs(v);
        order.pb(u);
    }

    void explore(int u) {
        vis[u] = 1;

        if(parent[u] != u)
            coin[parent[u]] += coin[u];

        for(const int &v : revAdj[u]){
            if(vis[v]) continue;
            parent[v] = parent[u];
            explore(v);
        }
    }

    void trav(int u, int p) {
        vis[u] = 1;
        ans[u] = coin[u];

        for(const int &v : graph[u]){
            if(v == p) continue;
            if(!vis[v]) trav(v, u);
            ans[u] = max(ans[u], coin[u] + ans[v]);
        }
    }

    ll solve() {
        fill(all(vis), 0);
        for(int u = 0; u < N; u++)
            if(!vis[u] && u == parent[u])
                trav(u, -1);
        return *max_element(all(ans));
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    SCC graph(n);

    for(auto &c : graph.coin)
        cin >> c;

    for(int i = 0, u, v;  i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    graph.build();
    cout << graph.solve() << '\n';

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
