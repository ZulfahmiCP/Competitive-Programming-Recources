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
    int t; cin >> t;
 
    auto ans = [&]() -> int {
        string s; cin >> s;
        int n = s.size(), res(n), j;
        vector<vector<int>> pos(10);
        
        for(int i = n - 1; i > -1; i--)
            pos[s[i] - '0'].pb(i + 1);
        
        if(pos[0].size() > 1)
            res = min(res, n - pos[0][1] - 1);
 
        if(!pos[0].empty() && !pos[5].empty()){
            j = 0;
            while(j < pos[5].size() && pos[5][j] > pos[0][0])
                j++;
                
            if(j < pos[5].size())
              res = min(res, n - pos[5][j] - 1);
        }
 
        if(!pos[5].empty() && !pos[2].empty()){
            j = 0;
            while(j < pos[2].size() && pos[2][j] > pos[5][0])
                j++;
            
            if(j < pos[2].size())
                res = min(res, n - pos[2][j] - 1);
        }
        
        if(!pos[5].empty() && !pos[7].empty()){
            j = 0;
            while(j < pos[7].size() && pos[7][j] > pos[5][0])
                j++;
            
            if(j < pos[7].size())
                res = min(res, n - pos[7][j] - 1);
        }
 
        return res;
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
