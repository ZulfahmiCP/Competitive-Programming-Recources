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

struct Centroid {
    int N, K, depth;
    vector<vector<int>> adj;
    vector<int> sub, cnt;
    vector<bool> vis;
    ll ans = 0;

    Centroid(int n, int k) : N(n), K(k), vis(N, 0),    
                             adj(N), sub(N), cnt(N, 0) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int dfs_sub(int u, int p = -1){
        sub[u] = 1;
        for(const int &v : adj[u])
            if(v != p && !vis[v])
                sub[u] += dfs_sub(v, u);
        return sub[u];
    }

    int centroid(int u, int p, int n){
        for(const int &v : adj[u])
            if(v != p && !vis[v] && sub[v] > n / 2)
                return centroid(v, u, n);
        return u;
    }

    void solve(int u = 0){
        int c = centroid(u, -1, dfs_sub(u));
        vis[c] = 1;
        depth = 0;

        for(const int &v : adj[c]){
            if(vis[v]) continue;
            dfs(v, c, 0);
            dfs(v, c, 1);
        }

        fill(1 + all_range(cnt) + depth + 1, 0);

        for(const int &v : adj[c])
            if(!vis[v])
                solve(v);
    }

    void dfs(int u, int p, bool t, int d = 1){
        if(d > K)   
            return;

        depth = max(depth, d);
        t ? cnt[d]++ : ans += cnt[K - d];

        for(const int &v : adj[u])
            if(v != p && !vis[v])
                dfs(v, u, t, d + 1);
    }
};

int main(){

    FastIO();
    int n,k; cin >> n >> k;
    Centroid tree(n, k);

    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }

    tree.cnt[0] = 1;
    tree.solve();
    cout << tree.ans << '\n';

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
