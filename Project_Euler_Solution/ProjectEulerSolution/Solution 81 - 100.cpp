#include <iostream>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <tuple>
#include <set>
#include <map>
#define ll long long int
#define ull unsigned long long int
#define Map unordered_map
#define Set unordered_set
#define pb push_back
#define all(x) x.begin(), x.end()
#define All(x) x.rebegin, r.rend()
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
int main(){
    
    FastIO();
    auto Solution_81 = [&]() {
        /*⁡⁢⁢⁢Given n x n matrix consisting of an integer, find minimal path sum by only moving to the right and down⁡*/
        int n; cin >> n;
        vector<vector<int>> matrix(n, vector<int>(n));

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cin >> matrix[i][j];
        
        function<int(int, int)> explore = [&](int i, int j) -> int {
            if(i < 0 || j < 0 || i == n || j == n)
                return 0;
            matrix[i][j] += max(explore(i + 1, j), explore(i, j + 1));
        };

        Debug(explore(0, 0));
    };

    auto Solution_82 = [&]() {
        /*⁡⁢⁢⁢⁡⁢⁢⁢Given n x n matrix consisting of an integer, find minimal path sum by only moving to the right, up, an down⁡ ⁡⁢⁢⁢staring from any left path⁡*/
        int n; cin >> n;
        vector<vector<int>> matrix(n, vector<int>(n));
        vector<int> sum(n, 1e9);
        
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cin >> matrix[i][j];
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> explore;
        for(int i = 0; i < n; i++)
            explore.push({i, 0});
        while(!explore.empty()){
            auto [i, j] = explore.top();
            explore.pop();
        }
    };

    auto Solution_83 = [&]() {

    };

    auto Solution_84 = [&]() {

    };

    auto Solution_85 = [&]() {

    };

    auto Solution_86 = [&]() {

    };

    auto Solution_87 = [&]() {
        /*⁡⁢⁢⁢How many numbers below fify million can be expressed as the sum of prime square, prime cube, and prime quartic⁡*/
        int mx = 5e7, a = sqrt(mx), b = cbrt(mx), c = sqrt(sqrt(mx));
        vector<bool> prime(a + 1, 1);
        vector<vector<int>> primes(3);

        for(int i = 2; i*i <= a; i++)
            if(prime[i]){
                if(i <= a)
                    primes[0].push_back(i);
                if(i <= b)
                    primes[1].push_back(i);
                if(i <= c)
                    primes[2].push_back(i);

                for(int j = i*i; j <= a; j += i)
                    prime[j] = 0;
            }
        for(int i = sqrt(a) + 1; i <= a; i++)
            if(prime[i]){
                if(i <= a)
                    primes[0].push_back(i);
                if(i <= b)
                    primes[1].push_back(i);
                if(i <= c)
                    primes[2].push_back(i);
            }
    
        vector<map<int, int>> powerI(3);

        for(int p : primes[0])
            powerI[0][p] = p*p;
        for(int p : primes[1])
            powerI[1][p] = p*p*p;
        for(int p : primes[2])
            powerI[2][p] = p*p*p*p;

        set<int> prime_power_triple;
        for(int p : primes[0])
            for(int q : primes[1])
                for(int r : primes[2]){
                    int N = powerI[0][p] + powerI[1][q] + powerI[2][r];
                    if(N < mx)
                        prime_power_triple.insert(N);
                }
        Debug(prime_power_triple.size());
    };

    auto Solution_88 = [&]() {

    };

    auto Solution_89 = [&]() {

    };

    auto Solution_90 = [&]() {

    };

    auto Solution_91 = [&]() {
        
    };

    auto Solution_92 = [&]() {
        /*We Define SDC(n) the sum of the square of digits of n. Any chain thath arrives at 1 or 89 will become stuck in an endless loop.
          Every starting number will eventually arrive at 1 or 89. How many starting numbers below ten million will arrive at 89*/
        ll mx(1e7), res(1);
        vector<int> square(10);
        vector<bool> visited(mx + 1, 0);

        for(int i = 0; i < 10; i++)
            square[i] = i*i;
        
        auto SDC = [&](ll n) -> ll {
            ll x(0);
            while(n)
                x += square[n % 10], n /= 10;
            return x;
        };

        function<ll(ll)> arrive_at_89 = [&](ll n) -> bool {
            if(n == 1 || n == 89)
                return (n == 89);
            if(n <= mx)
                visited[n] = 1;
            
            bool valid = arrive_at_89(SDC(n));
            res += (valid && n <= mx);
            return valid;
        };

        for(int i = 1; i < mx; i++)
            if(!visited[i] && arrive_at_89(i))
                res += 0;
        Debug(res);
    };

    auto Solution_93 = [&]() {

    };

    auto Solution_94 = [&]() {

    };

    auto Solution_95 = [&]() {

    };

    auto Solution_96 = [&]() {

    };

    auto Solution_97 = [&]() {

    };

    auto Solution_98 = [&]() {

    };

    auto Solution_99 = [&]() {

    };

    auto Solution_100 = [&]() {
        
    };

    cout << "Put the number of of the Problem : ";
    int number; cin >> number;
    switch(number){
        case 81 : Solution_81(); break;
        case 82 : Solution_82(); break;
        case 83 : Solution_83(); break;
        case 84 : Solution_84(); break;
        case 85 : Solution_85(); break;
        case 86 : Solution_86(); break;
        case 87 : Solution_87(); break;
        case 88 : Solution_88(); break;
        case 89 : Solution_89(); break;
        case 90 : Solution_90(); break;
        case 91 : Solution_91(); break;
        case 92 : Solution_92(); break;
        case 93 : Solution_93(); break;
        case 94 : Solution_94(); break;
        case 95 : Solution_95(); break;
        case 96 : Solution_96(); break;
        case 97 : Solution_97(); break;
        case 98 : Solution_98(); break;
        case 99 : Solution_99(); break;
        case 100 : Solution_100(); break;
    }

    return 0;
}

void FastIO(){ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); }
template <typename T> void printDebug(const T& x){ cout << x; }
template <typename T, typename U>void printDebug(const pair<T, U>& value){ cout << "("; printDebug(value.first); cout << ", "; printDebug(value.second); cout << ")"; }
template <typename T, typename... Args>void printDebug(const T& value, Args... args){ cout << value << ", "; printDebug(args...); }
template <typename... Args> void Debug(Args... args){ cout << "[";  printDebug(args...); cout << "]\n"; }
template <typename K, typename V> void Debug(const map<K, V>& container){ cout << '['; bool comma = 0; for(auto [k, v] : container){ if(comma) cout << ", "; cout << '['; printDebug(k); cout << ", "; printDebug(v); cout << ']'; comma = 1; } cout << "]\n"; }
template <typename T> void Debug(const set<T>& container) { cout << '['; bool comma = 0; for (const auto& st : container) { if (comma) cout << ", "; printDebug(st); comma = 1; } cout << "]\n";}
template <typename T> void Debug(const vector<T>& container) { cout << '['; bool comma = 0; for (const auto& v : container){ if(comma) cout << ", "; printDebug(v); comma = 1; } cout << "]\n"; }
