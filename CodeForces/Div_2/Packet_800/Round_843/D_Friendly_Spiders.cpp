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
    int n,s,t,mx(3e5); cin >> n;
    vector<vector<int>> adjList(2*mx + 1);
    vector<int> path, parent(2*mx + 1, -1);
    vector<bool> visited(2*mx + 1, 0);

    for(int i = 0, a; i < n; i++){
        cin >> a;

        for(int j = 2; j * j <= a; j++)
            if(!(a % j)){
                while(!(a % j))
                    a /= j;
                adjList[i + 1].pb(mx + j);
                adjList[mx + j].pb(i + 1);
            }
        
        if(a > 1){
            adjList[mx + a].pb(i + 1);
            adjList[i + 1].pb(mx + a);
        }
    }

    cin >> s >> t;
    queue<int> explore;
    explore.push(s);
    visited[s] = 1;
    for(int node; !explore.empty();){ 
        node = explore.front();
        explore.pop();

        if(node == t){
            while(node != -1){
                if(node <= n)
                    path.pb(node);
                node = parent[node];
            }

            n = path.size();
            cout << n << '\n';
            for(int i = n - 1; i >= 0; i--)
                cout << path[i] << " \n"[!i];

            return 0;
        }

        for(int adjNode : adjList[node]) if(!visited[adjNode]) {
            visited[adjNode] = 1;
            parent[adjNode] = node;
            explore.push(adjNode);
        }
    }

    cout << "-1\n";

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
