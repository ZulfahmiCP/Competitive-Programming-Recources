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
    // Todo
    auto Solution_61 = [&]() {
        /*Triangle, Square, Pentagonal, Hexagonal,, Heptagonal, and Octagonal numbers are all figurate (polygonal) numbers and are generated by the following formula :
          Tringle T(n) = n(n + 1)/2, Square S(n) = n^2, Pentagonal P(n) = n(3n - 1)/2, Hexagonal X(n) = n(2n - 1), Heptagonal H(n) = n(5n - 3)/2, Octagonal O(n) = n(3n - 2) 
          Find the sum of ony ordered set A of six cyclic 4-digit numbers for each numbers satisfy this property
          1. The set is cyclic, such that last two digit of A[i] is first two digit of A[i + 1] and last two digit of A[6] is the first two digit of A[1]
          2. For each elemenet, they have different type of Valid Polygonal numbers*/
        auto polygonal_type = [&](int n) -> int {
            int t = ((int)(sqrt(8*n + 1) - 1) >> 1);
            if((t*(t + 1) >> 1) == n) 
                return 1;
            
            int s = sqrt(n);
            if(s*s == n)
                return 2;
            
            int p = ((int)(sqrt(24*n + 1) + 1)/6);
            if((p*(3*p - 1) >> 1) == n)
                return 3;
            
            int x = ((int)(sqrt(8*x + 1) + 1) >> 2);
            if(x*(2*x - 1) == n)
                return 4;
            
            int h = ((int)(sqrt(40*x + 9) +3)/10);
            if(h*(5*h - 3) == n)
                return 5;
            
            return -1;
        };

        for(int n = 58, O; n < 183; n++){
            O = n*(3*n - 2);
            vector<pair<int, int>> cyclic_figurate_nums = {{O, 6}};
            vector<bool> visited(6, 0);

            int cur = O % 100;
            for(int i = 0; i < 4; i++){
                for(int j = 1; j < 10; j++)
                    for(int j = 2; j < 10; j++)
                        if(i == 2)
                            break;
            }
        }
    };

    auto Solution_62 = [&]() {
        /*⁡⁢⁢⁢Find the smallest cube numbers such that fo which exactly 5 permutation of its digits are cubes⁡*/
        auto string_to_ll = [&](string s) -> ll {
            ll x(0);
            
            for(char c : s){
                x *= 10;
                x += (c - '0');
            }
            
            return x;
        };
        
        vector<ll> visited(1e12, 0);
        auto cubic_perm = [&](ll x) -> vector<ll> {
            string s = to_string(x);
            vector<ll> perm;

            sort(all(s));

            if(s[0] == '0')
                swap(s[0], s[1]);

            do {
                ll n = string_to_ll(s), c = floor(cbrt(n));
                visited[n] = 1;
                if(c*c*c == n)
                    perm.pb(n);
            } while(next_permutation(all(s)));

            return perm;
        };

        for(ll i = 1e2 + 1; i < 1e4; i++){
            if(visited[i*i*i])
                continue;

            vector<ll> CPD = cubic_perm(i*i*i);
            if(CPD.size() == 5){
                Debug(CPD);
                return;
            }
        }
    };

    auto Solution_63 = [&]() {
        /*⁡⁢⁢⁢How many n - digit positive integer which are also an n-th power?⁡*/
        auto digit = [&](double x) -> int {
            int d(0);
            while(x >= 1){
                x /= 10;
                d++;
            }

            return d;
        };

        int count(0);
        for(int i = 1; i <= 21; i++)
            for(int j = 1; j < 10; j++){
                double a(j);
                int d = digit(floor(pow(a, i)));

                if(d == i)
                    count++;
            }
        Debug(count);
    };

    auto Solution_64 = [&]() {

    };

    auto Solution_65 = [&]() {

    };

    auto Solution_66 = [&]() {

    };

    auto Solution_67 = [&]() {
        /*⁡⁢⁢⁢Given a path in a form of triangle, by starting at the top of the triangle and moving to adjacent numbers ont he row.
          Find the maximum total from top to bottom the file txt⁡*/
        int n; cin >> n;
        vector<vector<int>> triangle(n);

        for(int i = 0; i < n; i++)
            for(int j = 0, a; j < i + 1; j++){
                cin >> a;
                triangle[i].pb(a);
            }
        
        function<int(int, int)> maximum_path_sum = [&](int i, int j) -> int {
            if(i == n - 1)
                return triangle[i][j];
            
            triangle[i][j] += max(maximum_path_sum(i + 1, j), maximum_path_sum(i + 1, j + 1));
        };

        Debug(maximum_path_sum(0, 0));
    };

    auto Solution_68 = [&]() {

    };

    auto Solution_69 = [&]() {
        /*⁡⁢⁢⁢Given integer n, find the maximum of k/phi(k) where 1 <= k <= n⁡ */
        int n(1e6);
        vector<int> phi(n + 1, 1);
        vector<bool> prime(n + 1, 1);

        for(int i = 2; i <= n; i++)
            if(prime[i]){
                phi[i] = i - 1;
                for(int j = 2LL*i; j <= n; j += i){
                    prime[j] = 0;
                    phi[j] /= i;
                    phi[j] *= (i - 1);
                }
            }
        
        double max_phi(0), max_k;
        for(int i = 2; i <= n; i++){
            double check = ((double)i/(double)phi[i]);
            if(check > max_phi)
                max_phi = check, max_k = i;
        }

        Debug(max_k, max_phi);
    };

    auto Solution_70 = [&]() {
        /*⁡⁢⁢⁢Given integer n, find all k such that phi(k) is a permutation of k where 1 <= k <= n⁡ */
        auto is_permutation = [&](int a, int b) -> bool {
            string s = to_string(a), t = to_string(b);
            sort(all(s)); sort(all(t));
            return a == b;
        };

        int n(1e6);
        vector<int> phi(n + 1, 1);
        vector<bool> prime(n + 1, 1);

        for(int i = 2; i <= n; i++)
            if(prime[i]){
                phi[i] = i - 1;
                for(int j = 2LL*i; j <= n; j += i){
                    prime[j] = 0;
                    phi[j] /= i;
                    phi[j] *= (i - 1);
                }
            }
        
        int count(0);
        for(int i = 2; i <= n; i++)
            if(is_permutation(i, phi[i]))
                count++;
        Debug(count);
    };

    auto Solution_71 = [&]() {
        
    };

    auto Solution_72 = [&]() {

    };

    auto Solution_73 = [&]() {

    };

    auto Solution_74 = [&]() {
        /*⁡⁢⁢⁢Suppose thath DFC(n) is define as the sum of a factorial of digit n. Find all number n below one million such that n produces sixty non repeating terms⁡.*/
        ll mx(1e6);
        vector<ll> factorial(10);

        factorial[0] = 1;
        for(ll i = 1; i < 10; i++)
            factorial[i] = i * factorial[i - 1];
        
        auto DCF = [&](ll n) -> ll {
            ll x(0);
            while(n)
                x += factorial[n % 10], n /= 10;

            return x;
        };

        vector<ll> max_dcf_sequence;
        for(ll i = 1, x; i < 1e6; i++){
            map<ll, bool> visited;
            x = i;

            while(!visited[x]){
                visited[x] = 1;
                x = DCF(x);
            }
            
            if(visited.size() == 60)
                max_dcf_sequence.pb(i);
        }
        Debug(max_dcf_sequence.size());
        Debug(max_dcf_sequence);
    };

    auto Solution_75 = [&]() {

    };

    auto Solution_76 = [&]() {

    };

    auto Solution_77 = [&]() {

    };

    auto Solution_78 = [&]() {

    };

    auto Solution_79 = [&]() {

    };

    auto Solution_80 = [&]() {
        
    };

    cout << "Put the number of of the Problem : ";
    int number; cin >> number;
    switch(number){
        case 61 : Solution_61(); break;
        case 62 : Solution_62(); break;
        case 63 : Solution_63(); break;
        case 64 : Solution_64(); break;
        case 65 : Solution_65(); break;
        case 66 : Solution_66(); break;
        case 67 : Solution_67(); break;
        case 68 : Solution_68(); break;
        case 69 : Solution_69(); break;
        case 70 : Solution_70(); break;
        case 71 : Solution_71(); break;
        case 72 : Solution_72(); break;
        case 73 : Solution_73(); break;
        case 74 : Solution_74(); break;
        case 75 : Solution_75(); break;
        case 76 : Solution_76(); break;
        case 77 : Solution_77(); break;
        case 78 : Solution_78(); break;
        case 79 : Solution_79(); break;
        case 80 : Solution_80(); break;
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
