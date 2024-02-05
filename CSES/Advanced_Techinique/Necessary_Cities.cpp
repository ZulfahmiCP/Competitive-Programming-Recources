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

struct ArticulationPoint {
    int N, timer; 
    vector<vector<int>> graph;
    vector<int> tin, low, art_point;  
    vector<bool> vis, isAr;

    ArticulationPoint(int n) : N(n), timer(0), graph(N), isAr(N, 0), 
                               tin(N, -1), low(N, -1), vis(N, 0) {}

    void add_edge(int u, int v) {
        graph[u].pb(v);
        graph[v].pb(u);
    }

    void build() {
        for(int u = 0; u < N; u++)
            if(!vis[u]) dfs(u, -1);

        for(int u = 0; u < N; u++)
            if(isAr[u]) art_point.pb(u);
    }

    void dfs(int u, int p) {
        int child = 0;
        tin[u] = low[u] = timer++;
        vis[u] = 1;

        for(const int &v : graph[u]){
            if(v == p) continue;
            if(!vis[v]){
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] >= tin[u] && p != -1)
                    isAr[u] = 1;
            } else if (v != p) 
                low[u] = min(low[u], tin[v]);
        }

        if(p == -1 && child > 1)
            isAr[u] = 1;
    }
};

int main() {
    
    FastIO();
    int n,m; cin >> n >> m;
    ArticulationPoint graph(n);

    for(int i = 0, u, v; i < m; i++){
        cin >> u >> v, u--, v--;
        graph.add_edge(u, v);
    }

    graph.build();
    cout << sz(graph.art_point) << '\n';
    for(int &v : graph.art_point)
        cout << v + 1 << ' ';

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
