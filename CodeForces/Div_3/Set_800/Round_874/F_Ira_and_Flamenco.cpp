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
    int t,n,m,ans,M(1e9 + 7); cin >> t;

    auto power = [&](int a, int b) -> int {
        int c = 1;
        while(b){
            if(b & 1)
                c = (1LL * c * a) % M;
            a = (1LL * a * a) % M, b >>= 1;
        }

        return c % M;
    };  

    auto inv = [&](int a) -> int {
        return power(a, M - 2);
    };

    while(t--){
        cin >> n >> m;
        vector<int> A, occ, inv_occ;
        map<int, int> freq;

        for(int i = 0, a; i < n; i++){
            cin >> a;
            if(!freq[a]++)
                A.pb(a);
        }

        sort(all(A));

        ans = 0, n = A.size();
        occ.resize(n);
        inv_occ.resize(n);
        for(int i = 0; i < n; i++)
            occ[i] = freq[A[i]];

        for(int i = 0; i < n; i++)
            inv_occ[i] = (1LL * inv(occ[i]) * (i ? inv_occ[i - 1] : 1)) % M;
        for(int i = 1; i < n; i++)
            occ[i] = (1LL * occ[i] * occ[i - 1]) % M;
        
            
        for(int i = 0, j = m - 1; j < n; i++, j++){
            if(A[j] - A[i] != m - 1)
                continue;
            if(A[j] - A[i] == m - 1)
                ans = (ans + (1LL * occ[j] * (i ? inv_occ[i - 1] : 1) % M)) % M;;
        }

        cout << ans << '\n';
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
