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
    int n; cin >> n;
    ll ans = 0;
    vector<vector<ll>> dp(n, vector<ll>(2, -1e18));
    vector<vector<pair<int, int>>> adjList(n);
    vector<int> A(n);

    for(int &a : A)
        cin >> a;
    
    for(int i = 1, u,v,w; i < n; i++){
        cin >> u >> v >> w;
        adjList[--u].pb({--v, w});
        adjList[v].pb({u, w});
    }

    function<void(int, int)> explore = [&](int node, int parent) -> void {
        dp[node][0] = dp[node][1] = A[node];
        
        vector<ll> child_dp;
            
        for(auto &[adjNode, edgeWeight] : adjList[node]){
            if(adjNode == parent)
                continue;

            explore(adjNode, node);
            child_dp.pb(dp[adjNode][0] - edgeWeight);
        }

        sort(All(child_dp));

        if(!child_dp.empty())
            dp[node][0] = A[node] + max(0LL, child_dp[0]);
        if(child_dp.size() > 1)
            dp[node][1] = A[node] + max(0LL, child_dp[0] + child_dp[1]);

        ans = max({ans, dp[node][0], dp[node][1]});
    };

    explore(0, -1);
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
