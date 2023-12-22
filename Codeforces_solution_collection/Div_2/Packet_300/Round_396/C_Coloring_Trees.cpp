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
    int n,m,p; cin >> n >> m >> p;
    vector<int> color(n);
    vector<vector<int>> cost(n, vector<int>(m));
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(m, vector<ll>(p + 1, 1e18))); 

    for(int &c : color){
        cin >> c;
        c--;
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> cost[i][j];
    
    if(color[0] == -1)
        for(int i = 0; i < m; i++)
            dp[0][i][1] = cost[0][i];
    else    
        dp[0][color[0]][1] = 0;

    for(int i = 1; i < n; i++)
        for(int k = 1; k <= p; k++){
            if(color[i] == -1){
                for(int a = 0; a < m; a++){
                    dp[i][a][k] = min(dp[i][a][k], dp[i - 1][a][k] + cost[i][a]);
                    for(int b = 0; b < m; b++) if(a != b)
                        dp[i][a][k] = min(dp[i][a][k], cost[i][a] + dp[i - 1][b][k - 1]);
                }
            } else {
                dp[i][color[i]][k] = min(dp[i][color[i]][k], dp[i - 1][color[i]][k]);
                for(int j = 0; j < m; j++)
                    if(j != color[i])
                        dp[i][color[i]][k] = min(dp[i][color[i]][k], dp[i - 1][j][k - 1]);
            }
        }
    
    ll ans = 1e18;
    for(int c = 0; c < m; c++)
        ans = min(ans, dp[n - 1][c][p]);
    cout << (ans == 1e18 ? -1 : ans) << '\n';

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
