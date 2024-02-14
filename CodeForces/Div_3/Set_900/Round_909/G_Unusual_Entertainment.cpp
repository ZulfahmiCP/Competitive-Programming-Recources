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

    MergeSortTree(int n) : N(n), arr(N), tree(4 * N) {}
    MergeSortTree(const vector<int> &A) : arr(A), N(sz(A)), tree(4 * N) {
        build(0, 0, N - 1);
    }

    void pull(int x) {
        merge(all(tree[2 * x + 1]), all(tree[2 * x + 2]), back_inserter(tree[x]));
    } 

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = {arr[l]};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);
        pull(x);
    }

    void update(int j, int v) {
        modify(0, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r){
            tree[x] = {v};
            return;
        }

        int m = (l + r) >> 1;

        j <= m ? modify(2 * x + 1, l, m, j, v)
               : modify(2 * x + 2, m + 1, r, j, v);
        pull(x);
    }

    int calc(int l, int r, int mn, int mx) {
        return process(0, 0, N - 1, l, r, mn, mx);
    }

    int calc(int l, int r, int v) {
        return calc(l, r, v, v);
    }

    int process(int x, int l, int r, int ql, int qr, int mn, int mx) {
        if(qr < l || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return upper_bound(all(tree[x]), mx) - lower_bound(all(tree[x]), mn);

        int m = (l + r) >> 1;

        return process(2 * x + 1, l, m, ql, qr, mn, mx) + 
               process(2 * x + 2, m + 1, r, ql, qr, mn, mx);
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

        function<void(int, int)> explore = [&](int x, int parent) -> void {
            tin[x] = timer++;
            
            for(int adjx : adjList[x])
                if(adjx != parent)
                    explore(adjx, x);
            
            tout[x] = timer - 1;
        };

        timer = 0;
        explore(0, -1);

        for(int i = 0; i < n; i++)
            A[i] = tin[P[i]];

        MergeSortTree mst(A);

        for(int i = 0, l, r, x; i < q; i++){
            cin >> l >> r >> x;
            l--, r--, x--;
            cout << (mst.calc(l, r, tin[x], tout[x]) ? "YES" : "NO") << '\n';
        }

        cout << '\n';
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
