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

struct node {
    ll pref, suff, seg, sum;
};

struct SegTree {
    int N;
    vector<int> A;
    vector<node> tree;

    SegTree(const vector<int> &arr) {
        A = arr, N = A.size();
        tree.resize(4 * N);
        build(0, 0, N - 1);
    }

    node combine(node a, node b) {
        return node{
            max(a.pref, a.sum + b.pref),
            max(b.suff, a.suff + b.sum),
            max({a.seg, b.seg, a.suff + b.pref}),
            a.sum + b.sum
        };
    }

    node combine(int a) {
        return (a > 0 ? node{a, a, a, a} : node{0, 0, 0, a});
    }

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = combine(A[l]);
            return;
        }

        int m = (l + r) / 2;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void update(int index, int val){
        update(0, 0, N - 1, index, val);
    }

    void update(int x, int l, int r, int index, int val) {
        if(l == r){
            tree[x] = combine(val);
            A[l] = val;
            return;
        }

        int m = (l + r) / 2;
        index <= m ? update(2 * x + 1, l, m, index, val)
                   : update(2 * x + 2, m + 1, r, index, val);

        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<int> A(n);

    for(int &a : A)
        cin >> a;
    
    SegTree seg(A);

    cout << seg.tree[0].seg << '\n';
    for(int i = 0, pos, v; i < q; i++){
        cin >> pos >> v;
        seg.update(pos, v);
        cout << seg.tree[0].seg << '\n';
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
