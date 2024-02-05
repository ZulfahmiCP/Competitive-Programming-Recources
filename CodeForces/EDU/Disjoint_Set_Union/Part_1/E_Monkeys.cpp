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

struct DSU {
    int N;
    vector<int> parent, size, fall_time;
    vector<vector<int>> component;

    DSU(int n) : N(n) {
        parent.resize(n);
        size.resize(n, 1);
        fall_time.resize(n, -1);
        component.resize(n);
        iota(all(parent), 0);
    }

    int find(int x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }

    void update(int x, int t) {
        fall_time[x] = t;
        for(int v : component[x])
            update(v, t);
    }

    void unite(int x, int y, int t) {
        x = find(x), y = find(y);
        
        if(x == y) return;
        if(size[x] < size[y]) swap(x, y);
        if(!y) swap(x, y);
        if(!x) update(y, t);

        size[x] += size[y];
        parent[y] = x;
        component[x].pb(y);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<int> l(n), r(n);
    vector<pair<int, int>> op(q);
    vector hand(n, vector<bool>(2, 0));

    for(int i = 0; i < n; i++)
        cin >> l[i] >> r[i], l[i]--, r[i]--;
    for(int i = 0; i < q; i++){
        cin >> op[i].fi >> op[i].se;
        hand[--op[i].fi][--op[i].se] = 1;
    }

    DSU dsu(n);

    for(int i = 0; i < n; i++){
        if(!hand[i][0] && l[i] != -2)
            dsu.unite(i, l[i], -1);
        if(!hand[i][1] && r[i] != -2)
            dsu.unite(i, r[i], -1);
    }

    for(int i = q - 1; i >= 0; i--)
        dsu.unite(op[i].fi, op[i].se ? r[op[i].fi] : l[op[i].fi], i);

    for(int time : dsu.fall_time)
        cout << time << '\n';

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
