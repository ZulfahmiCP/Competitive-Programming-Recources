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
const int MAX = 500;
const double EPS = 1e-9;

void FastIO();

template <typename T>
struct MaxFlow {
    int N;
    vector<vector<T>> capacity;
    vector<vector<int>> graph;
    vector<int> parent;

    MaxFlow(int n) : N(n), parent(N), graph(N) {
        capacity.assign(N, vector<T>(N, 0));
    }

    void add_edge(int u, int v, int cap) {
        graph[u].pb(v);
        graph[v].pb(u);
        capacity[u][v] += cap;
    }

    T bfs(int s, int t) {
        fill(all(parent), -1);

        queue<pair<int, T>> explore;
        explore.push({s, numeric_limits<T>::max()});
        parent[s] = s;

        for(T new_flow; !explore.empty();){
            auto &[u, flow] = explore.front();
            explore.pop();

            for(const int &v : graph[u]){
                if(parent[v] != -1 || !capacity[u][v])
                    continue;
                
                parent[v] = u;
                new_flow = min(flow, capacity[u][v]);
                if(v == t)
                    return new_flow;
                explore.push({v, new_flow});
            }
        }

        return 0;
    }

    T max_flow(int s, int t) {
        T flow = 0, new_flow;

        while(new_flow = bfs(s, t)){
            flow += new_flow;
            for(int u = t; u != s; u = parent[u]){
                capacity[parent[u]][u] -= new_flow;
                capacity[u][parent[u]] += new_flow;
            }
        }

        return flow;
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    MaxFlow<ll> graph(n);

    for(int i = 0, u, v, c; i < m; i++){
        cin >> u >> v >> c, u--, v--;
        graph.add_edge(u, v, c);
    }

    cout << graph.max_flow(0, n - 1) << '\n';

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
