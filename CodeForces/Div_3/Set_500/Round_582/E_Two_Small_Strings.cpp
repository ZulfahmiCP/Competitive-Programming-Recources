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
    int n; cin >> n;
    string s,t; cin >> s >> t;

    auto opp = [&](char x, char y) -> char {
        set<char> abc{'a', 'b', 'c'};
        abc.erase(x); abc.erase(y);
        return *abc.begin();
    };  

    string ans, add;

    auto join = [&](char a, char b, char c) -> void {
        add += a; add += b; add += c;
        for(int i = 0; i < n; i++)
            ans += add;
    };  

    auto repeat = [&](char a, char b, char c) -> void {
        string A(n, a); ans += A;
        string B(n, b); ans += B;
        string C(n, c); ans += C;
    };

    if(s[0] == s[1] && t[0] == t[1])
        join('a', 'b', 'c');
    else if(s[0] == t[1] && t[0] == s[1])
        repeat(s[0], opp(s[0], t[0]), t[0]);
    else if(s[0] == s[1])
        join(t[1], t[0], opp(t[0], t[1]));
    else if(t[0] == t[1])
        join(s[1], s[0], opp(s[0], s[1]));
    else if(s[1] == t[0])
        repeat(t[1], s[1], opp(s[1], t[1]));
    else if(t[1] == s[0])
        repeat(s[1], t[1], opp(s[1], t[1]));
    else if(s[1] == t[1])
        repeat(s[1], s[0], opp(s[0], s[1]));
    else if(s[0] == t[0])
        repeat(s[1], t[1], opp(s[1], t[1]));

    cout << "YES\n" << ans << '\n';

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
