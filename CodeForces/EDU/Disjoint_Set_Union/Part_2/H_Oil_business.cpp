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

struct DSU {
    int N;
    vector<int> rank, parent;

    DSU(int n) : N(n) {
        rank.resize(n, 0);
        parent.resize(n);
        iota(all(parent), 0);
    }

    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        x = find(x), y = find(y);
        
        if(x == y)
            return;
        
        if(rank[x] < rank[y])
            swap(x, y);

        if(rank[x] == rank[y])
            rank[x]++;

        parent[y] = x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

struct Edge {
    int u, v, w, i;

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct MST {
    int N;
    vector<Edge> edges;
    vector<int> ans;
    vector<bool> inMST;
    
    MST(int n) : N(n), inMST(N, 0) {}

    void add_edge(int u, int v, int w, int i) {
        edges.pb({u, v, w, i});
    }

    void solve(ll s) {
        DSU dsu(N);
        
        sort(All(edges));

        for(Edge& edge : edges){
            if(dsu.find(edge.u) != dsu.find(edge.v)){
                inMST[edge.u] = inMST[edge.v] = 1;
                dsu.unite(edge.u, edge.v);
                edge.i = -1;
            }
        }

        for(int u = 0; u < N; u++)
            if(!inMST[u])
                return;

        ll cur = 0;
        sort(all(edges));
        for(const Edge& edge : edges){
            if(cur + edge.w > s)
                break;

            if(edge.i != -1){
                cur += edge.w;
                ans.pb(edge.i);
            }
        }
    }
};

int main(){
 
    FastIO();
    ll n,m,s; cin >> n >> m >> s;
    MST mst(n);

    for(int i = 0, u,v,w; i < m; i++){
        cin >> u >> v >> w;
        u--, v--;
        mst.add_edge(u, v, w, i);
    }

    mst.solve(s);
    n = mst.ans.size();
    cout << n << '\n';
    for(int i = 0; i < n; i++)
        cout << mst.ans[i] + 1 << " \n"[i == n - 1];

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
