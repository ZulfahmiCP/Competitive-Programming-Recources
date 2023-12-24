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
    ll t,n,m,k,cur; cin >> t;
    string s; 
    while(t--){
        cin >> s >> k;
        n = s.size();
        vector<int> used(n, 1), prev(n), next(n);

        m = 0;
        for(int i = n; i > 0 && i < k; i--)
            m = n - i + 1, k -= i;

        auto remove = [&](int index) -> void {
            used[index] = 0;

            if(prev[index] != -1)
                next[prev[index]] = next[index];
            if(next[index] != n)
                prev[next[index]] = prev[index];
            
            if(next[index] == n)
                cur = prev[index];
            else if(prev[index] == -1 || s[prev[index]] <= s[next[index]]){
                for(int i = next[index]; i < n; i = next[i])
                    if(next[i] < n && s[i] > s[next[i]]){
                        cur = i;
                        break;
                    } else if(next[i] == n && cur == index)
                        cur = i;
            } else 
                cur = prev[index];
        };

        iota(all(prev), -1);
        iota(all(next), 1);

        cur = n - 1;
        for(int i = n - 2; i >= 0; i--)
            if(s[i] > s[i + 1])
                cur = i;
        
        for(int i = 0; i < m; i++)  
            remove(cur);
        
        cur = 0;
        for(int i = 0; i < n; i++){
            if(!used[i])
                continue;
            
            if(++cur == k){
                cout << s[i];
                break;
            }
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
