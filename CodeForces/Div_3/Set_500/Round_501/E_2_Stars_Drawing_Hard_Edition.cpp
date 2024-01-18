

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
template <typename T>
    void Debug(const vector<vector<T>> &container);
 
void FastIO();
void FreeOpen();

int main(){
 
    FastIO();
    int n,m,ans(0); cin >> n >> m;
    vector<string> A(n);
    vector<vector<int>> star_size(n, vector<int>(m, 1e9));
    vector<vector<bool>> mark(n, vector<bool>(m, 0));

    for(auto &a : A)
        cin >> a;
    
    for(int i = 0, cur1, cur2; i < n; i++){
        cur1 = cur2 = 0;
        for(int j = 0, k = m - 1; j < m; j++, k--){
            A[i][j] == '.' ? cur1 = 0 : cur1++;
            A[i][k] == '.' ? cur2 = 0 : cur2++;
            
            star_size[i][j] = min(star_size[i][j], cur1);
            star_size[i][k] = min(star_size[i][k], cur2);
        }
    }

    for(int j = 0, cur1, cur2; j < m; j++){
        cur1 = cur2 = 0;
        for(int i = 0, k = n - 1; i < n; i++, k--){
            A[i][j] == '.' ? cur1 = 0 : cur1++;
            A[k][j] == '.' ? cur2 = 0 : cur2++;

            star_size[i][j] = min(star_size[i][j], cur1);
            star_size[k][j] = min(star_size[k][j], cur2);
        }
    }

    for(int i = 0, cur1, cur2; i < n; i++){
        cur1 = cur2 = 0;
        for(int j = 0, k = m - 1; j < m; cur1--, cur2--, j++, k--){
            if(star_size[i][j] > 1)
                cur1 = max(cur1, star_size[i][j]);
            if(star_size[i][k] > 1)
                cur2 = max(cur2, star_size[i][k]);
            
            if(cur1 > 0)
                mark[i][j] = 1;
            if(cur2 > 0)
                mark[i][k] = 1;
        }
    }

    for(int j = 0, cur1, cur2; j < m; j++){
        cur1 = cur2 = 0;
        for(int i = 0, k = n - 1; i < n; cur1--, cur2--, i++, k--){
            if(star_size[i][j] > 1)
                cur1 = max(cur1, star_size[i][j]);
            if(star_size[k][j] > 1)
                cur2 = max(cur2, star_size[k][j]);

            if(cur1 > 0)
                mark[i][j] = 1;
            if(cur2 > 0)
                mark[k][j] = 1;
        }
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++){
            ans += star_size[i][j] > 1;
            if(!mark[i][j] && A[i][j] == '*'){
                cout << "-1\n";
                return 0;
            }
        }

    cout << ans << '\n';
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(star_size[i][j] > 1)
                cout << i + 1 << ' ' << j + 1 << ' ' << star_size[i][j] - 1 << '\n';

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
template <typename T> void Debug(const vector<vector<T>> &container) { for (const auto &v : container) Debug(v); }
