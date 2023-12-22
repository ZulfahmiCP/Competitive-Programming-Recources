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
    int n,m,l(0),r(0),mx(1e6 + 1); cin >> n;
    vector<vector<vector<string>>> count(mx, vector<vector<string>>(5));
    map<char, int> vowel{{'a', 0}, {'i', 1}, {'u', 2}, {'e', 3}, {'o', 4}};

    for(int i = 0, v; i < n; i++){
        string s; cin >> s;
        char last_v;

        v = 0;
        for(char c : s)
            if(vowel.find(c) != vowel.end())
                v++, last_v = c;
        count[v][vowel[last_v]].pb(s);
    }

    vector<vector<string>> ans;
    vector<string> F, S;

    for(int i = 1, first_count; i < mx; i++){
        first_count = 0;
        for(int j = 0; j < 5; j++){
            m = count[i][j].size();
            for(int k = 0; k < m; k += 2) if(k + 1 < m){
                S.pb(count[i][j][k]);
                S.pb(count[i][j][k + 1]);
            }

            if(m & 1){
                F.pb(count[i][j][m - 1]);
                first_count++;
            }
        }

        if(first_count & 1)
            F.pop_back();
    } 

    n = F.size(), m = S.size();

    while(l + 1 < n && r + 1 < m){
        ans.pb({F[l], F[l + 1], S[r], S[r + 1]});
        l += 2, r += 2;
    }

    while(r + 3 < m){
        ans.pb({S[r], S[r + 1], S[r + 2], S[r + 3]});
        r += 4;
    }

    if(l < n && r + 2 < m)
        ans.pb({F[l], S[r + 2], S[r], S[r + 1]});

    cout << ans.size() << '\n';
    for(auto res : ans)
        cout << res[0] << ' ' << res[2] << '\n' << res[1] << ' ' << res[3] << '\n'; 
    
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
