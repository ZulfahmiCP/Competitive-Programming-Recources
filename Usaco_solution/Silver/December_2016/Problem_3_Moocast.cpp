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

struct Ship{
    int x,y,r;
};

int main(){
 
    FastIO();
    FreeOpen();
    int n,max_range,ans(1); cin >> n;
    vector<Ship> A(n);
    vector<vector<int>> adjList(n);
    vector<bool> visited(n);

    for(auto &a : A)
        cin >> a.x >> a.y >> a.r;
    for(int i = 0; i < n; i++)
    
    for(int i = 0, count; i < n; i++){
        count = 0;
        for(int j = 0, range; j < n; j++) if(i != j) {
            range = pow(abs(A[i].x - A[j].x), 2) + pow(abs(A[i].y - A[j].y), 2);
            if(range <= A[i].r * A[i].r)
                adjList[i].pb(j);
        }
    }

    function<void(int)> explore = [&](int node) -> void {
        max_range++;
        visited[node] = 1;
        for(int adjNode : adjList[node])
            if(!visited[adjNode])
                explore(adjNode);
    };

    for(int i = 0; i < n; i++) {
        fill(all(visited), 0);
        max_range = 0;
        explore(i);

        ans = max(ans, max_range);
    }

    cout << ans << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("moocast.in", "r", stdin); freopen("moocast.out", "w", stdout); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U>void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Args>void printDebug(const T& value, Args... args){printDebug(value); cout << ", "; printDebug(args...); }
template <typename... Args> void Debug(Args... args){ cout << "[";  printDebug(args...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1; } cout << "]\n";}
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
