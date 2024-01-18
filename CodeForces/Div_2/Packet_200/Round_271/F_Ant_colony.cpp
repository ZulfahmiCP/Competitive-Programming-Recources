
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

struct MinSegTree {
    int N;
    vector<int> A;
    vector<pair<int, int>> tree;

    MinSegTree(const vector<int> &arr) {
        A = arr, N = A.size();
        tree.resize(4 * N);
        build(0, 0, N - 1);
    }

    pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
        if(a.fi < b.fi)
            return a;
        if(b.fi < a.fi)
            return b;
        return {a.fi, a.se + b.se};
    }

    void build(int node, int l, int r) {
        if(l == r){
            tree[node] = {A[l], 1};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * node + 1, l, m);
        build(2 * node + 2, m + 1, r);

        tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
    }

    pair<int, int> query(int node, int l, int r, int ql, int qr) {
        if(l > qr || r < ql)
            return {INT_MAX, 0};
        if(ql <= l && r <= qr)
            return tree[node];

        int m = (l + r) >> 1;
        return combine(query(2 * node + 1, l, m, ql, qr),
                       query(2 * node + 2, m + 1, r, ql, qr));
    } 

    pair<int, int> query(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }
};

struct SegTree {
    int N;
    vector<int> A;
    vector<ll> tree;

    SegTree(const vector<int> &arr) {
        A = arr, N = A.size();
        tree.resize(4 * N);
        build(0, 0, N - 1);
    }

    void build(int node, int l, int r) {
        if(l == r){
            tree[node] = A[l];
            return;
        }

        int m = (l + r) / 2;

        build(2 * node + 1, l, m);
        build(2 * node + 2, m + 1, r);

        tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void update(int node, int l, int r, int index, int val) {
        if(l == r){
            tree[node] = val;
            return;
        }

        int m = (l + r) / 2;
        index <= m ? update(2 * node + 1, l, m, index, val)
                   : update(2 * node + 2, m + 1, r, index, val);

        tree[node] = gcd(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void update(int index, int val){
        update(0, 0, N - 1, index, val);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if(l > qr || r < ql)
            return 0;
        if(ql <= l && r <= qr)
            return tree[node];
        
        int m = (l + r)/2;
        return gcd(query(2 * node + 1, l, m, ql, qr),
                   query(2 * node + 2, m + 1, r, ql, qr));
    }

    ll query(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }
};


int main(){
 
    FastIO();
    int n; cin >> n;
    vector<int> A(n);

    for(int &a : A)
        cin >> a;

    MinSegTree mst(A);
    SegTree st(A);

    int q; cin >> q;
    for(int i = 0, l,r; i < q; i++){
        cin >> l >> r;
        l--, r--;
        
        int g = st.query(l, r);
        pair<int, int> cur = mst.query(l, r);

        cout << r - l + 1 - (cur.fi == g ? cur.se : 0) << '\n';
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
