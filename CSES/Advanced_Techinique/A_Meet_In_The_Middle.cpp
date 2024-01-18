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

struct MeetInTheMiddle {
    vector<ll> getSubset(const vector<int> &A) {
        int m = A.size();
        ll sum;
        vector<ll> subset;

        for(int i = 0; i < (1 << m); i++){
            sum = 0;
            for(int j = 0; j < m; j++)
                if(i & (1 << j))
                    sum += A[j];
            subset.pb(sum);
        }

        sort(all(subset));

        return subset;
    }

    ll solve(const vector<int>& A, int &x) {
        int n = A.size(), posA, posB;
        ll ans = 0;

        vector<ll> subA = getSubset(vector<int>(A.begin(), A.begin() + n/2));
        vector<ll> subB = getSubset(vector<int>(A.begin() + n/2, A.end()));

        for(ll &a : subA){
            posA = lower_bound(all(subB), x - a) - subB.begin();
            posB = upper_bound(all(subB), x - a) - subB.begin();
            ans += posB - posA;
        }

        return ans;
    }
};

int main(){
 
    FastIO();
    int n,x; cin >> n >> x;
    vector<int> A(n);

    for(int &a : A)
        cin >> a;
    
    MeetInTheMiddle ans;
    cout << ans.solve(A, x) << '\n';

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
