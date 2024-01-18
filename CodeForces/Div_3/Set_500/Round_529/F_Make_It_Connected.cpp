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
#include <bitset>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <deque>
#include <set>
#include <map>
#define fi first 
#define se second 
#define Int int64_t
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define ull unsigned long long int
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
template <typename T>
    void printDbg(const T& x);
template <typename T, typename U>
    void printDbg(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDbg(const T& value, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& container);
template <typename T>
    void debug(const set<T>& container);
template <typename T>
    void debug(const vector<T>& container);
template <typename T>
    void debug(const vector<vector<T>> &container);

const int MOD = 1e9 + 7;
const int mod = 998244353;

void FastIO();
void FreeOpen();

struct MST {
    int N;  
    vector<vector<pair<int, ll>>> adjList;  

    MST(const vector<vector<pair<int, ll>>> &adj){
        N = adj.size();
        adjList = adj;
    }

    ll primMST() {
        vector<ll> key(N, 9e18);  
        vector<bool> visited(N, 0); 
        min_heap<pair<ll, int>> explore;

        explore.push({0, 0});
        key[0] = 0;

        while(!explore.empty()){
            auto [weight, node] = explore.top();
            explore.pop();

            if(visited[node])
                continue;
            
            visited[node] = 1;
            key[node] = weight;

            for(auto [adjNode, edgeWeight] : adjList[node])
                if(!visited[adjNode])
                    explore.push({edgeWeight, adjNode});
        }

        ll totalWeight = 0;
        for(int i = 0; i < N; i++){
            if(!visited[i])
                return -1;
            totalWeight += key[i];
        }

        return totalWeight;
    }
};

int main(){
 
    FastIO();
    int n,m,best(0); cin >> n >> m;
    vector<ll> A(n);
    vector<vector<pair<int, ll>>> adjList(n);

    for(int i = 0; i < n; i++){
        cin >> A[i];
        if(A[i] < A[best])
            best = i;
    }

    for(int i = 0; i < n; i++){
        if(i == best)
            continue;
        adjList[best].pb({i, A[best] + A[i]});
        adjList[i].pb({best, A[best] + A[i]});
    }

    for(ll i = 0, u,v,w; i < m; i++){
        cin >> u >> v >> w;
        u--, v--;
        adjList[u].pb({v, w});
        adjList[v].pb({u, w});
    }

    MST mst(adjList);
    cout << mst.primMST() << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& value){ cerr << "("; printDbg(value.first); cerr << ", "; printDbg(value.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& value, Args... args){printDbg(value); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
