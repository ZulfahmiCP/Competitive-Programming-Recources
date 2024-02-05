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
void FreeOpen();

struct node {
    ll sum = 0, inc = 0, change = 0;
    bool status = 0;

    void reset() {
        status = inc = 0;
    }
};

struct SegTree {
    int N;
    vector<node> tree;

    SegTree(int n) : N(n), tree(4 * N) {}

    void push(int x) {
        for(int y = 2 * x + 1; y <= 2 * x + 2; y++){
            if(!tree[x].status){
                tree[y].inc += tree[x].inc;
                continue;
            }

            tree[y].status = 1;
            tree[y].change = tree[x].change;
            tree[y].inc = tree[x].inc;
        }
    }

    void propagate(int x, int l, int r) {
        if(tree[x].status)
            tree[x].sum = tree[x].change * (r - l + 1);
        tree[x].sum += tree[x].inc * (r - l + 1);

        if(l != r)  
            push(x);

        tree[x].reset();
    }

    void update(int l, int r, int v, bool t) {
        upgrade(0, 0, N - 1, l, r, v, t);
    }

    void upgrade(int x, int l, int r, int ql, int qr, int v, bool t) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            if(t){
                tree[x].status = 1;
                tree[x].change = v;
                tree[x].inc = 0;
            } else 
                tree[x].inc += v;

            return;
        }

        int m = (l + r) >> 1;

        upgrade(2 * x + 1, l, m, ql, qr, v, t);
        upgrade(2 * x + 2, m + 1, r, ql, qr, v, t);
        propagate(2 * x + 1, l, m);
        propagate(2 * x + 2, m + 1, r);

        tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
    }

    ll calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
    }

    ll process(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return tree[x].sum;

        int m = (l + r) >> 1;

        return process(2 * x + 1, l, m, ql, qr) +
               process(2 * x + 2, m + 1, r, ql, qr);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree A(n);

    for(int i = 0, t,l,r,v; i < q; i++){
        cin >> t >> l >> r, r--;

        if(t != 3){
            cin >> v;
            A.update(l, r, v, t & 1);
        } else 
            cout << A.calc(l, r) << '\n';
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
