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
    int t,n,l,r,s,k,cur; cin >> t;
    while(t--){
        cin >> n >> l >> r >> s;
 
        k = r - l + 1;
        vector<int> B(k + 1);
        iota(all(B), 1);
        B[k] = n + 1;
 
        if(s < k*(k + 1)/2 || s > n*(n + 1)/2 - (n - k)*(n - k + 1)/2){
            cout << "-1\n";
            continue;
        }
 
        cur = k*(k + 1)/2;
        for(int i = k - 1; i > -1; i--){
            if(cur + B[i + 1] - B[i] - 1 >= s){
                B[i] += (s - cur);
                break;
            }
 
            cur += (B[i + 1] - B[i] - 1);
            B[i] = B[i + 1] - 1;
        }
 
        vector<int> A(n, -1);
        vector<bool> visited(n + 1, 0);
        for(int i = l - 1; i < r; i++){
            A[i] = B[i - l + 1];
            visited[A[i]] = 1;
        }
 
        k = 1;
        for(int i = 0; i < n; i++)
            if(A[i] == -1){
                while(visited[k])
                    k++;
 
                A[i] = k;
                visited[k] = 1;
            }
        
        for(int i = 0; i < n; i++)
            cout << A[i] << (i < n - 1 ? ' ' : '\n');
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
