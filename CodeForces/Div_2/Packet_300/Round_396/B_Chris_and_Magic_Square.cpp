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
    auto ans = [&]() -> ll {
        int n; cin >> n;
        pair<int, int> cell = {-1, -1};
        vector<vector<int>> A(n, vector<int>(n));

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++){
                cin >> A[i][j];
                if(!A[i][j])
                    cell = {i, j};
            }

        if(n == 1)
            return 1;
    
        set<ll> S, M;
        ll row,coulomn;

        for(int i = 0; i < n; i++){
            row = coulomn = 0;
            for(int j = 0; j < n; j++)
                row += A[i][j], coulomn += A[j][i];

            if(i != cell.X)
                S.insert(row);
            else 
                M.insert(row);

            if(i != cell.Y)
                S.insert(coulomn);
            else 
                M.insert(coulomn);
        }

        bool ZA(0), ZB(0);
        row = coulomn = 0;
        for(int i = 0; i < n; i++){
            row += A[i][i];
            coulomn += A[i][n - i - 1];
    
            if(i == cell.X && i == cell.Y)
                ZA = 1;
            if(i == cell.X && n - i - 1 == cell.Y)
                ZB = 1;
        }

        (!ZA ? S : M).insert(row);
        (!ZB ? S : M).insert(coulomn);

        return (S.size() > 1 || M.size() > 1 || *S.begin() <= *M.begin() ? -1 : *S.begin() - *M.begin());
    };

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
