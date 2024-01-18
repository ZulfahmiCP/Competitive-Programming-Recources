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
#define X first 
#define Y second 
#define Int int64_t
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define ull unsigned long long int
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void printDbg(const T& x);
template <typename T, typename U>
    void printDbg(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDbg(const T& value, Args... args);
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

int valid_cycle(int n, int m) {
    int k = sqrt(n);
    if(k * k != n || k * (k + 1) != m)
        return 0;
    return k;
}

int main(){
 
    FastIO();
    int t,n,m,k; cin >> t;
    
    auto ans = [&]() -> bool {
        cin >> n >> m;
        vector<vector<int>> adjList(n);
        vector<bool> visited(n, 0);

        for(int i = 0, u,v; i < m; i++){
            cin >> u >> v;
            u--, v--;
            adjList[u].pb(v);
            adjList[v].pb(u);
        }

        k = valid_cycle(n, m);
        if(k < 3)
            return 0;

        for(int i = 0; i < n; i++)
            if(adjList[i].size() != 4 && adjList[i].size() != 2)
                return 0;

        vector<int> center;

        function<bool(int, int)> find_center = [&](int node, int parent) -> bool {
            center.pb(node);
            visited[node] = 1;

            int cnt = 0;
            for(int adjNode : adjList[node])
                if(adjList[adjNode].size() == 4)
                    cnt++;
            
            if(cnt != 2)
                return 0;

            for(int adjNode : adjList[node]){
                if(adjNode == parent || adjList[adjNode].size() == 2)
                    continue;
                if(adjNode == center[0]) 
                    return 1;
                if(visited[adjNode])
                    return 0;
                if(find_center(adjNode, node))
                    return 1;
            }

            return 0;
        };

        for(int i = 0; i < n; i++)
            if(adjList[i].size() == 4){
                if(!find_center(i, -1) || center.size() != k)
                    return 0;
                break;
            }

        int cnt;

        function<bool(int, int, int)> other = [&](int index, int node, int parent) -> bool {
            visited[node] = 1;
            cnt++;

            for(int adjNode : adjList[node]){
                if(adjNode == parent)
                    continue;

                if(adjNode == center[index])
                    return 1;

                if(adjList[adjNode].size() == 4 || visited[adjNode])
                    return 0;

                if(!other(index, adjNode, node))
                    return 0;
            }

            return 1;
        };

        for(int i = 0; i < k; i++){
            cnt = 0;
            for(int j : adjList[center[i]])
                if(adjList[j].size() == 2){
                    if(!other(i, j, center[i]) || cnt != k - 1)
                        return 0;
                    break;
                }
        }

        return 1;
    };

    while(t--)
        cout << (ans() ? "YES" : "NO") << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& value){ cerr << "("; printDbg(value.first); cerr << ", "; printDbg(value.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& value, Args... args){printDbg(value); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); }
