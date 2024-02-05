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
    vector<int> parent, size;

    DSU(int n) {
        N = n;
        parent.resize(N);
        iota(all(parent), 0);
        size.resize(N, 1);
    }

    int find(int x) {
        return (x == parent[x]) ? x : (parent[x] = find(parent[x]));
    }

    void join(int x, int y) {
        x = find(x), y = find(y);

        if(x == y)
            return;

        if(size[x] < size[y])
            swap(x, y);
        
        parent[y] = x;
        size[x] += size[y];
        size[y] = 0;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

struct query {
    int u,v;
    bool ask, same;
};

int main(){
 
    FastIO();
    int n,m,q; cin >> n >> m >> q;

    for(int i = 0, u,v; i < m; i++)
        cin >> u >> v;

    string s;
    DSU dsu(n);
    vector<query> op(q);
    vector<bool> ans(q);
    
    for(int i = 0; i < q; i++){
        cin >> s >> op[i].u >> op[i].v;
        op[i].ask = s == "ask", op[i].u--, op[i].v--;
    }

    for(int i = q - 1; i >= 0; i--){
        if(op[i].ask)
            op[i].same = dsu.same(op[i].u, op[i].v);
        else    
            dsu.join(op[i].u, op[i].v);
    }

    for(int i = 0; i < q; i++)
        if(op[i].ask)
            cout << (op[i].same ? "YES" : "NO") << '\n';

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
