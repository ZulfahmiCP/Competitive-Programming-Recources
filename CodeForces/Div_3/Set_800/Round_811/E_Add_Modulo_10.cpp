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
#define fi first 
#define se second 
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
    void printDbg(const T& x);
template <typename T, typename U>
    void printDbg(const pair<T, U>& value);
template <typename T, typename... Args>
    void printDbg(const T& value, Args... args);
template <typename... Args>
    void debug(Args... args);
template <typename K, typename V>
    void debug(const map<K, V>& container);
template <typename T>
    void debug(const set<T>& container);
template <typename T>
    void debug(const vector<T>& container);
template <typename T>
    void debug(const vector<vector<T>> &container);

const int MOD = 1e9 + 7;
const int mod = 998244353;

void FastIO();
void FreeOpen();

int main(){
 
    FastIO();
    int t,n; cin >> t;
 
    vector<int> type(21, 0);
    for(int i = 0; i < 5; i++)
        type[1 << i] = 1;
    type[13] = type[17] = type[19] = 1;
    for(int i = 3; i < 21; i++)
        if(!type[i])
            type[i] = 2;
 
    while(t--){
        cin >> n;
        vector<int> A(n);
 
        for(int &a : A)
            cin >> a;
 
        auto valid_type_zero = [&]() -> int {
            int zero(-1), five(-1), zero_occ(0), five_occ(0);
            for(int a : A){
                if(a % 10)
                    continue;
                if(zero == -1)
                    zero = a;
                else if(zero != a)
                    return 0;
                zero_occ++;
            }
 
            for(int a : A){
                if(a % 5 || !(a % 10))
                    continue;
                if(five == -1)
                    five = a;
                else if(five != a)
                    return 0;
                five_occ++;
            }
 
            if(zero == -1 && five == -1)
                return -1;
            if(zero_occ == n || five_occ == n)
                return 1;
            return (five + 5 == zero && five_occ + zero_occ == n);
        };
 
        auto valid = [&]() -> bool {
            int type_zero = valid_type_zero();
            if(type_zero == 1)
                return 1;
            if(type_zero == 0)
                return 0;
            
            for(int &a : A)
                a %= 20;
            for(int i = 0; i < n - 1; i++)
                if(type[A[i]] != type[A[i + 1]])
                    return 0;
            return 1;
        };
 
        cout << (valid() ? "YES\n" : "NO\n");
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& value){ cerr << "("; printDbg(value.first); cerr << ", "; printDbg(value.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& value, Args... args){printDbg(value); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); cerr << '\n';}
