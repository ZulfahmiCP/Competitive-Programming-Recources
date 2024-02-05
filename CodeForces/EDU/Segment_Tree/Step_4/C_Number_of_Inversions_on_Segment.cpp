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

struct arr {
    ll inv = 0;
    array<int, 40> occ{0};

    arr() {}
};

struct SegTree {
    int N;
    vector<int> A;
    vector<arr> tree;

    SegTree(int n) {
        N = n;
        A.resize(N);
        tree.resize(4 * N);
    }

    arr combine(arr a, arr b) {
        arr c;

        for(int i = 0, cur = 0; i < 40; i++){
            c.occ[i] = a.occ[i] + b.occ[i];
            c.inv += 1LL * cur * a.occ[i];
            cur += b.occ[i];
        }

        c.inv += a.inv + b.inv;

        return c;
    }

    void build() {
        build(0, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x].occ[A[l]]++;
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int j, int v){
        update(0, 0, N - 1, j, v);
    }

    void update(int x, int l, int r, int j, int v) {
        if(l == r){
            tree[x].occ[A[l]]--;
            A[l] = v;
            tree[x].occ[A[l]]++;
            return;
        }

        int m = (l + r) >> 1;
        j <= m ? update(2 * x + 1, l, m, j, v)
               : update(2 * x + 2, m + 1, r, j, v);

        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    ll ans(int l, int r) {
        return query(0, 0, N - 1, l, r).inv;
    }

    arr query(int x, int l, int r, int ql, int qr) {
        if(l > qr || r < ql)
            return arr();
        if(ql <= l && r <= qr)
            return tree[x];
        
        int m = (l + r) >> 1;
        return combine(query(2 * x + 1, l, m, ql, qr),
                       query(2 * x + 2, m + 1, r, ql, qr));
    }
};


int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int &a : seg.A)
        cin >> a, a--;

    seg.build();

    for(int i = 0, t,l,r,j,v; i < q; i++){
        cin >> t;

        if(t == 2){
            cin >> j >> v;
            seg.update(--j, --v);
        } else {
            cin >> l >> r;
            cout << seg.ans(--l, --r) << '\n';
        }
    }

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
