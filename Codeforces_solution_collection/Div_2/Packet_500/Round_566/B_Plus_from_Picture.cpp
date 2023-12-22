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
    auto ans = [&]() -> bool {
        int m,n; cin >> m >> n;
        vector<string> S(m);
        vector<pair<int, int>> direct{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for(string &s : S)
            cin >> s;
    
        auto valid = [&](int i, int j) -> bool {
            for(auto [I, J] : direct)
                if(S[i + I][j + J] == '.')
                    return 0;
            return 1;
        };

        function<void(int, int, int)> mark = [&](int i, int j, int index) -> void {
            if(i < 0 || j < 0 || i == m || j == n || S[i][j] == '.')
                return;

            S[i][j] = '.';
            mark(i + direct[index].X, j + direct[index].Y, index);
        };

        for(int i = 1; i < m - 1; i++)
            for(int j = 1; j < n - 1; j++) if(S[i][j] == '*' && valid(i, j)){
                for(int k = 0; k < 4; k++){
                    mark(i, j, k);
                    S[i][j] = '*';
                } S[i][j] = '.';

                for(int r = 0; r < m; r++)
                    for(int c = 0; c < n; c++)
                        if(S[r][c] == '*')
                            return 0;
                return 1;  
            }
        
        return 0;
    };

    cout << (ans() ? "YES\n" : "NO\n");
    
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
