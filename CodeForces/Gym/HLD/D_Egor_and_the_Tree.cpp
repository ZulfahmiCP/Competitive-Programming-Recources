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
const double EPS = 1e-9;

void FastIO();

struct MergeSortTree {
    int N;
    vector<int> arr;
    vector<vector<int>> tree;

    MergeSortTree(int n = 0) : N(n), arr(N), tree(4 * N) {}

    void pull(int x) {
        merge(all(tree[2 * x + 1]), all(tree[2 * x + 2]), back_inserter(tree[x]));
    } 

    void build(int x, int l, int r) {
        if (l == r) {
            tree[x] = {arr[l]};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);
        pull(x);
    }

    int calc(int l, int r, int v) {
        return process(0, 0, N - 1, l, r, v);
    }

    int process(int x, int l, int r, int ql, int qr, int v) {
        if(l > qr || ql > r)
            return INF;
        
        if(ql <= l && r <= qr){
            auto pos = upper_bound(all(tree[x]), v);
            return pos == tree[x].end() ? INF : *pos;
        }

        int m = (l + r) >> 1;

        return min(process(2 * x + 1, l, m, ql, qr, v),
                   process(2 * x + 2, m + 1, r, ql, qr, v));
    }
};

struct HLD {
    int N, root, cnt;
    vector<vector<int>> adj;
    vector<int> value, pos, head;
    vector<int> depth, sub, parent;
    MergeSortTree seg;
 
    HLD(int n) : N(n), cnt(0), sub(N, 1), pos(N), head(N),
                 adj(N), depth(N), value(N), parent(N), seg(N) {}
 
    void add_edge(int u, int v) {
        adj[u].pb(v);
        adj[v].pb(u);
    }
 
    void build(int rt = 0) {
        root = rt;
        depth[root] = parent[root] = 0;
        dfs_sub(0); 
        dfs_hld(0, 0);

        for(int u = 0; u < N; u++)
            seg.arr[pos[u]] = value[u];
        seg.build(0, 0, N - 1);
    }
 
    int dfs_sub(int u) {
		adj[u].erase(remove(all(adj[u]), parent[u]), adj[u].end());

        for(const int &v : adj[u]){
            depth[v] = depth[u] + 1;
            parent[v] = u;
            sub[u] += dfs_sub(v);
        }

		sort(all(adj[u]), [&](int &a, int &b) {
			return sub[a] > sub[b];
		});

        return sub[u];
    }
 
    void dfs_hld(int u, bool heavy) {
        pos[u] = cnt++;
        head[u] = heavy ? head[parent[u]] : u;
		bool heavy_child = 1;

		for(const int &v : adj[u]){
			dfs_hld(v, heavy_child);
			heavy_child = 0;
		}
    }
 
    int calc(int u, int v, int x) {
        int res = INF;

        for(;head[u] != head[v]; u = parent[head[u]]){
            if(depth[head[u]] < depth[head[v]])
                swap(u, v);
            res = min(res, seg.calc(pos[head[u]], pos[u], x));
        }
 
        if(depth[u] > depth[v])
            swap(u, v);
            
        res = min(res, seg.calc(pos[u], pos[v], x));
        return res == INF ? -1 : res;
    }
};  
 
int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    HLD tree(n);
 
    for(int &a : tree.value)
        cin >> a;
 
    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v, u--, v--;
        tree.add_edge(u, v);
    }   
    
    tree.build();
 
    for(int i = 0, u, v, x; i < q; i++){
        cin >> u >> v >> x, u--, v--;
        cout << tree.calc(u, v, x) << '\n';
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
