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

void FastIO();

struct SegTree {
    int N;
    vector<int> A, B, tree;

    SegTree(int n) : N(n), A(N), B(N), tree(4 * N, -1) {}

    void propagate(int x, int l, int r) {
        if(tree[x] == -1)
            return;

        if(l == r){
            A[l] = B[tree[x]];
            return;
        }

        tree[2 * x + 1] = tree[x];
        tree[2 * x + 2] = tree[x] + (r - l) / 2 + 1;

        tree[x] = -1;
    }

    void update(int l, int r, int j) {
        modify(0, 0, N - 1, l, r, j);
    }

    void modify(int x, int l, int r, int ql, int qr, int j) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return;
        if(ql <= l && r <= qr){
            tree[x] = l - ql + j;
            propagate(x, l, r);

            return;
        }

        int m = (l + r) >> 1;

        modify(2 * x + 1, l, m, ql, qr, j);
        modify(2 * x + 2, m + 1, r, ql, qr, j);
    }

    int val(int j) {
        return process(0, 0, N - 1, j);
    }

    int process(int x, int l, int r, int j) {
        propagate(x, l, r);

        if(l == r){
            return A[l];
        }

        int m = (l + r) >> 1;

        return (j <= m ? process(2 * x + 1, l, m, j) : 
                         process(2 * x + 2, m + 1, r, j));
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int &x : seg.B) cin >> x;
    for(int &x : seg.A) cin >> x;

    for(int i = 0, t, la, lb, k; i < q; i++){
        cin >> t;

        if(t == 1){
            cin >> lb >> la >> k;
            la--, lb--;
            seg.update(la, la + k - 1, lb);
        } else {
            cin >> k, k--;
            cout << seg.val(k) << '\n';
        }
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
