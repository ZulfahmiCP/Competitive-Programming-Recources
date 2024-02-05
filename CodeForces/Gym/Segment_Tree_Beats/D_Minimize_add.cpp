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
    void prd(const pair<T, U>& vue);
template <typename T, typename... Args>
    void prd(const T& vue, Args... args);
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
const ll INFLL = 1e17 + 7;

void FastIO();

struct SegTree {
    struct node {
        ll sum, max, smax, maxc, lz = 0;
    };

    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    void pull(int x) {
        int l = 2 * x + 1, r = 2 * x + 2;

        tree[x] = {
            tree[l].sum + tree[r].sum,
            max(tree[l].max, tree[r].max),
            max(tree[l].smax, tree[r].smax),
            0
        };
        
        for(int y : {l, r}){
            if(tree[x].max == tree[y].max) tree[x].maxc += tree[y].maxc;
            else tree[x].smax = max(tree[x].smax, tree[y].max);
        }
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = {arr[l], arr[l], -INFLL, 1};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);
        pull(x);
    }
 
    void push_min(int x, ll v) {
        if(tree[x].max > v){
            tree[x].sum -= (tree[x].max - v) * tree[x].maxc;
            tree[x].max = v;
        }
    }

    void push_sum(int x, int l, int r, ll v) {
        tree[x].max += v;
        tree[x].smax += v;
        tree[x].sum += v * (r - l + 1);
        tree[x].lz += v;
    }
 
    void push(int x, int l, int r) {
        if(l == r) 
            return;

        int m = (l + r) >> 1;

        if(tree[x].lz){
            push_sum(2 * x + 1, l, m, tree[x].lz);
            push_sum(2 * x + 2, m + 1, r, tree[x].lz);
            tree[x].lz = 0;
        }

        push_min(2 * x + 1, tree[x].max);
        push_min(2 * x + 2, tree[x].max);
    }
 
    void modify_min(int x, int l, int r, int ql, int qr, int v) {
        if(qr < l || r < ql || tree[x].max <= v) 
            return;

        if(ql <= l && r <= qr && tree[x].smax < v){
            push_min(x, v);
            return;
        }

        int m = (l + r) >> 1;

        push(x, l, r);
        modify_min(2 * x + 1, l, m, ql, qr, v);
        modify_min(2 * x + 2, m + 1, r, ql, qr, v);
        pull(x);
    }
 
    void update_min(int l, int r, int v) {
        modify_min(0, 0, N - 1, l, r, v);
    }
 
    void modify_sum(int x, int l, int r, int ql, int qr, int v) {
        if(qr < l || r < ql) 
            return;

        if(ql <= l && r <= qr){
            push_sum(x, l, r, v);
            return;
        }

        int m = (l + r) >> 1;

        push(x, l, r);
        modify_sum(2 * x + 1, l, m, ql, qr, v);
        modify_sum(2 * x + 2, m + 1, r, ql, qr, v);
        pull(x);
    }
 
    void update_sum(int l, int r, int v) {
        modify_sum(0, 0, N - 1, l, r, v);
    }
 
    ll process_sum(int x, int l, int r, int ql, int qr) {
        if(qr < l || r < ql) 
            return 0;

        if(ql <= l && r <= qr) 
            return tree[x].sum;

        int m = (l + r) >> 1;
        push(x, l, r);

        return process_sum(2 * x + 1, l, m, ql, qr) + 
               process_sum(2 * x + 2, m + 1, r, ql, qr);
    }
 
    ll calc_sum(int l, int r) {
        return process_sum(0, 0, N - 1, l, r);
    }
};
 
int main() {
    
    FastIO();
    int n; cin >> n;
    SegTree seg(n);
    
    for(int &a : seg.arr)
        cin >> a;
    seg.build(0, 0, n - 1);

    int q,t,l,r,v; cin >> q;
    while(q--){
        cin >> t >> l >> r, l--, r--;

        if(t == 1){
            cin >> v;
            seg.update_min(l, r, v);
        } else if(t == 2) {
            cin >> v;
            seg.update_sum(l, r, v);
        } else 
            cout << seg.calc_sum(l, r) << '\n';
    }
    
    return 0;
}

 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& vue){ cerr << "("; prd(vue.first); cerr << ", "; prd(vue.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& vue, Args... args){prd(vue); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
