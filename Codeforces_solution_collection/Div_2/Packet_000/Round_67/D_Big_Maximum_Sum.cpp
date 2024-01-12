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
#define X first 
#define Y second 
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
 
void FastIO();
void FreeOpen();

int max_pref(vector<int> &A) {
    int mx = -2e9, cur = 0;
    for(int &a : A){
        cur += a;
        mx = max(mx, cur);
    }

    return mx;
}

int max_suff(vector<int> &A) {
    int n = A.size(), mx = -2e9, cur = 0;
    for(int i = n - 1; i >= 0; i--){
        cur += A[i];
        mx = max(mx, cur);
    }

    return mx;
}

int max_sub(vector<int> &A) {
    int mx = -2e9, cur = 0;
    for(int &a : A){
        cur += a;
        mx = max(mx, cur);
        cur = max(cur, 0);
    }

    return mx;
}

int main(){
 
    FastIO();
    int n,m; cin >> n >> m;
    vector<vector<int>> A(n);
    vector<int> pref(n, 0), suff(n, 0), sum(n);
    ll ans = -1e18, cur = 0;

    for(int i = 0, k; i < n; i++){
        cin >> k;
        A[i] = vector<int>(k);

        for(int &a : A[i])
            cin >> a;

        pref[i] = max_pref(A[i]);
        suff[i] = max_suff(A[i]);
        sum[i] = accumulate(all(A[i]), 0);
    }

    vector<bool> used(n, 0);

    for(int i = 0, x; i < m; i++){
        cin >> x, x--;

        used[x] = 1;
        ans = max(ans, cur + pref[x]);
        cur = max({0LL, cur + sum[x], (ll)suff[x]});
    }

    for(int i = 0; i < n; i++)
        if(used[i])
            ans = max(ans, (ll)max_sub(A[i]));

    cout << ans << '\n';

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cerr.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& value){ cerr << "("; printDbg(value.first); cerr << ", "; printDbg(value.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& value, Args... args){printDbg(value); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); }
