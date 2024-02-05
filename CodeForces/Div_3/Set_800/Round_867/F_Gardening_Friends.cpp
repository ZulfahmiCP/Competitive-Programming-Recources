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

int main(){
 
    FastIO();
    ll t,n,k,c,ans; cin >> t;
    while(t--){
        cin >> n >> k >> c;
        vector<vector<int>> tree(n);
        vector<int> depth(n, 0), dist(n, 0);

        for(int i = 1, u,v; i < n; i++){
            cin >> u >> v;
            u--, v--;
            tree[u].pb(v);
            tree[v].pb(u);
        }

        function<void(int, int)> dfs = [&](int u, int p) -> void {
            if(p != -1)
                depth[u] = depth[p] + 1;

            for(int &v : tree[u]){
                if(v == p)
                    continue;
                dfs(v, u);
                dist[u] = max(dist[u], dist[v] + 1);
            }
        };

        function<void(int, int)> explore = [&](int u, int p) -> void {
            ans = max(ans, k * dist[u] - c * depth[u]);
            
            sort(all(tree[u]), [&](int &a, int &b) {
                return dist[a] > dist[b];
            });

            int temp1, temp2;
            for(int i = 0, v; i < tree[u].size(); i++){
                v = tree[u][i];
                if(p == v)
                    continue;
                
                temp1 = dist[u];
                dist[u] = 0;

                for(int w = 0; w < min((int)tree[u].size(), 3); w++)
                    if(w != i)
                        dist[u] = max(dist[u], dist[tree[u][w]] + 1);
                
                temp2 = dist[v];
                dist[v] = max(dist[v], dist[u] + 1);
                explore(v, u);

                dist[u] = temp1;
                dist[v] = temp2;
            }
        };

        dfs(0, -1);
        ans = 0;
        explore(0, -1);
        cout << ans << '\n';
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
