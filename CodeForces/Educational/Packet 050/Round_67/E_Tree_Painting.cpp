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

struct Tree {
    int N, root, diameter;
    vector<vector<int>> adj;
    vector<int> tour, in, out;
    vector<int> sub, depth, parent;
    vector<ll> dp;
    ll ans;

    Tree(int n) : N(n), in(N), out(N), adj(N), dp(N),
                  sub(N, 1), depth(N), parent(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    void build(int rt = 0) {
        root = rt;  
        depth[root] = 0;
        parent[root] = -1;
        dfs_sub(root);
        dfs_dp(root);
    }

    ll res() {
        ans = 0;
        dfs(root);
        return ans;
    }

    void dfs(int u) {
        ans = max(ans, dp[u]);

        for(const int &v : adj[u]){
            dp[u] -= dp[v];
            dp[u] -= sub[v];
            sub[u] -= sub[v];
            dp[v] += dp[u];
            dp[v] += sub[u];
            sub[v] += sub[u];

            dfs(v);

            sub[v] -= sub[u];
            dp[v] -= sub[u];
            dp[v] -= dp[u];
            sub[u] += sub[v];
            dp[u] += sub[v];
            dp[u] += dp[v];
        }
    }

    int dfs_sub(int u) {
        in[u] = sz(tour);
        tour.pb(u);

        for(const int &v : adj[u]){
            eliminate(adj[v], u);
            parent[v] = u, depth[v] = depth[u] + 1;
            sub[u] += dfs_sub(v);
        }

        out[u] = sz(tour);
        tour.pb(u);

        return sub[u];
    }

    ll dfs_dp(int u) {
        dp[u] = sub[u];
        for(const int &v : adj[u])
            dp[u] += dfs_dp(v);
        return dp[u];
    }
};

int main(){
 
    FastIO();
    int n; cin >> n;
    Tree tree(n);

    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();
    cout << tree.res() << '\n';

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
