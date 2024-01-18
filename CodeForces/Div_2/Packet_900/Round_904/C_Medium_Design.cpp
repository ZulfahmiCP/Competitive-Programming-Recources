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
    int t,n,m,ans,count_m,count_1; cin >> t;
    while(t--){
        cin >> n >> m;
        vector<pair<int, int>> A(n);

        for(int i = 0; i < n; i++)
            cin >> A[i].X >> A[i].Y;
        
        auto res = [&]() -> void {
            sort(all(A), [&](pair<int, int> &a, pair<int, int> &b) {
                return (a.X == b.X ? a.Y < b.Y : a.X < b.X);
            });

            count_m = count_1 = 0;
            priority_queue<pair<int, int>, vector<pair<int, int>>,
            greater<pair<int, int>>> B;
            for(int i = 0,j,k; i < n; i++){
                while(!B.empty() && B.top().X < A[i].X){
                    count_1 -= B.top().Y == 1;
                    count_m -= B.top().X == m;
                    B.pop();        
                }

                for(j = i; j < n && A[i].X == A[j].X; j++){
                    count_1 += A[j].X == 1;
                    count_m += A[j].Y == m;
                    B.push({A[j].Y, A[j].X});
                }

                k = B.size();
                if(A[i].X == 1)
                    ans = max(ans, k - count_m);
                else if(A[i].X == m)
                    ans = max(ans, k - count_1);
                else if(!count_1 || !count_m)
                    ans = max(ans, k);
                else 
                    ans = max(ans, k - min(count_1, count_m));
                
                i = j - 1;
            }

        };
        

    }

    /*
    2 4, 3 5, 4 6
    
    1 2 3 4 5 6 7 8
    0 1 2 3 2 1 0 0 
    
    */

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
