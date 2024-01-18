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
    int n,k; cin >> n >> k;
    vector<vector<int>> adjList(n);
    vector<vector<ll>> dp(n, vector<ll>(k + 1, 0));
    // dp[u][d] represent the number of node v which v is in the subtree of u
    // which have distance of exactly d

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v;
        adjList[--u].pb(--v);
        adjList[v].pb(u);
    }

    ll ans = 0, total;
    function<void(int, int)> explore = [&](int node, int parent) -> void {
        dp[node][0] = 1;

        for(int &adjNode : adjList[node]) if(adjNode != parent) {
            explore(adjNode, node);

            for(int i = 1; i <= k; i++)
                dp[node][i] += dp[adjNode][i - 1];
        }

        ans += dp[node][k], total = 0;

        for(int &adjNode : adjList[node]) if(adjNode != parent) {
            for(int i = 1; i < k; i++)
                total += dp[adjNode][i - 1] * (dp[node][k - i] - dp[adjNode][k - i - 1]);
            // this was count the number of vertices in the subtree of node 
            // which have distance of k. which is if for every vertices who have
            // distance of i times the other child of node who have distance of k - i
            // Because i + k - i = k, and we subtract dp[adjNode][k - i - 1], cause
            // we just wanna count from the distance other than adjNode
        }

        ans += total/2;
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
