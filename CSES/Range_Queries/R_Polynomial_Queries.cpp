
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

void FastIO();

struct SegTree {
    int N;
    vector<int> arr;
    vector<ll> tree, A, D;

    SegTree(int n) : N(n), arr(N), A(4 * N, 0), D(4 * N, 0), tree(4 * N) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void push(int x, int m) {
        A[2 * x + 1] += A[x];
        A[2 * x + 2] += A[x] + m * D[x];
        D[2 * x + 1] += D[x];
        D[2 * x + 2] += D[x];
    }

    void propagate(int x, int l, int &r) {
        if(!A[x])
            return;

        tree[x] += (r - l + 1) * (2 * A[x] + (r - l) * D[x]) >> 1;

        if(l != r)
            push(x, (r - l) / 2 + 1);

        A[x] = D[x] = 0;
    }

    void update(int l, int r) {
        modify(0, 0, N - 1, l, r);
    }

    void modify(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            A[x] = l - ql + 1, D[x] = 1;
            propagate(x, l, r);
            return;
        }

        int m = (l + r) >> 1;

        modify(2 * x + 1, l, m, ql, qr);
        modify(2 * x + 2, m + 1, r, ql, qr);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    ll calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
    }

    ll process(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x];

        int m = (l + r) >> 1;

        return process(2 * x + 1, l, m, ql, qr) +
               process(2 * x + 2, m + 1, r, ql, qr);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree A(n);

    for(int &a : A.arr)
        cin >> a;
    A.build(0, 0, n - 1);

    for(int i = 0, t, l, r; i < q; i++){
        cin >> t >> l >> r;
        t--, l--, r--;

        if(t) cout << A.calc(l, r) << '\n';
        else A.update(l, r);
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
