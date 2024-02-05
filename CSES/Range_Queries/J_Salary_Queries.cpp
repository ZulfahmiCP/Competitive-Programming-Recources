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
    vector<int> cnt, tree;

    SegTree(int n) : N(n), cnt(N, 0), tree(4 * N) {}

    void build(int x, int l, int r) {
        if(l == r){
            tree[x] = cnt[l];
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void update(int j, int v){
        modify(0, 0, N - 1, j, v);
    }

    void modify(int x, int l, int r, int j, int v) {
        if(l == r){
            tree[x] += v;
            return;
        }

        int m = (l + r) >> 1;
        
        j <= m ? modify(2 * x + 1, l, m, j, v)
               : modify(2 * x + 2, m + 1, r, j, v);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    int calc(int l, int r) {
        return process(0, 0, N - 1, l, r);
    }

    int process(int x, int l, int r, int ql, int qr) {
        if(l > qr || r < ql)
            return 0;
        if(ql <= l && r <= qr)
            return tree[x];
        
        int m = (l + r) >> 1;
        return process(2 * x + 1, l, m, ql, qr) + 
               process(2 * x + 2, m + 1, r, ql, qr);
    }
};

struct query {
    char op;
    int a, b;
};

int main(){
 
    FastIO();
    int n,q,cur(0); cin >> n >> q;
    vector<int> A(n), op;
    Map<int, int> who;

    for(int &a : A){
        cin >> a, a--;
        op.pb(a);
    }

    vector<query> queries(q);
    for(auto &q : queries){
        cin >> q.op >> q.a >> q.b;
        --q.b, --q.a;
        op.pb(q.b);
        if(q.op == '?')
            op.pb(q.a);
    }

    sort(all(op));
    for(int i = 0; i < (int)op.size(); i++){
        if(i && op[i] == op[i - 1])
            continue;
        who[op[i]] = cur++;
    }

    n = cur;

    SegTree seg(n);
    for(int &a : A){
        a = who[a];
        seg.cnt[a]++;
    }

    seg.build(0, 0, n - 1);

    for(auto &q : queries){
        q.b = who[q.b];
        
        if(q.op == '!'){
            seg.update(A[q.a], -1);
            A[q.a] = q.b;
            seg.update(A[q.a], 1);
        } else {
            q.a = who[q.a];
            cout << seg.calc(q.a, q.b) << '\n';
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
