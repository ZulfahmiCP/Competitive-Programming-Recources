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


/*  Types of Constrains
    (x OR y) = (~x ==> y) AND (~y ==> x)

    1. If we want force x to be true, then add (x OR x)
    2. If we one condition must be true, the add (x OR y) AND (~x OR ~y)
    3. If at least one condition must be true, then add (x OR y)
    4. If both condition must be true, then add (~x OR y) AND (x OR ~y) 

    clause OR ==> At least one of them is true
    clause XOR ==> Only one of them is true
    clause AND ==> Both of them have the same value
*/

struct TwoSAT {
    int N;
    vector<vector<int>> graph, rev_graph;
    vector<int> comp, order, ans;
    vector<bool> vis;

    TwoSAT(int n = 0) : N(n), graph(2 * N), rev_graph(2 * N),
                        comp(2 * N), vis(2 * N), ans(2 * N) {}

    void add_edge(int u, int v) {
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }

    void add_clause_or(int u, bool a, int v, bool b) {
        add_edge(u + (a ? N : 0), v + (b ? 0 : N));
        add_edge(v + (b ? N : 0), u + (a ? 0 : N));
    }

    void add_clause_xor(int u, bool a, int v, bool b) {
        add_clause_or(u, a, v, b);
        add_clause_or(u, !a, v, !b);
    }

    void add_clause_and(int u, bool a, int v, bool b) {
        add_clause_xor(u, !a, v, b);
    }

    void dfs(int u) {
        vis[u] = 1;
        for(const int &v : graph[u])
            if(!vis[v]) dfs(v);
        order.pb(u);
    }

    void scc(int u, int i) {
        vis[u] = true;
        comp[u] = i;

        for(const int &v : rev_graph[u])
            if(!vis[v]) scc(v, i);
    }

    bool satisfiable() {
        fill(all(vis), 0);

        for(int u = 0; u < 2 * N; u++)
            if(!vis[u]) dfs(u);

        fill(all(vis), 0);
        reverse(all(order));

        int id = 0;
        for(const int &v : order)
            if(!vis[v]) scc(v, id++);

        for(int u = 0; u < N; u++){
            if(comp[u] == comp[u + N])
                return 0;
            ans[u] = (comp[u] > comp[u + N]);
        }

        return 1;
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> m >> n;
    TwoSAT sat(n);

    for(int i = 0, u, v; i < m; i++){
        char s, t;
        cin >> s >> u >> t >> v, u--, v--;
        sat.add_clause_or(u, s == '+', v, t == '+');
    }

    if(!sat.satisfiable()){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    for(int u = 0; u < n; u++)
        cout << (sat.ans[u] ? '+' : '-') << " \n"[u == n - 1];

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
