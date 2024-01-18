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
void UsacoOpen();
int main(){
 
    FastIO();
    FreeOpen();
    int n,m,ans(1e9); cin >> n >> m;
    vector<pair<int, int>> coor(n);
    vector<vector<int>> adjList(n);
    vector<bool> visited(n, 0);

    for(auto &c : coor)
        cin >> c.X >> c.Y;
    
    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v;
        u--, v--;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }

    pair<int, int> a,b;

    function<void(int)> explore = [&](int node) -> void {
        visited[node] = 1;

        a.X = min(a.X, coor[node].X);
        a.Y = max(a.Y, coor[node].X);
        b.X = min(b.X, coor[node].Y);
        b.Y = max(b.Y, coor[node].Y);

        for(int adjNode : adjList[node])
            if(!visited[adjNode])
                explore(adjNode);
    };  

    for(int i = 0; i < n; i++) if(!visited[i]) {
        a = b = {1e9, 0};
        explore(i);

        ans = min(ans, 2*(a.Y - a.X + b.Y - b.X));
    }

    cout << ans << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("fenceplan.in", "r", stdin); freopen("fenceplan.out", "w", stdout); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U>void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Args>void printDebug(const T& value, Args... args){printDebug(value); cout << ", "; printDebug(args...); }
template <typename... Args> void Debug(Args... args){ cout << "[";  printDebug(args...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1; } cout << "]\n";}
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
