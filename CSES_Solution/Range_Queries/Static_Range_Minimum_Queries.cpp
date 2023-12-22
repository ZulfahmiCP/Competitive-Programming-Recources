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
    int n,q,mx(2e9); cin >> n >> q;
    vector<int> A(n), min_val(4*n);

    for(int &a : A)
        cin >> a;
    
    function<int(int, int, int)> build = [&](int pos, int l, int r) -> int {
        if(l == r){
            min_val[pos] = A[l];
            return min_val[pos];
        }

        int m = (l + r)/2;
        int min_left = build(2*pos + 1, l, m);
        int min_right = build(2*pos + 2, m + 1, r);

        min_val[pos] = min(min_left, min_right);
        return min_val[pos];
    };

    function<int(int, int, int, int, int)> get_min_val = [&](int pos, int l, int r, int L, int R) -> int {
        if(l > R || r < L)
            return mx;
        
        if(L <= l && r <= R)
            return min_val[pos];
        
        int m = (l + r)/2;
        int min_left = get_min_val(2*pos + 1, l, m, L, R);
        int min_right = get_min_val(2*pos + 2, m + 1, r, L, R);

        return min(min_left, min_right);
    };

    build(0, 0, n - 1);

    for(int i = 0, a,b; i < q; i++){
        cin >> a >> b;
        cout << get_min_val(0, 0, n - 1, a - 1, b - 1) << '\n';
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
