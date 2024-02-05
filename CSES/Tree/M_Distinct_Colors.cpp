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
const int MX = 2e5 + 5;

void FastIO();
void FreeOpen();

int BLOCK;

struct query {
    int l, r, i;
    
    bool operator<(const query &other) const {
        return make_pair(l / BLOCK, r) < make_pair(other.l / BLOCK, other.r);
    }
};

struct MO {
    int N, Q, ans;
    vector<int> arr, res;
    vector<query> queries;
    vector<int> occ;

    MO(int n) : N(n), Q(0), ans(0), arr(N) {
        BLOCK = sqrt(N);
        occ.resize(MX, 0);
    }

    void add_query(int l, int r) {
        queries.pb({l, r, Q++});
    }

    void add(int i) {
        if(!occ[arr[i]])
            ans++;
        occ[arr[i]]++;
    }
   
    void remove(int i) {
        occ[arr[i]]--;
        if(!occ[arr[i]])
            ans--;
    }

    void process() {
        res.resize(Q);
        sort(all(queries));

        int L = queries[0].l, R = queries[0].l - 1;

        for(const auto& q : queries) {
            while(L > q.l)
                add(--L);
            while(L < q.l)
                remove(L++);
            while(R < q.r)
                add(++R);
            while(R > q.r)
                remove(R--);
            
            res[q.i] = ans;
        }
    }
};

struct FT {
    int N, timer;
    vector<vector<int>> tree;
    vector<int> tour, in, out;

    FT(int n) : N(n), timer(0), tree(N), in(N, 0), out(N, 0) {}

    void build(int root = 0) {
        dfs(root, -1);
    }

    void add_edge(int u, int v) {
        tree[u].pb(v);
        tree[v].pb(u);
    }

    void dfs(int u, int p) {
        tour.pb(u);
        in[u] = timer++;

        for(int v : tree[u])
            if(v != p)
                dfs(v, u);

        tour.pb(u);
        out[u] = timer++;
    }
};

int main(){
 
    FastIO();
    int n, cur(0); cin >> n;
    vector<int> color(n);
    Map<int, int> other;
    FT tree(n);

    for(int &c : color){
        cin >> c;

        if(other.find(c) != other.end())
            c = other[c];
        else 
            c = other[c] = cur++;
    }

    for(int i = 1, u, v; i < n; i++){
        cin >> u >> v;
        u--, v--;
        tree.add_edge(u, v);
    }

    tree.build();

    MO mo(2 * n);

    for(int u = 0; u < n; u++)
        mo.add_query(tree.in[u], tree.out[u]);
        
    for(int i = 0; i < 2 * n; i++)
        mo.arr[i] = color[tree.tour[i]];

    mo.process();

    for(int i = 0; i < n; i++)
        cout << mo.res[i] << " \n"[i == n - 1];

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
