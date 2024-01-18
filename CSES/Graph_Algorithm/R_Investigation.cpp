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

int main(){
 
    FastIO();
    int n,m,M(1e9 + 7); cin >> n >> m;
    vector<vector<pair<int, int>>> adjList(n);
    vector<ll> distance(n, 9e18), ways(n, 0), mx(n, 0), mn(n, 0);

    for(int i = 0, u,v,w; i < m; i++){
        cin >> u >> v >> w;
        adjList[--u].pb({--v, w});
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>,
    greater<pair<ll, int>>> explore;
    explore.push({0, 0});
    distance[0] = 0, ways[0] = 1, mx[0] = 1, mn[0] = 1;

    while(!explore.empty()){
        auto [weight, node] = explore.top();
        explore.pop();

        if(distance[node] < weight)
            continue;
        
        for(auto &[adjNode, edgeWeight] : adjList[node])
            if(weight + edgeWeight < distance[adjNode]){
                distance[adjNode] = weight + edgeWeight;
                ways[adjNode] = ways[node];
                mx[adjNode] = mx[node] + 1;
                mn[adjNode] = mn[node] + 1;
                explore.push({distance[adjNode], adjNode});
            } else if(weight + edgeWeight == distance[adjNode]) {
                ways[adjNode] = (ways[adjNode] + ways[node]) % M;
                mx[adjNode] = max(mx[adjNode], mx[node] + 1);
                mn[adjNode] = min(mn[adjNode], mn[node] + 1);
            }
    }

    cout << distance[n - 1] << ' ' << ways[n - 1] << ' ' << mn[n - 1] - 1 << ' ' << mx[n - 1] - 1 << '\n';

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
