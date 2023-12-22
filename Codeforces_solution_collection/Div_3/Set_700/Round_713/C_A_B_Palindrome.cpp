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
    int t,n,a[2]; cin >> t;
    string s;
 
    auto ans = [&]() -> string {
        cin >> a[0] >> a[1] >> s;
        n = s.size();
 
        for(int i = 0, j = n - 1; i < j; i++, j--)
            if(s[i] == '?' && s[j] == '?')
                continue;
            else if(s[i] == '?'){
                s[i] = s[j];
                a[s[i] == '1'] -=2 ;
            } else if(s[j] == '?'){
                s[j] = s[i];
                a[s[i] == '1'] -= 2;
            } else if(s[i] == s[j])
                a[s[i] == '1'] -= 2;
            else 
                return "-1";
        
        for(int i = 0, j = n - 1; i < j; i++, j--)
            if(s[i] == '?'){
                if(a[0] > 1){
                    s[i] = s[j] = '0';
                    a[0] -= 2;
                } else if(a[1] > 1){
                    s[i] = s[j] = '1';
                    a[1] -= 2;
                } else 
                    return "-1";
            } 
        
        if((n & 1)){
            if(s[n/2] != '?')
                a[s[n/2] == '1']--;
            else if(a[0] == 1)
                s[n/2] = '0', a[0]--;
            else if(a[1] == 1)
                s[n/2] = '1', a[1]--;
        }
 
        return (min(a[0], a[1]) == 0 ? s : "-1");
    };
 
    while(t--)
        cout << ans() << '\n';
 
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
