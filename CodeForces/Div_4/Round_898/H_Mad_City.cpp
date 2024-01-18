#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
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
    int t,n,a,b,A,B,done; cin >> t;
    while(t--){
        cin >> n >> a >> b;
        vector<vector<int>> adjList(n);
        vector<int> depth(n);
        vector<bool> visited(n, 0);

        for(int i = 0, u,v; i < n; i++){
            cin >> u >> v;
            adjList[--u].pb(--v);
            adjList[v].pb(u);
        }

        function<void(int, int)> find_cycle = [&](int node, int parent) -> void {
            visited[node] = 1;
            for(int &adjNode : adjList[node]) if(adjNode != parent) {
                if(!visited[adjNode]){
                    depth[adjNode] = depth[node] + 1;
                    find_cycle(adjNode, node);
                } else if(!done) {
                    done = 1;
                    b = adjNode;
                    B = depth[adjNode];
                }
            }
        };

        A = 1e9, done = 0;

        find_cycle(--b, -1);

        fill(all(visited), 0);
        fill(all(depth), 0);

        queue<pair<int, int>> catch_cycle;
        catch_cycle.push({--a, 0});
        visited[a] = 1;
        while(!catch_cycle.empty()){
            auto [node, parent] = catch_cycle.front();
            catch_cycle.pop();

            if(node == b){
                A = depth[node];
                break;
            }

            for(int &adjNode : adjList[node]) if(!visited[adjNode]) {
                visited[adjNode] = 1;
                depth[adjNode] = depth[node] + 1;
                catch_cycle.push({adjNode, node});
            }
        }

        assert(A != 1e9);

        cout << (A > B ? "YES" : "NO") << '\n';
    }



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
