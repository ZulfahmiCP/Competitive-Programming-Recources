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

struct Edge {
    int u, v, w;
};

struct BellmanFord {
    int N;
    vector<Edge> edges;
    vector<int> parent, cycle;
    vector<ll> dist;

    BellmanFord(int n) : N(n), dist(N, INFLL), parent(N, -1) {}

    void add_edge(int u, int v, int w) {
        edges.pb({u, v, w});
    }

    bool solve(int source) {
        dist[source] = 0;

        int x;
        for(int i = 0; i < N; i++){
            x = -1;
            for(const auto &[u, v, w] : edges)
                if(dist[u] != INFLL && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w, parent[v] = u, x = v;
        }

        if(x == -1)
            return 1;

        for(int i = 0; i < N; i++)
            x = parent[x];

        for(int v = x;;v = parent[v]){
            cycle.pb(v);
            if(v == x && sz(cycle) > 1)
                break;
        }

        reverse(all(cycle));

        return 0;
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

    if(!graph.solve(0) || !graph.solve(1) || !graph.solve(n - 1)){
        cout << "YES\n";
        for(const int &v : graph.cycle)
            cout << v + 1 << ' ';
    } else 
        cout << "NO\n";

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
