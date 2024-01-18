#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <numeric>
#include <vector>
#include <string>
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
#define ld long double
#define ll long long int
#define ull unsigned long long int
#define min_heap priority_queue<int, vector<int>, greater<int>>
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()
#define Map unordered_map
#define Set unordered_set
using namespace std;
 
template <typename T>
    void printDebug(const T& x);
template <typename T, typename U>
    void printDebug(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDebug(const T& value, Args... args);
template <typename... Args>
    void Debug(Args... args);
template <typename K, typename V>
    void Debug(const map<K, V>& container);
template <typename T>
    void Debug(const set<T>& container);
template <typename T>
    void Debug(const vector<T>& container);
 
void FastIO();
void FreeOpen();

struct LCA {
    int n, max_depth;
    vector<vector<int>> parent, adjList; 
    vector<int> depth;           

    LCA(const vector<vector<int>>& adj, int root) {
        n = adj.size();
        adjList = adj;
        max_depth = 0;

        while((1 << max_depth) <= n) 
            max_depth++;

        parent.assign(n, vector<int>(max_depth, -1));
        depth.assign(n, 0);

        dfs(root, -1);
        for(int i = 1; i < max_depth; i++) 
            for(int j = 0; j < n; j++) 
                if(parent[j][i - 1] != -1) 
                    parent[j][i] = parent[parent[j][i - 1]][i - 1];
    }

    void dfs(int node, int par) {
        parent[node][0] = par;

        for(int i = 1; i < max_depth; i++){
            if(parent[node][i - 1] == -1)
                break;
            parent[node][i] = parent[parent[node][i - 1]][i - 1]; 
        }

        for(int adjNode : adjList[node]) 
            if(adjNode != par){
                depth[adjNode] = depth[node] + 1;
                dfs(adjNode, node);
            }
    }

    int getLCA(int u, int v) {
        if(depth[u] < depth[v]) 
            swap(u, v); 

        int diff = depth[u] - depth[v];

        for(int i = 0; i < max_depth; i++) 
            if(diff & (1 << i)) 
                u = parent[u][i];

        if(u == v) 
            return u;

        for(int i = max_depth - 1; i >= 0; i--) 
            if(parent[u][i] != parent[v][i])
                u = parent[u][i], v = parent[v][i];

        return parent[u][0]; 
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<vector<int>> adjList(n);

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v;
        adjList[--u].pb(--v);
        adjList[v].pb(u);
    }

    LCA A(adjList, 0);

    for(int i = 0, u,v,lca; i < q; i++){
        cin >> u >> v;
        lca = A.getLCA(--u, --v);

        cout << A.depth[u] + A.depth[v] - 2*A.depth[lca] << '\n';
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U>void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Args>void printDebug(const T& value, Args... args){printDebug(value); cout << ", "; printDebug(args...); }
template <typename... Args> void Debug(Args... args){ cout << "[";  printDebug(args...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1; } cout << "]\n";}
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
