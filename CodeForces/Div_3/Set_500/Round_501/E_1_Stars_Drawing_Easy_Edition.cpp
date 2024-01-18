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
#define ppb pop_back
#define ppf pop_front
#define ld long double
#define ll long long int
#define ull unsigned long long int
#define all(x) x.begin(), x.end()
#define All(x) x.rbegin(), x.rend()

using namespace std;
template<class T> using Set = unordered_set<T>;
template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;  
template<class T, class U> using Map = unordered_map<T, U>;
 
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
    int n,m; cin >> n >> m;
    vector<string> A(n);
    vector<tuple<int, int, int>> ans;
    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<vector<bool>> mark(n, vector<bool>(m, 0));

    for(auto &s : A)
        cin >> s;
    
    function<int(int, int, int)> explore = 
    [&](int i, int j, int k) -> int {
        if(i < 0 ||  j < 0 || i == n || j == m || A[i][j] == '.')
            return 0;
        return 1 + explore(i + dir[k].X, j + dir[k].Y, k);
    };

    function<void(int, int, int, int)> mark_star = 
    [&](int i, int j, int k, int cnt) -> void {
        if(!cnt)
            return;

        mark[i][j] = 1;
        mark_star(i + dir[k].X, j + dir[k].Y, k, cnt - 1);
    };

    for(int i = 0, star_size; i < n; i++)
        for(int j = 0; j < m; j++){
            if(A[i][j] == '.'){
                mark[i][j] = 1;
                continue;
            }

            star_size = 2e9;
            for(int k = 0; k < 4; k++)
                star_size = min(star_size, explore(i, j, k) - 1);

            if(!star_size)
                continue;

            for(int k = 0; k < 4; k++)
                mark_star(i, j, k, star_size + 1);
                
            ans.pb({i + 1, j + 1, star_size});
        }
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(!mark[i][j]){
                cout << "-1\n";
                return 0;
            }

    cout << ans.size() << '\n';
    for(auto &[x, y, size] : ans)
        cout << x << ' ' << y << ' ' << size << '\n';        

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
