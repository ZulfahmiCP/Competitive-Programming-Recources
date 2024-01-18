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
    int t,n,cur_B; cin >> t;
    while(t--){
        cin >> n;
        vector<int> A(n + 1), B(n + 1, 0), C(n + 1, 0);
        vector<bool> visited_B(n + 1, 0), visited_C(n + 1, 0);
 
        for(int i = 0; i < n; i++){
            cin >> A[i];
            if(!i || A[i] != A[i - 1]){
                B[i] = C[i] = A[i];
                visited_B[A[i]] = visited_C[A[i]] = 1;
            }
        } A[n] = B[n] = C[n] = n + 1, cur_B = 1;
 
        for(int i = 0, pos,cur_C; i < n; i++){
            pos = i + 1;
            while(A[pos] == A[i])
                pos++;
            
            for(int j = i + 1; j < pos; j++){
                while(visited_B[cur_B])
                    cur_B++;
                B[j] = cur_B;
                visited_B[B[j]] = 1;
            }
 
            cur_C = A[i] - 1;
            for(int j = i + 1; j < pos; j++){
                while(visited_C[cur_C])
                    cur_C--;
                C[j] = cur_C;
                visited_C[C[j]] = 1;
            }
 
            i = pos - 1;
        }
 
        for(int i = 0; i < n; i++)
            cout << B[i] << (i < n - 1 ? ' ' : '\n');
        for(int i = 0; i < n; i++)
            cout << C[i] << (i < n - 1 ? ' ' : '\n');
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
