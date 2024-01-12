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
 
void FastIO();
void FreeOpen();

int main(){
 
    FastIO();
    int t,n,k,len,mx(1e9); cin >> t;
    vector<int> k1_beautiful, k2_beautiful;

    function<void(int, int, vector<int>)> gen_beautiful_num = 
    [&](int x, int cnt, vector<int> digit) -> void {
        if(digit.size() == 1)
            k1_beautiful.pb(x);
        k2_beautiful.pb(x);

        if(cnt == 9)
            return;

        x *= 10;
        if(digit.size() == 1){
            for(int i = 0; i < 10; i++){
                if(i != digit[0])
                    digit.pb(i);

                gen_beautiful_num(x + i, cnt + 1, digit);
                
                if(i != digit[0])
                    digit.ppb();
            }
        } else {
            gen_beautiful_num(x + digit[0], cnt + 1, digit);
            gen_beautiful_num(x + digit[1], cnt + 1, digit);
        }
    };

    for(int i = 1; i < 10; i++)
        gen_beautiful_num(i, 1, {i});
    
    k1_beautiful.pb(1111111111);
    k2_beautiful.pb(1111111111);
    k2_beautiful.pb(1e9);

    sort(all(k1_beautiful));
    sort(all(k2_beautiful));


    while(t--){
        cin >> n >> k;

        if(k == 1)
            cout << *lower_bound(all(k1_beautiful), n) << '\n';
        else 
            cout << *lower_bound(all(k2_beautiful), n) << '\n';
    }

    return 0;
}
 
void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cerr.tie(0); }
void FreeOpen(){ freopen("input.txt", "r", stdin); freopen("output.txt", "c", stdout); }
template <typename T> void printDbg(const T& x){ cerr << x; }
template <typename T, typename U>void printDbg(const pair<T, U>& value){ cerr << "("; printDbg(value.first); cerr << ", "; printDbg(value.second); cerr << ")"; }
template <typename T, typename... Args>void printDbg(const T& value, Args... args){printDbg(value); cerr << ", "; printDbg(args...); }
template <typename... Args> void debug(Args... args){ cerr << "[";  printDbg(args...); cerr << "]\n"; }
template <typename K, typename V> void debug(const map<K, V>& container){ cerr << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cerr << ", "; cerr << '['; printDbg(k); cerr << ", "; printDbg(v); cerr << ']'; comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const set<T>& container) { cerr << '['; bool comma = 0; for (const auto& st : container) { if (comma) cerr << ", "; printDbg(st); comma = 1; } cerr << "]\n";}
template <typename T> void debug(const vector<T>& container) { cerr << '['; bool comma = 0; for (const auto& v : container){ if(comma) cerr << ", "; printDbg(v); comma = 1; } cerr << "]\n"; }
template <typename T> void debug(const vector<vector<T>> &container) { for (const auto &v : container) debug(v); }
