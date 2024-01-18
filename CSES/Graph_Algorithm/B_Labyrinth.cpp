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
    int m,n; cin >> m >> n;
    vector<vector<char>> direct(m, vector<char>(n));
    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<string> maze(m);
 
    pair<int, int> start, ending;
    for(int i = 0; i < m; i++){
        cin >> maze[i];
        for(int j = 0; j < n; j++)
            if(maze[i][j] == 'A')
                start = {i, j}, direct[i][j] = '?', maze[i][j] = '#';
            else if(maze[i][j] == 'B')
                ending = {i, j};
    }
 
    queue<pair<int, int>> explore;
    explore.push(start);
    while(!explore.empty()){
        auto [i, j] = explore.front();
        explore.pop();
 
        for(auto [r, c] : dir){
            int I = i + r, J = j + c;
 
            if(I < 0 || J < 0 || I == m || J == n || maze[I][J] == '#')
                continue;
 
            maze[I][J] = '#';
            explore.push({I, J});
            
            if(r == -1 && !c)
                direct[I][J] = 'U';
            else if(r == 1 && !c)
                direct[I][J] = 'D';
            else if(!r && c == -1)
                direct[I][J] = 'L';
            else if(!r && c == 1)
                direct[I][J] = 'R';
 
            if(I == ending.first && J == ending.second){
                string path;
                while(direct[I][J] != '?'){
                    path += direct[I][J];
                    switch(direct[I][J]){
                        case 'U' : I++; break;
                        case 'D' : I--; break;
                        case 'L' : J++; break;
                        case 'R' : J--; break;
                    }
                }
 
                reverse(path.begin(), path.end());
                cout << "YES\n" << path.size() << '\n' << path << '\n';
 
                return 0;
            }
        }
    }
 
    cout << "NO\n";

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
