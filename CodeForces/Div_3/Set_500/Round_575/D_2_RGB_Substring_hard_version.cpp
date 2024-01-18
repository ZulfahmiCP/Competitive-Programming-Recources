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
void UsacoOpen();
int main(){
 
    FastIO();
    int t,n,k,ans,m[3]; cin >> t;
    map<char, int> val{{'R', 0}, {'G', 1}, {'B', 2}};
    string s;
    while(t--){
        cin >> n >> k >> s;
        vector<vector<vector<int>>> A(n + 1, vector<vector<int>>(3, {0, 0, 0}));

        for(int i = n - 1; i >= 0; i--){
            A[i] = A[i + 1];
            A[i][val[s[i]]][i % 3]++;
        }

        ans = 1e9, m[0] = (k + 2)/3, m[1] = (k + 1)/3, m[2] = k/3; 
        for(int i = 0, p[3]; i <= n - k; i++){
            auto B = A[i], C = A[i + k];

            for(int j = 0; j < 3; j++)
                for(int l = 0; l < 3; l++)
                    B[j][l] -= C[j][l];
            
            for(int j = 0; j < 3; j++)
                p[j] = (i % 3 + j) % 3;

            ans = min(ans, m[0] - B[0][p[0]] + m[1] - B[1][p[1]] + m[2] - B[2][p[2]]);
            ans = min(ans, m[0] - B[1][p[0]] + m[1] - B[2][p[1]] + m[2] - B[0][p[2]]);
            ans = min(ans, m[0] - B[2][p[0]] + m[1] - B[0][p[1]] + m[2] - B[1][p[2]]);
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
