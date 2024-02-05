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

struct Graph {
    int N, max_depth = 30;
    vector<int> child, cycle, deg, ans;

    Graph(int n) : N(n), child(N), ans(N, 0), cycle(N, 1), deg(N, 0) {}

    void add_child(int u, int v) {
        child[u] = v;
        deg[v]++;
    }

    void dfs(int u) {
        if(!cycle[u])
            return;

        cycle[u] = 0;
        ans[child[u]] = ans[u] + 1;
        dfs(child[u]);
        ans[u] = ans[child[u]];
    }

    void dfs2(int u) {
        if(ans[u])
            return;
        dfs2(child[u]);
        ans[u] = ans[child[u]] + 1;
    }

    void build() {
        queue<int> Q;
        for(int u = 0; u < N; u++)
            if(!deg[u]) Q.push(u);

        for(int u; !Q.empty();){
            u = Q.front(); Q.pop();
            cycle[u] = 0;

            if(!(--deg[child[u]]))
                Q.push(child[u]);
        } 

        for(int u = 0; u < N; u++)
            if(cycle[u]) dfs(u);

        for(int u = 0; u < N; u++)
            if(!ans[u]) dfs2(u);
    }
};


int main(){
 
    FastIO();
    int n; cin >> n;
    Graph graph(n);

    for(int u = 0, v; u < n; u++){
        cin >> v, v--;
        graph.add_child(u, v);
    }

    graph.build();

    for(int u = 0; u < n; u++)
        cout << graph.ans[u] << " \n"[u == n - 1];

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
