
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
    int t,n,mx(1e6),min_move,move,min_exp; cin >> t;
    vector<bool> prime(mx + 1, 1);
    vector<vector<pair<int, int>>> factor(mx + 1);

    for(int i = 2; i*i <= mx; i++) if(prime[i])
        for(int j = i, a,c; j <= mx; j += i){
            prime[j] = 0;

            a = j, c = 0;
            while(!(a % i))
                a /= i, c++;
            factor[j].pb({i, c});
        }

    for(int i = 1e3 + 1; i <= mx; i++) if(prime[i])
        for(int j = i, a,c; j <= mx; j += i){
            a = j, c = 0;
            while(!(a % i))
                a /= i, c++;
            factor[j].pb({i, c});
        }

    while(t--){
        cin >> n;
        Set<int> primes;
        vector<int> A(n);

        for(int &x : A){
            cin >> x;
            for(auto [p, a] : factor[x])
                primes.insert(p);
        }

        min_move = 0;
        for(int p : primes){
            vector<int> exp(n, 0);

            for(int i = 0; i < n; i++) 
                for(auto [q, a] : factor[A[i]])
                    if(p == q)
                        exp[i] = a;
            
            move = 0, min_exp = *min_element(all(exp));
            for(int i = 0, pos; i < n; i++) if(exp[i] == min_exp) {
                pos = i + 1;
                while(pos < n && exp[pos] != min_exp)
                    pos++;

                move = max(move, pos - i - 1);
                i = pos - 1; 
            } 

            for(int i = 0, j = n - 1; !i && j == n - 1;){
                while(i < n && exp[i] != min_exp)
                    i++;
                while(j >= 0 && exp[j] != min_exp)
                    j--;

                move = max(move, i + n - j - 1);
                break;
            } 


            min_move = max(min_move, move);
        }

        cout << min_move << '\n';
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
