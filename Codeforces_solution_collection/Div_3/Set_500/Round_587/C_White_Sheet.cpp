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
    int n(7);
    vector<int> x(7), y(7);

    for(int i = 1; i < n; i++){
        cin >> x[i] >> y[i];
        x[i] *= 2, y[i] *= 2;
    }
    
    auto valid = [&](int x, int y, int x1, int y1, int x2, int y2) {
	    return x < x1 || x2 < x || y < y1 || y2 < y;
    };

    auto ans = [&]() -> bool {
        for(int X = x[1]; X <= x[2]; X++){
		    if(valid(X, y[1], x[3], y[3], x[4], y[4]) && valid(X, y[1], x[5], y[5], x[6], y[6]))
			    return 1;
		    if (valid(X, y[2], x[3], y[3], x[4], y[4]) && valid(X, y[2], x[5], y[5], x[6], y[6])) 
			    return 1;
		}
	
	    for(int Y = y[1]; Y <= y[2]; Y++){
		    if(valid(x[1], Y, x[3], y[3], x[4], y[4]) && valid(x[1], Y, x[5], y[5], x[6], y[6])) 
			    return 1;
		    if(valid(x[2], Y, x[3], y[3], x[4], y[4]) && valid(x[2], Y, x[5], y[5], x[6], y[6]))
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
