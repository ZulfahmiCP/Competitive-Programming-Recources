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
const int INF = 2e9;

void FastIO();

struct SegTree {
    struct node {
        ll sum;
        int mx, smx, mxc;
    };

    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n) : N(n), arr(N),  tree(4 * N) {}

    void push(int x, int v) {
        if(tree[x].mx > v){
            tree[x].sum -= 1LL * (tree[x].mx - v) * tree[x].mxc;
            tree[x].mx = v;
        }
    }

    void push(int x) {
        push(2 * x + 1, tree[x].mx);
        push(2 * x + 2, tree[x].mx);
    }

    void pull(int x) {
        tree[x] = {
            tree[2 * x + 1].sum + tree[2 * x + 2].sum,
            max(tree[2 * x + 1].mx, tree[2 * x + 2].mx),
            max(tree[2 * x + 1].smx, tree[2 * x + 2].smx),
            0
        };

        for(int y : {2 * x + 1, 2 * x + 2}){
            if(tree[y].mx == tree[x].mx)
                tree[x].mxc += tree[y].mxc;
            else 
                tree[x].smx = max(tree[x].smx, tree[y].mx);
        }
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = {arr[l], arr[l], -INF, 1};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);
        pull(x);
    }

    void update(int l, int r, int v) {
        modify(0, 0, N - 1, l, r, v);
    }

    void modify(int x, int l, int r, int ql, int qr, int v) {
        if(l > qr || ql > r || tree[x].mx <= v)  
            return;

        if(ql <= l && r <= qr && tree[x].smx < v){
            push(x, v);
            return;
        }

        int m = (l + r) >> 1;

        push(x);
        modify(2 * x + 1, l, m, ql, qr, v);
        modify(2 * x + 2, m + 1, r, ql, qr, v);
        pull(x);
    }

    ll calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
    }

    ll process(int x, int l, int r, int ql, int qr) {
        if(l > qr || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x].sum;

        int m = (l + r) >> 1;
        push(x);

        return process(2 * x + 1, l, m, ql, qr) +
               process(2 * x + 2, m + 1, r, ql, qr);
    }
};

int main(){
 
    FastIO();
    int n; cin >> n;
    SegTree A(n);

    for(int &a : A.arr)
        cin >> a;
    A.build(0, 0, n - 1);

    int q,t,l,r,v; cin >> q;
    while(q--){
        cin >> t >> l >> r, l--, r--;

        if(t == 1){
            cin >> v;
            A.update(l, r, v);
        } else 
            cout << A.calc(l, r) << '\n';
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
