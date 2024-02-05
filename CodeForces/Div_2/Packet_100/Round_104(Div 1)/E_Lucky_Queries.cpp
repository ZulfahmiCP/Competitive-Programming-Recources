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
    void printDbg(const pair<T, U>& v);
template <typename T, typename... Args>
    void printDbg(const T& v, Args... args);
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

struct node {
    int a = 0, b = 0, c = 1, d = 1;
};

struct SegTree {
    int N;
    string S;
    vector<node> tree;
    vector<bool> extra;

    SegTree(int n) : N(n), tree(4 * N), extra(4 * N) {}

    node merge(node x, node y, bool flip = 0) {
        return {
            x.a + y.a, x.b + y.b,
            max({x.a + y.b, x.c + y.b, x.a + y.c}),
            max({x.b + y.a, x.d + y.a, x.b + y.d})
        };
    }

    void build(int x, int l, int r) {
        if(l == r){
            S[l] == '4' ? tree[x].a++ : tree[x].b++;
            return;
        }

        int m = (l + r) >> 1;

        build(2 * x + 1, l, m);
        build(2 * x + 2, m + 1, r);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void push(int x) {
        extra[2 * x + 1] = !extra[2 * x + 1];
        extra[2 * x + 2] = !extra[2 * x + 2];
    }

    void propagate(int x, int l, int r) {
        if(!extra[x])
            return;

        swap(tree[x].a, tree[x].b);
        swap(tree[x].c, tree[x].d);

        if(l != r)
            push(x);

        extra[x] = 0;
    }

    void update(int l, int r) {
        upgrade(0, 0, N - 1, l, r);
    }

    void upgrade(int x, int l, int r, int ql, int qr) {
        propagate(x, l, r);

        if(l > qr || ql > r)
            return;

        if(ql <= l && r <= qr){
            swap(tree[x].a, tree[x].b);
            swap(tree[x].c, tree[x].d);

            if(l != r)
                push(x);

            return;
        }

        int m = (l + r) >> 1;

        upgrade(2 * x + 1, l, m, ql, qr);
        upgrade(2 * x + 2, m + 1, r, ql, qr);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    SegTree A(n); cin >> A.S;

    A.build(0, 0, n - 1);

    string s;
    for(int i = 0, l, r; i < q; i++){
        cin >> s;

        if(s[0] == 's'){
            cin >> l >> r;
            l--, r--;
            A.update(l, r);
        } else 
            cout << A.tree[0].c << '\n';
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& v){ cerr << "("; printDbg(v.first); cerr << ", "; printDbg(v.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& v, Args... args){printDbg(v); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
