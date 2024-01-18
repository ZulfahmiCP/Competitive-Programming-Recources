

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
#define ull unsigned long long int
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void printDbg(const T& x);
template <typename T, typename U>
    void printDbg(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDbg(const T& value, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& container);
template <typename T>
    void debug(const set<T>& container);
template <typename T>
    void debug(const vector<T>& container);
template <typename T>
    void debug(const vector<vector<T>> &container);

const int MOD = 1e9 + 7;
const int mod = 998244353;

void FastIO();
void FreeOpen();

struct MergeSortTree {
    int N;
    vector<int> A;
    vector<vector<int>> tree;

    MergeSortTree(const vector<int>& arr) {
        A = arr;
        N = A.size();
        tree.resize(4 * N);
        build(0, 0, N);
    }

    void build(int node, int l, int r) {
        if (l + 1 == r) {
            tree[node].pb(A[l]);
            return;
        }

        int m = (l + r) / 2;
        build(2 * node + 1, l, m);
        build(2 * node + 2, m, r);

        merge(all(tree[2 * node + 1]), all(tree[2 * node + 2]), back_inserter(tree[node]));
    }

    int query(int node, int l, int r, int L, int R, int mn, int mx) {
        if(R <= l || r <= L)
            return 0;
        if(L <= l && r <= R) 
            return lower_bound(all(tree[node]), mx) - lower_bound(all(tree[node]), mn);

        int m = (l + r) / 2;
        int cntL = query(2 * node + 1, l, m, L, R, mn, mx);
        int cntR = query(2 * node + 2, m, r, L, R, mn, mx);

        return cntL + cntR;
    }

    int query(int l, int r, int mn, int mx) {
        return query(0, 0, N, l, r, mn, mx);
    }
};

int main(){
 
    FastIO();
    int t,n,q,timer; cin >> t;
    while(t--){
        cin >> n >> q;
        vector<int> A(n), P(n), tin(n), tout(n);
        vector<vector<int>> adjList(n);

        for(int i = 1, u,v; i < n; i++){
            cin >> u >> v;
            u--, v--;
            adjList[u].pb(v);
            adjList[v].pb(u);
        }

        for(int &p : P) 
            cin >> p, p--;

        function<void(int, int)> explore = [&](int node, int parent) -> void {
            tin[node] = timer++;
            
            for(int adjNode : adjList[node])
                if(adjNode != parent)
                    explore(adjNode, node);
            
            tout[node] = timer;
        };

        timer = 0;
        explore(0, -1);

        for(int i = 0; i < n; i++)
            A[i] = tin[P[i]];

        MergeSortTree mst(A);

        for(int i = 0, l, r, x; i < q; i++){
            cin >> l >> r >> x;
            l--, r--, x--;
            cout << (mst.query(l, r + 1, tin[x], tout[x]) ? "YES" : "NO") << '\n';
        }

        cout << '\n';
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& value){ cerr << "("; printDbg(value.first); cerr << ", "; printDbg(value.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& value, Args... args){printDbg(value); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
