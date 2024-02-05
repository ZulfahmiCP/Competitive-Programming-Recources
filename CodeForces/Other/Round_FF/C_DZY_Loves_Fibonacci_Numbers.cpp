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

vector<int> fib, F;

int add(int a, const int b) {
    a += b;
    return a >= MOD ? a - MOD : a;
}

int sub(int a, const int b) {
    a -= b;
    return a < 0 ? a + MOD : a;
}

int sum(int l, int r) {
    return sub(F[r], F[l]);
}

struct SegTree {
    int N;
    vector<int> arr, tree, lazy1, lazy2;

    SegTree(int n) : N(n) {
        arr.resize(N);
        tree.resize(4 * N, 0);
        lazy1.resize(4 * N, 0);
        lazy2.resize(4 * N, 0);
    }

    void build() {
        build(0, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = add(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void single(int &x, int v, int m) {
        if(!lazy1[2 * x + 1])
            lazy1[2 * x + 1] = v;
        else 
            lazy2[2 * x + 1] = v;
        
        if(!lazy1[2 * x + 2]) 
            lazy1[2 * x + 2] = v + m;
        else 
            lazy2[2 * x + 2] = v + m;
    }

    void propagate(int &x, int &l, int &r, int &m) {
        if(!lazy1[x])
            return;

        tree[x] = add(tree[x], sum(lazy1[x] - 1, r - l + lazy1[x]));
        if(lazy2[x])
            tree[x] = add(tree[x], sum(lazy2[x] - 1, r - l + lazy2[x]));

        if(l != r){
            single(x, lazy1[x], m + 1 - l);
            if(lazy2[x])
                single(x, lazy2[x], m + 1 - l);
        }

        lazy1[x] = lazy2[x] = 0;
    }

    void update(int l, int r) {
        update(0, 0, N - 1, l, r);
    }

    void update(int x, int l, int r, int ql, int qr) {
        int m = (l + r) >> 1;

        propagate(x, l, r, m);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            tree[x] = add(tree[x], sum(l - ql, r - ql + 1));

            if(l != r)
                single(x, l - ql + 1, m + 1 - l);

            return;
        }

        update(2 * x + 1, l, m, ql, qr);
        update(2 * x + 2, m + 1, r, ql, qr);

        tree[x] = add(tree[2 * x + 1], tree[2 * x + 2]);
    }

    int ans(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }

    int query(int x, int l, int r, int ql, int qr) {
        int m = (l + r) >> 1;

        propagate(x, l, r, m);

        if(l > qr || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x];

        return add(query(2 * x + 1, l, m, ql, qr),
                   query(2 * x + 2, m + 1, r, ql, qr));
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    fib.resize(n + 1);
    F.resize(n + 1, 0);

    fib[1] = F[1] = 1;
    for(int i = 2; i <= n; i++){
        fib[i] = add(fib[i - 1], fib[i - 2]);
        F[i] = add(F[i - 1], fib[i]);
    }

    SegTree A(n);
    for(int &a : A.arr)
        cin >> a;
    A.build();

    for(int i = 0, t,l,r; i < q; i++){
        cin >> t >> l >> r;
        l--, r--;

        if(t == 1)
            A.update(l, r);
        else
            cout << A.ans(l, r) << '\n';
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
