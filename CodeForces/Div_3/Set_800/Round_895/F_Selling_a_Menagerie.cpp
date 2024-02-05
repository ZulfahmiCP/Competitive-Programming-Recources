#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <climits>
#include <cstring>
#include <numeric>
#include <iomanip>
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
#define sz(x) (int)x.size()
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
const int INF = 2e9 + 7;
const ll INFLL = 9e18 + 7;

void FastIO();

int main(){
 
    FastIO();
    int t,n,best; cin >> t;
    while(t--){
        cin >> n;
        vector<vector<int>> graph(n);
        vector<int> cost(n), deg(n, 0), ans;
        vector<bool> vis(n, 0), vis2(n, 0);

        for(int u = 0, v; u < n; u++){
            cin >> v, v--;
            graph[u].pb(v);
            deg[v]++;
        }

        for(int &c : cost)
            cin >> c;

        queue<int> explore;
        for(int u = 0; u < n; u++)
            if(!deg[u])
                explore.push(u);

        for(int u; !explore.empty();){
            u = explore.front();
            explore.pop();

            ans.pb(u);
            vis[u] = 1;

            for(const int &v : graph[u])
                if(!(--deg[v]))
                    explore.push(v);
        }

        function<void(int)> dfs = [&](int u) -> void {
            vis2[u] = 1;
            if(cost[u] < cost[best]) 
                best = u;
            
            for(const int &v : graph[u])
                if(!vis2[v])
                    dfs(v);
        };

        function<void(int)> dfs2 = [&](int u) -> void {
            vis[u] = 1;
            ans.pb(u);

            for(const int &v : graph[u])
                if(vis2[v] && !vis[v])
                    dfs2(v);
        };

        for(int u = 0; u < n; u++){
            if(vis[u])
                continue;

            best = u;
            dfs(u);
            dfs2(graph[best][0]);
        }

        for(int i = 0; i < n; i++)
            cout << ans[i] + 1 << " \n"[i == n - 1];
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
