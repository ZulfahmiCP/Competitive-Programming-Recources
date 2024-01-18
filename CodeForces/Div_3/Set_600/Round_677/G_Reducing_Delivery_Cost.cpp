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
void FreeOpen();

struct Dijkstra {
    int N; 
    vector<vector<pair<int, int>>> adjList;
    vector<pair<int, int>> edges, routes; 
    vector<int> distance;

    Dijkstra(int n) {
        N = n;
        adjList.resize(N);
        distance.resize(N);
    }

    void add_edge(int u, int v, int w) {
        adjList[u].pb({v, w});
        adjList[v].pb({u, w});
        edges.pb({u, v});
    }

    void run(int source) {
        fill(all(distance), 1e8);

        min_heap<pair<int, int>> explore;
        explore.push({0, source});
        distance[source] = 0;

        while(!explore.empty()) {
            auto [weight, node] = explore.top();
            explore.pop();

            if(distance[node] < weight)
                continue;

            for(auto &[adjNode, edgeWeight] : adjList[node]) 
                if(distance[node] + edgeWeight < distance[adjNode]) {
                    distance[adjNode] = distance[node] + edgeWeight;
                    explore.push({distance[adjNode], adjNode});
                }
        }
    }
};

int main(){
 
    FastIO();
    int n,m,k; cin >> n >> m >> k;
    vector<vector<int>> D(n);
    Dijkstra graph(n);

    for(int i = 0, u,v,w; i < m; i++){
        cin >> u >> v >> w;
        u--, v--;
        graph.add_edge(u, v, w);
    }

    for(int i = 0; i < n; i++){
        graph.run(i);
        D[i] = graph.distance;
    }

    for(int i = 0, a,b; i < k; i++){
        cin >> a >> b;
        a--, b--;
        graph.routes.pb({a, b});
    }

    ll ans = 9e18;
    for(auto &[u, v] : graph.edges){
        ll cost = 0;
        for(auto &[a, b] : graph.routes)
            cost += min({D[a][b], D[u][a] + D[v][b], D[u][b] + D[v][a]});
        ans = min(ans, cost);
    }

    cout << ans << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& value){ cerr << "("; prd(value.first); cerr << ", "; prd(value.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& value, Args... args){prd(value); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
