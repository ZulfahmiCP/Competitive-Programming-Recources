
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

int main(){
 
    FastIO();
    int t,n,ans; cin >> t;
    string s;
    while(t--){
        cin >> s;
        n = ans = s.size();
        vector<vector<int>> pref(n, vector<int>(2, 0)), suff(n, vector<int>(2, 0));

        pref[0][0] = s[0] == '0', pref[0][1] = s[0] == '1';
        for(int i = 1; i < n; i++)
            for(int j = 0; j < 2; j++)
                pref[i][j] = pref[i - 1][j] + (s[i] == char(j + '0'));
        
        suff[n - 1][0] = s[n - 1] == '0', suff[n - 1][1] = s[n - 1] == '1';
        for(int i = n - 2; i >= 0; i--)
            for(int j = 0; j < 2; j++)
                suff[i][j] = suff[i + 1][j] + (s[i] == char(j + '0'));
        
        ans = min(suff[0][0], suff[0][1]);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < 2; j++)
                ans = min(ans, (i + 1 - pref[i][j]) + (n - i - 1 - suff[i][!j]));
        cout << ans << '\n';
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
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); }
