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

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct DSU {
    int N, M;
    vector<int> parent, rank, checkpoints;
    stack<pair<int, int>> history;

    DSU(int n) : N(n), M(N), parent(N), rank(N, 1) {
        iota(all(parent), 0);
    }

    int find(int x) {
        return x == parent[x] ? x : find(parent[x]);
    }

    int unite(int x, int y) {
        x = find(x), y = find(y);

        if(x == y)
            return M;

        if(rank[x] < rank[y])
            swap(x, y);

        history.push({y, parent[y]});
        parent[y] = x;
        
        return (--M);
    }

    void persist() {
        checkpoints.pb(history.size());
    }

    int rollback() {
        int target = checkpoints.back();

        while(history.size() > target){
            auto& [x, par] = history.top();
            parent[x] = par;
            M += x == par;
            history.pop();
        }

        checkpoints.pop_back();

        return M;
    }
};

int main() {

    FastIO();
    int n, q; cin >> n >> q;
    DSU dsu(n);

    string op;
    for(int i = 0, u, v; i < q; i++){
        cin >> op;

        if(op[0] == 'u'){
            cin >> u >> v, u--, v--;
            cout << dsu.unite(u, v) << '\n';
        } else if(op[0] == 'r')
            cout << dsu.rollback() << '\n';
        else    
            dsu.persist();
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
