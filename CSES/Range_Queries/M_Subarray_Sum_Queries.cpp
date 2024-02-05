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

struct node {
    ll pref, suff, sub, sum;
};

struct SegTree {
    int N;
    vector<int> arr;
    vector<node> tree;

    SegTree(int n) : N(n), arr(N), tree(4 * N) {}

    node combine(node a, node b) {
        return node{
            max(a.pref, a.sum + b.pref),
            max(b.suff, a.suff + b.sum),
            max({a.sub, b.sub, a.suff + b.pref}),
            a.sum + b.sum
        };
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = arr[l] > 0 ? node{arr[l], arr[l], arr[l], arr[l]} : node{0, 0, 0, arr[l]};
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    ll maxsub_after_update(int j, int v){
        modify(0, 0, N - 1, j, v);
        return tree[0].sub;
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r){
            tree[x] = v > 0 ? node({v, v, v, v}) : node{0, 0, 0, v};
            return;
        }

        int m = (l + r) >> 1;
        
        j <= m ? modify(2 * x + 1, l, m, j, v)
               : modify(2 * x + 2, m + 1, r, j, v);

        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree seg(n);

    for(int &a : seg.arr)
        cin >> a;
    seg.build(0, 0, n - 1);

    for(int i = 0, j, v; i < q; i++){
        cin >> j >> v, j--;
        cout << seg.maxsub_after_update(j, v) << '\n';
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
