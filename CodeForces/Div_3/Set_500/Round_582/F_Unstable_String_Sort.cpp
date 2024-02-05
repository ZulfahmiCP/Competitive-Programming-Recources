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

struct SCC {
    int N, M;
    vector<vector<int>> adj, revAdj, graph;
    vector<int> parent;
    vector<bool> vis;
    stack<int> order;

    SCC(int n) : N(n), M(0) {
        adj.resize(N);
        revAdj.resize(N);
        vis.resize(N, 0);
        parent.resize(N);
        iota(all(parent), 0);
    }

    void add_edge(int u, int v) {
        adj[u].pb(v);
        revAdj[v].pb(u);
    }

    void run() {
        for(int u = 0; u < N; u++)
            if(!vis[u])
                dfs(u);
        
        fill(all(vis), 0);

        for(int u; !order.empty();){
            u = order.top();
            order.pop();

            if(vis[u])
                continue;
        
            explore(u);
            M++;
        }
    }

    void gen_new_graph() {
        graph.resize(N);
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

        for(int &v : adj[u])
            if(!vis[v])
                dfs(v);
        
        order.push(u);
    }

    void explore(int u) {
        vis[u] = 1;

        for(int v : revAdj[u]){
            if(vis[v])
                continue;
            parent[v] = parent[u];
            explore(v);
        }
    }
};

int main(){
 
    FastIO();
    int n,k; cin >> n >> k;
    vector<int> P(n), Q(n);
    SCC A(n);

    for(int &p : P) cin >> p, p--;
    for(int &q : Q) cin >> q, q--;

    for(int i = 1; i < n; i++){
        A.add_edge(P[i - 1], P[i]);
        A.add_edge(Q[i - 1], Q[i]);
    }

    A.run();

    if(A.M < k){
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    A.gen_new_graph();

    vector<int> ans(n, 0), inDeg(n, 0);

    for(int u = 0; u < n; u++)
        for(int v : A.graph[u])
            if(v < n)
                inDeg[v]++;

    queue<int> bfs;

    for(int u = 0; u < n; u++)
        if(u == A.parent[u] && !inDeg[u])
            bfs.push(u);

    for(int u; !bfs.empty();){
        u = bfs.front();
        bfs.pop();

        for(int v : A.graph[u]){
            ans[v] = min(ans[u] + 1, 25);
            bfs.push(v);
        }
    }

    for(int i = 0; i < n; i++)
        cout << char(ans[A.parent[i]] + 'a');

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
