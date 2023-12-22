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

struct DSU {
    vector<int> rank, parent, sum, minV, maxV;

    DSU(int n) {
        rank.resize(n, 0);
        sum.resize(n, 1);
        minV.resize(n);
        maxV.resize(n);
        parent.resize(n);
        iota(all(minV), 0);
        iota(all(maxV), 0);
        iota(all(parent), 0);
    }

    int Find(int x) {
        return x == parent[x] ? x : parent[x] = Find(parent[x]);
    }

    void Union(int x, int y) {
        x = Find(x), y = Find(y);

        if(x == y)
            return;

        if(rank[x] < rank[y])
            swap(x, y);
        if(rank[x] == rank[y])
            rank[x]++;
        
        parent[y] = x;
        sum[x] += sum[y];
        minV[x] = min(minV[x], minV[y]);
        maxV[x] = max(maxV[x], maxV[y]);
    }
};

int main(){
 
    FastIO();
    int n,q; cin >> n >> q;
    string command;

    DSU A(n + 1);

    for(int i = 0, u,v; i < q; i++){
        cin >> command;

        if(command == "union"){
            cin >> u >> v;
            A.Union(u, v);
            continue;
        }

        cin >> u;
        u = A.Find(u);
        cout << A.minV[u] << ' ' << A.maxV[u] << ' ' << A.sum[u] << '\n';
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
