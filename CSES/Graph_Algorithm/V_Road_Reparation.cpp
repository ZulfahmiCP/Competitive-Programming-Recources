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

struct MST {
    int N;  
    vector<vector<pair<int, int>>> adjList;  

    MST(const vector<vector<pair<int, int>>> &adj){
        N = adj.size();
        adjList = adj;
    }

    ll primMST() {
        priority_queue<pair<int, int>, vector<pair<int, int>>, 
        greater<pair<int, int>>> explore;
        vector<int> key(N, 2e9);  
        vector<bool> visited(N, 0); 

        explore.push({0, 0});
        key[0] = 0;

        while(!explore.empty()){
            auto [weight, node] = explore.top();
            explore.pop();

            if(visited[node])
                continue;
            
            visited[node] = 1;
            key[node] = weight;

            for(auto [adjNode, edgeWeight] : adjList[node])
                if(!visited[adjNode])
                    explore.push({edgeWeight, adjNode});
        }

        ll totalWeight = 0;
        for(int i = 0; i < N; i++){
            if(!visited[i])
                return -1;
            totalWeight += key[i];
        }

        return totalWeight;
    }
};

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    vector<vector<pair<int, int>>> adjList(n);

    for(int i = 0, u,v,w; i < m; i++){
        cin >> u >> v >> w;
        u--, v--;
        adjList[u].pb({v, w});
        adjList[v].pb({u, w});
    }

    MST mst(adjList);
    ll ans = mst.primMST();
    if(ans == -1)
        cout << "IMPOSSIBLE\n";
    else 
        cout << ans << '\n';

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
