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
    int t,n,ans; cin >> t;
    while(t--){
        cin >> n;
        ans = 0;
        vector<int> A(n), B(n);

        for(int &x : A) cin >> x;
        for(int &x : B) cin >> x;
    
        auto remove_duplicate = [&]() -> void {
            sort(all(A));
            sort(all(B));

            vector<int> delA = A, delB = B;

            for(int i = 0, j = 0; i < n && j < n;){
                if(A[i] == B[j]){
                    delA[i] = delB[j] = 0;
                    i++, j++;
                } else if(A[i] < B[j])
                    i++;
                else 
                    j++;
            }

            A.clear(); B.clear();

            for(int i = 0; i < n; i++) if(delA[i])
                A.pb(delA[i]);

            for(int i = 0; i < n; i++) if(delB[i])
                B.pb(delB[i]);

            n = A.size();
        };  

        remove_duplicate();
        
        for(int &a : A)
            if(a >= 10)
                a = log10(a) + 1, ans++;
        
        for(int &b : B)
            if(b >= 10)
                b = log10(b) + 1, ans++;

        remove_duplicate();
     
        for(int &a : A) 
            ans += (a != 1);
        for(int &b : B) 
            ans += (b != 1);
        
        cout << ans << '\n';
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
