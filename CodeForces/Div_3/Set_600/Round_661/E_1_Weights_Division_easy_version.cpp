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
    int t,n; cin >> t;
    ll sum,cur_sum,move;
    while(t--){
        cin >> n >> sum;
        move = cur_sum = 0;
        vector<vector<pair<int, int>>> adjList(n);
        priority_queue<pair<ll, int>> divide_weight;
        vector<ll> leaves_count(n, 0), weight(n);

        for(int i = 0, u,v,w; i < n - 1; i++){
            cin >> u >> v >> w;
            u--, v--;
            adjList[u].pb({v, w});
            adjList[v].pb({u, w});
        }

        function<void(int, int)> count_leaves = [&](int node, int parent) -> void {
            if(adjList[node].size() == 1 && node)
                leaves_count[node] = 1;
            
            for(auto [adjNode, adjWeight] : adjList[node])
                if(adjNode != parent){
                    weight[adjNode] = adjWeight;

                    count_leaves(adjNode, node);
                    leaves_count[node] += leaves_count[adjNode];
                }
        };  

        count_leaves(0, -1);

        auto diff = [&](int i) -> ll {
            return weight[i]*leaves_count[i] - (weight[i]/2)*leaves_count[i];
        };  

        for(int i = 1; i < n; i++){
            divide_weight.push({diff(i), i});
            cur_sum += weight[i]*leaves_count[i];
        }

        while(cur_sum > sum){
            auto [adjWeight, node] = divide_weight.top();
            divide_weight.pop();

            cur_sum -= diff(node);
            weight[node] /= 2;

            divide_weight.push({diff(node), node});
            move++;
        }

        cout << move << '\n';
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
