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

struct Sieve {
    bool isPrime(ll n) {
        for(int i = 2; 1LL * i * i <= n; i++)
            if(!(n % i))
                return 0;
        return 1;
    }

    vector<bool> getPrimes(int n) {
        vector<bool> prime(n, 1);
        
        prime[0] = prime[1] = 0;
        for(int i = 2; i * i <= n; i++) if(prime[i]) 
            for(int j = i * i; j <= n; j += i)
                prime[j] = 0;
        
        return prime;
    }

    vector<int> getDivisorCount(int n) {
        vector<int> divisor_count(n + 1, 0);

        for(int i = 1; i <= n; i++)
            for(int j = i; j <= n; j += i)
                divisor_count[j]++;
        
        return divisor_count;
    }

    vector<int> getSumDivisor(int n) {
        vector<int> divisor_sum(n + 1, 0);

        for(int i = 1; i <= n; i++)
            for(int j = i; j <= n; j += i)
                divisor_sum[j] += i;

        return divisor_sum;   
    }

    vector<int> getTotient(int n) {
        vector<int> totient(n + 1);
        iota(all(totient), 0);

        for(int i = 2; i <= n; i++) if(totient[i] == i) 
            for(int j = i; j <= n; j += i)
                totient[j] -= totient[j]/i;

        return totient;
    }

    vector<int> getBiggestPrimeFactor(int n) {
        vector<int> biggest_prime_factor(n + 1, 1);

        for(int i = 2; i <= n; i++) if(biggest_prime_factor[i] == 1)
            for(int j = i; j <= n; j += i)
                biggest_prime_factor[j] = i;
            
        return biggest_prime_factor;
    }

    vector<vector<pair<int, int>>> getFactorization(int n) {
        vector<bool> prime(n + 1, 1);
        vector<vector<pair<int, int>>> factorization(n + 1);

        for(int p = 2; p <= n; p++) if(prime[p]) 
            for(int i = p, a,num; i <= n; i += p){
                a = 0, num = i;

                while(!(num % p))
                    num /= p, a++;
                
                factorization[i].pb({p, a});
                prime[i] = 0;
            }

        return factorization;
    }

    vector<int> getNumberOfPrimeDivisors(int n) {
        vector<int> mind(n + 1, -1), val(n + 1);
        mind[1] = 1;

        for(int i = 2; i <= n; i++) if(mind[i] == -1)
            for(int j = i; j <= n; j += i)
                if(mind[j] == -1)
                    mind[j] = i;

        for(int i = 2, j; i <= n; i++){
            j = i / mind[i];
            val[i] = val[j] + (mind[i] != mind[j]);
        }

        return val;
    }
};


int main(){
 
    FastIO();
    ll b,mx(1e7); cin >> b;
    Sieve sieve;
    vector<bool> prime = sieve.getPrimes(mx);
    vector<int> primes{0};

    for(int i = 2; i <= mx; i++)
        if(prime[i])
            primes.pb(i);
    
    for(int i = 1, p; i < primes.size(); i += 2){
        p = primes[i];
        
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
