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
     int n,m; cin >> n >> m;
    vector<vector<int>> adjList(n);
    vector<bool> visited(n, 0);
    vector<int> route(n, 0);
 
    for(int i = 0, u,v; i < m; i++){
        cin >> u >> v;
        u--, v--;
        adjList[u].pb(v);
        adjList[v].pb(u);
    }
 
    route[n - 1] = -1;
    
    queue<int> sendMessage;
    sendMessage.push(0);
    while(!sendMessage.empty()){
        int q = sendMessage.size();
        while(q--){
            int computer = sendMessage.front();
            sendMessage.pop();
 
            for(int comp : adjList[computer]) if(!visited[comp]) {
                visited[comp] = 1;
                route[comp] = computer;
                if(comp == n - 1)
                    return;
                sendMessage.push(comp);
            }
        }
    }

    if(route[n - 1] == -1){
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> theRoute;
    int curComp = n - 1;
    while(curComp){
        theRoute.pb(curComp + 1);
        curComp = route[curComp];
    }
 
    cout << theRoute.size() + 1 << "\n1 ";
    for(int i = theRoute.size() - 1; i >= 0; i--)
        cout << theRoute[i] << " \n"[!i];

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
