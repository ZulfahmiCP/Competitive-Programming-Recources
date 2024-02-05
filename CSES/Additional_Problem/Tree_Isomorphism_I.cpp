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

struct Tree {
    int N;
    vector<vector<int>> adj, layer;
    vector<int> par;

    Tree(int n) : N(n), adj(N) {}

    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vector<int> center() {
        int u = 0;

        for(int k = 0; k < 2; k++){
            queue<int> bfs;
            par.resize(N, -1);
            bfs.push(par[u] = u);
            while(!bfs.empty()){
                u = bfs.front();
                bfs.pop();
                
                for(const int &v : adj[u]){
                    if(par[v] >= 0) continue;
                    bfs.push(v);
                    par[v] = u;
                }
            }
        }

        vector<int> path = {u};
        while(u != par[u])
            path.pb(u = par[u]);
        
        int m = sz(path);
        return (m & 1 ? vector<int>{path[m / 2]} : 
                        vector<int>{path[m / 2 - 1], path[m / 2]});
    }

    int split(int node) {
        par.resize(N, -1);
        par[node] = N;
        layer = {{node}};

        while(true){
            vector<int> child;
            for(const int &u : layer.back()){
                for(const int &v : adj[u]){
                    if(par[v] >= 0) continue;
                    par[v] = u;
                    child.pb(v);
                }
            }

            if(child.empty())
                break;
            layer.pb(child);
        }

        return sz(layer);
    }
};

bool isomorphic(Tree &S, int s, Tree &T, int t) {
    if(S.N != T.N || S.split(s) != T.split(t))
        return 0;
    
    vector<vector<int>> A(S.N + 1), B(T.N + 1);
    vector<int> a(S.N), b(T.N);

    for(int h = S.layer.size() - 1, i; h >= 0; h--){
        map<vector<int>, int> M;

        for(const int &u : S.layer[h]){
            sort(all(A[u]));
            M[A[u]] = 0;
        }

        for(const int &u : T.layer[h]){
            sort(all(B[u]));
            M[B[u]] = 0;
        }

        i = 0;
        for(auto &p : M)
            p.se = i++;

        for(const int &u : S.layer[h]){
            a[u] = M[A[u]];
            A[S.par[u]].pb(a[u]);
        }

        for(const int &u : T.layer[h]){
            b[u] = M[B[u]];
            B[T.par[u]].pb(b[u]);
        }
    }

    return a[s] == b[t];
}

// bool isomorphic(Tree &S, Tree &T) {
//     auto a = S.center(), b = T.center();
//     if(sz(a) != sz(b)) 
//         return 0;
//     if(isomorphic(S, a[0], T, b[0])) 
//         return 1;
//     return sz(a) > 1 && isomorphic(S, a[1], T, b[1]);
// }

int main(){
 
    FastIO();
    int t,n; cin >> t;
    while(t--){
        cin >> n;
        Tree S(n), T(n);

        for(int i = 1, u, v; i < n; i++){
            cin >> u >> v, u--, v--;
            S.add_edge(u, v);
        }

        for(int i = 1, u, v; i < n; i++){
            cin >> u >> v, u--, v--;
            T.add_edge(u, v);
        }

        cout << (isomorphic(S, 0, T, 0) ? "YES" : "NO") << '\n';
    }

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
