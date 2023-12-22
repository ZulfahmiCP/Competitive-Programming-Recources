#include <iostream>
#include <functional>
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
#include <set>
#include <map>
#define ll long long int
#define ull unsigned long long int
#define ld long double
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()
#define pb push_back
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
    int n; cin >> n;
    vector<int> A(n);

    for(int &a : A)
        cin >> a;
    
    int ans(0);
    for(int i = 1; i < n - 1; i ++)
        if((A[i] < A[i - 1] && A[i] < A[i + 1]) || (A[i] > A[i - 1] && A[i] > A[i + 1]))
            ans++;
    cout << ans << '\n';
 
    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void UsacoOpen(){ freopen("planting.in", "r", stdin); freopen("planting.out", "w", stdout); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U> void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Args> void printDebug(const T& value, Args... args){ cout << value << ", "; printDebug(args...); }
template <typename... Args> void Debug(Args... args){ cout << "["; printDebug(args...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1;} cout << "]\n"; }
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
