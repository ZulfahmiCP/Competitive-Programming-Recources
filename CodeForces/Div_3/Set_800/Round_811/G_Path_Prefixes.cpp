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

int main(){
 
    FastIO();
    int t,n; cin >> t;
    while(t--){
        cin >> n;
        vector<int> A(n), B(n);
        vector<ll> ans(n, 0), sumB;
        vector<vector<int>> adjList(n);

        for(int v = 1, p; v < n; v++){
            cin >> p >> A[v] >> B[v];
            adjList[--p].pb(v);
        }

        function<void(int, ll)> explore = [&](int node, ll sumA) -> void {
            ans[node] = upper_bound(all(sumB), sumA) - sumB.begin();

            for(int adjNode : adjList[node]){
                if(sumB.empty())
                    sumB.pb(B[adjNode]);
                else
                    sumB.pb(sumB.back() + B[adjNode]);
                explore(adjNode, sumA + A[adjNode]);
                sumB.ppb();
            }
        };

        explore(0, 0);
        for(int i = 1; i < n; i++)
            cout << ans[i] << " \n"[i + 1 == n];
    }

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
