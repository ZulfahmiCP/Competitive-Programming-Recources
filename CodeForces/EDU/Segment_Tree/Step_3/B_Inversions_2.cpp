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

void FastIO();
void FreeOpen();

struct SegTree {
    int N;
    vector<ll> tree;

    SegTree(int n) {
        N = n;
        tree.resize(4 * N);
    }

    void build() {
        build(0, 0, N - 1);
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = 1;
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void update(int j){
        update(0, 0, N - 1, j);
    }

    void update(int x, int l, int r, int j) {
        if(l == r){
            tree[x] = 0;
            return;
        }

        int m = (l + r) / 2;
        j <= m ? update(2 * x + 1, l, m, j)
               : update(2 * x + 2, m + 1, r, j);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    ll query(int k) {
        return query(0, 0, N - 1, k);
    }

    ll query(int x, int l, int r, int k) {
        if(l == r)
            return l;
        
        int m = (l + r)/2, num = tree[2 * x + 1];
        return num > k ? query(2 * x + 1, l, m, k)
                        : query(2 * x + 2, m + 1, r, k - num);
    }
};


int main(){
 
    FastIO();
    int n; cin >> n;
    vector<int> A(n), ans(n);

    for(int &a : A)
        cin >> a, a--;

    SegTree seg(n);
    seg.build();

    for(int i = n - 1; i >= 0; i--){
        ans[i] = seg.query(A[i] + 1);
        seg.update(ans[i]);
    }

    for(int &a : ans)
        cout << n - a << ' ';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void prd(const T& x){ cerr << x; }
template <typename T, typename U>void prd(const pair<T, U>& vue){ cerr << "("; prd(vue.first); cerr << ", "; prd(vue.second); cerr << ")"; }
template <typename T, typename... Args>void prd(const T& vue, Args... args){prd(vue); cerr << ", "; prd(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  prd(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& cont){ cerr << '['; bool cm = 0; for(auto [k, v] : cont){ if(cm) cerr << ", "; cerr << '['; prd(k); cerr << ", "; prd(v); cerr << ']'; cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& cont) { cerr << '['; bool cm = 0; for (const auto& st : cont) { if (cm) cerr << ", "; prd(st); cm = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& cont) { cerr << '['; bool cm = 0; for (const auto& v : cont){ if(cm) cerr << ", "; prd(v); cm = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &cont) { for (const auto &v : cont) debug(v); cerr << '\n';}
