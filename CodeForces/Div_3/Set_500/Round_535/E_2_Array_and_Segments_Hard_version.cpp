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

struct SegTree {
    int N;
    vector<int> arr, tree, lz;

    SegTree(int n) : N(n), arr(N), tree(4 * N), lz(4 * N, 0) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void propagate(int x, int l, int r) {
        if(!lz[x])
            return;

        tree[x] += lz[x];

        if(l != r){
            lz[2 * x + 1] += lz[x];
            lz[2 * x + 2] += lz[x];
        }

        lz[x] = 0;
    }

    void update(int l, int r, int v) {
        modify(0, 0, N - 1, l, r, v);
    }

    void modify(int x, int l, int r, int ql, int qr, int v) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            lz[x] = v;
            propagate(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify(2 * x + 1, l, m, ql, qr, v);
        modify(2 * x + 2, m + 1, r, ql, qr, v);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    SegTree A(n);

    for(int &a : A.arr)
        cin >> a;

    A.build(0, 0, n - 1);

    vector<pair<int, int>> seg(m);

    for(auto &[a, b] : seg)
        cin >> a >> b, a--, b--;

    int mx = 0;
    vector<int> ans;
    for(int i = 0; i < n; i++){
        for(auto &[l, r] : seg)
            if(!(l <= i && i <= r))
                A.update(l, r, -1);

        if(A.arr[i] - A.tree[0] > mx){
            mx = A.arr[i] - A.tree[0];
            ans.clear();
            for(int j = 0; j < m; j++)
                if(!(seg[j].fi <= i && i <= seg[j].se))
                    ans.pb(j);
        }

        for(auto &[l, r] : seg)
            if(!(l <= i && i <= r))
                A.update(l, r, 1);
    }

    n = sz(ans);
    cout << mx << '\n' << n << '\n';
    for(int i = 0; i < n; i++)
        cout << ans[i] + 1 << " \n"[i == n - 1];

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
