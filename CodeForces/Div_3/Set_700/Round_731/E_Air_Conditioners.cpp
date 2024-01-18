
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
    int t,n,k,cur_l,cur_ac; cin >> t;
    while(t--){
        cin >> n >> k;
        min_heap cur_r;
        vector<int> ans(n, 0);
        vector<pair<int, int>> A(k);
        Map<ll, int> count;

        for(int i = 0, a; i < k; i++){
            cin >> a;
            A[i].X = a - 1;
        } for(int i = 0; i < k; i++)
            cin >> A[i].Y;
        sort(all(A));

        for(auto [a, t] : A){
            count[a + t]++;
            cur_r.push(a + t);
        } 

        cur_l = 2e9, cur_ac = 0;
        for(int i = 0, ac; i < n; i++){
            ans[i] = min(cur_l + i, cur_r.top() - i);

            if(i != A[cur_ac].X)
                continue;

            ac = A[cur_ac].X + A[cur_ac].Y;
            if(!(--count[ac]))
                count.erase(ac);

            while(!cur_r.empty() && !count[cur_r.top()])
                cur_r.pop();
            if(cur_r.empty())
                cur_r.push(2e9);
                
            cur_l = min(cur_l, A[cur_ac].Y - A[cur_ac].X);
            cur_ac++;
        }

        for(int i = 0; i < n; i++)
            cout << ans[i] << " \n"[i == n - 1];
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
