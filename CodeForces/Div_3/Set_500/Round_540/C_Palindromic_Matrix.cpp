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
    int n,mx(1001); cin >> n;
    vector<int> count(mx, 0);
    vector<vector<int>> grid(n, vector<int>(n));
    priority_queue<pair<int, int>> A; 
    pair<int, int> cur;  

    auto fail = [&]() -> void {
        cout << "NO\n";
        exit(0);
    };

    for(int i = 0, a; i < n*n; i++){
        cin >> a;
        count[a]++;
    }

    for(int i = 1; i < mx; i++) if(count[i]) 
        A.push({count[i], i});
    
    for(int i = 0; i < n/2; i++)
        for(int j = 0; j < n/2; j++){
            cur = A.top();
            A.pop();

            if(cur.X < 4)
                fail();

            grid[i][j] = grid[i][n - j - 1] = cur.Y;
            grid[n - i - 1][j] = grid[n - i - 1][n - j - 1] = cur.Y;

            if(cur.X > 4)
                A.push({cur.X - 4, cur.Y});
        }
    
    if(n & 1){
        for(int i = 0; i < n/2; i++){
            cur = A.top();
            A.pop();

            if(cur.X < 2)
                fail();

            grid[n/2][i] = grid[n/2][n - i - 1] = cur.Y;

            if(cur.X > 2)
                A.push({cur.X - 2, cur.Y});
            
            cur = A.top();
            A.pop();

            if(cur.X < 2)
                fail();
            
            grid[i][n/2] = grid[n - i - 1][n/2] = cur.Y;

            if(cur.X > 2)
                A.push({cur.X - 2, cur.Y});
        }

        grid[n/2][n/2] = A.top().Y;
    }

    cout << "YES\n";
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cout << grid[i][j] << " \n"[j == n - 1];

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
