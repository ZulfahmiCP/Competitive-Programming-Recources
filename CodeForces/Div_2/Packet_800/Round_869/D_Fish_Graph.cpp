
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

int main(){
 
    FastIO();
    int t,n,m; cin >> t;
    while(t--){
        cin >> n >> m;
        vector<vector<int>> adjList(n);
        vector<pair<int, int>> ans;
        vector<bool> visited(n, 0);
        vector<int> parent(n, -1);
        set<int> in_fish;

        for(int i = 0, u,v; i < m; i++){
            cin >> u >> v;
            u--, v--;
            adjList[u].pb(v);
            adjList[v].pb(u);
        }

        int index, other;
        function<int(int)> find_other = [&](int node) -> int {
            visited[node] = 1;
            if(parent[node] != index && in_fish.count(node))
                return node;

            for(int &adjNode : adjList[node]){
                if(visited[adjNode] || adjNode == parent[node])
                    continue;
                parent[adjNode] = node;
                other = find_other(adjNode);
                if(other != -1)
                    return other;
            }
            
            return -1;
        };

        for(index = 0; index < n; index++){
            if(adjList[index].size() < 4)
                continue;

            in_fish.clear();
            fill(all(visited), 0);

            for(int j : adjList[index])
                in_fish.insert(j);

            for(int j : adjList[index]){
                parent[j] = index;
                other = find_other(j);

                if(other == -1)
                    continue;

                for(int k : adjList[index]){
                    if(k == j || k == other)
                        continue;
                    if(ans.size() == 2)
                        break;
                    ans.pb({k, index});
                }

                assert(ans.size() == 2);
                
                ans.pb({other, index});
                while(other != index){
                    ans.pb({other, parent[other]});
                    other = parent[other];
                }

                break;
            }

            if(!ans.empty())
                break;
        }
        
        if (!ans.empty()) {
            cout << "YES\n" << ans.size() << '\n';
            for(auto &[u, v] : ans)
                cout << u + 1 << ' ' << v + 1 << '\n';
        } else 
            cout << "NO\n";
    }

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
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
