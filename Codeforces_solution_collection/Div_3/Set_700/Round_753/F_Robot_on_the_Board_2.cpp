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
    int t,m,n,r,c,max_step; cin >> t;
    map<char, pair<int, int>> dir{{'U', {-1, 0}}, {'D', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}};
    pair<int, int> lost;
    while(t--){
        cin >> m >> n;

        vector<string> S(m);
        vector<vector<int>> dist(m, vector<int>(n, 1)), visited(m, vector<int>(n, 0));

        for(string &s : S)
            cin >> s;
        
        function<void(int, int)> explore = [&](int i, int j) -> void {
            auto [I, J] = dir[S[i][j]];
            I += i, J += j;

            visited[i][j] = -1;
            if(I < 0 || J < 0 || I == m || J == n){
                visited[i][j] = 1;
                return;
            }
            
            if(visited[I][J] == -1){
                visited[i][j] = 1;
                lost = {I, J};
                return;
            }

            if(visited[I][J]){
                visited[i][j] = 1;
                dist[i][j] += dist[I][J];
                return;
            }

            explore(I, J);
            visited[i][j] = 1;
            dist[i][j] += dist[I][J];
        };

        function<void(int, int)> cycle = [&](int i, int j) -> void {
            dist[i][j] = dist[lost.X][lost.Y];
            auto [I, J] = dir[S[i][j]];
            I += i, J += j;

            if(I == lost.X && J == lost.Y)
                return;
            cycle(I, J);
        };

        r = c = 1, max_step = 0;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                if(!visited[i][j]){
                    lost = {-1, -1};
                    explore(i, j);

                    if(lost.X != -1)
                        cycle(lost.X, lost.Y);

                    if(dist[i][j] > max_step)
                        max_step = dist[i][j], r = i + 1, c = j + 1;
                }
        cout << r << ' ' << c << ' ' << max_step << '\n';
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
