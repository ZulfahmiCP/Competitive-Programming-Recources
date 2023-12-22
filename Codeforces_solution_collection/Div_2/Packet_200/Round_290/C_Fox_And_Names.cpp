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
    int n,m(26); cin >> n;
    string ans;
    vector<vector<int>> adjList(m);
    vector<string> S(n);
    vector<int> visited(m, -1);

    for(string &s : S)
        cin >> s;

    for(int i = 0, j,k; i < n - 1; i++){
        k = min(S[i].size(), S[i + 1].size());
        for(j = 0; j < k; j++)
            if(S[i][j] != S[i + 1][j])
                break;
        
        if(j == k){
            if(S[i].size() > S[i + 1].size()){
                cout << "Impossible\n";
                return 0;
            }

            continue;
        }

        adjList[S[i][j] - 'a'].pb(S[i + 1][j] - 'a');
    }

    function<bool(int)> explore = [&](int node) -> bool {
        if(visited[node] != -1)
            return visited[node];
        visited[node] = 0;

        for(int &adjNode : adjList[node])
            if(!explore(adjNode))
                return 0;
        
        visited[node] = 1;
        ans += char(node + 'a');
        return 1;
    };

    for(int i = 0; i < m; i++)
        if(visited[i] == -1 && !adjList[i].empty() && !explore(i)){
            cout << "Impossible\n";
            return 0;
        }

    reverse(all(ans));
    for(int i = 0; i < m; i++)
        if(visited[i] == -1)
            ans += char(i + 'a');
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
