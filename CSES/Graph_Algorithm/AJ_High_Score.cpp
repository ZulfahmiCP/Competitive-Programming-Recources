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

struct BellmanFord {
    int N;
    vector<vector<pair<int, int>>> graph; 
    vector<int> parent;
    vector<bool> vis;
    vector<ll> dist; 

    BellmanFord(int n) : N(n), graph(N), vis(N),
                         parent(N, -1), dist(N, -INFLL) {}

    void add_edge(int u, int v, int w) {
        graph[u].pb({v, w});
    }

    ll solve(int source = 0) {
        dist[source] = 0;

        for(int i = 0; i < N - 1; i++){
            for(int u = 0; u < N; u++) if(dist[u] != -INFLL)
                for(const auto &[v, w] : graph[u]) 
                    if(dist[u] + w > dist[v])
                        dist[v] = dist[u] + w, parent[v] = u;
        }

        for(int u = 0; u < N; u++) if(dist[u] != -INFLL) {
            for(const auto &[v, w] : graph[u]){
                if(dist[u] + w <= dist[v]) 
                    continue;

                queue<int> explore;
                explore.push(u);
                fill(all(vis), 0);

                for(int node; !explore.empty();){
                    node = explore.front();
                    explore.pop();

                    if(node == N - 1)
                        return -1;

                    vis[node] = 1;
                    for(auto &[adjNode, weight] : graph[node])
                        if(!vis[adjNode])
                            explore.push(adjNode);
                }
            }
        }

        return dist[N - 1];
    }
};

int main() {

    FastIO();
    int n,m; cin >> n >> m;
    BellmanFord graph(n);

    for(int i = 0, u, v, w; i < m; i++){
        cin >> u >> v >> w, u--, v--;
        graph.add_edge(u, v, w);
    }

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
