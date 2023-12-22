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

struct FenwickTree {
    int N;
    vector<ll> BIT;

    FenwickTree(int n) : N(n) {
        BIT.assign(N + 1, 0);
    }

    void update(int index, int delta) {
        for(; index <= N; index += index & -index) 
            BIT[index] += delta;
    }

    ll query(int index) const {
        ll sum = 0;
        for(; index > 0; index -= index & -index)
            sum += BIT[index];
        return sum;
    }

    ll rangeQuery(int left, int right) const {
        return query(right) - query(left - 1);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    vector<vector<int>> adjList(n);
    vector<int> S(n), T(n), value(n);

    for(int &v : value)
        cin >> v;

    for(int i = 1, u,v; i < n; i++){
        cin >> u >> v;
        adjList[--u].pb(--v);
        adjList[v].pb(u);
    }

    FenwickTree Tree(2*n);

    int timer = 0;
    function<void(int, int)> explore = [&](int node, int parent) -> void {
        S[node] = ++timer;
        Tree.update(S[node], value[node]);

        for(int &adjNode : adjList[node])
            if(adjNode != parent)
                explore(adjNode, node);
        
        T[node] = timer;
    };

    explore(0, -1);

    for(int i = 0, type,node,val; i < q; i++){
        cin >> type;

        if(type == 1){
            cin >> node >> val; node--;
            Tree.update(S[node], -value[node]);
            value[node] = val;
            Tree.update(S[node], value[node]);
        } else {
            cin >> node; node--;
            cout << Tree.rangeQuery(S[node], T[node]) << '\n';
        }
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
