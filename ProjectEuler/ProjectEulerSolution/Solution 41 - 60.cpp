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
#define ll unsigned long long int
#define all(x) x.begin(), x.end()
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

    auto Solution_41 = [&]() {
        /*⁡⁢⁢⁢Find the largest n-pandigital prime that exist⁡*/
        ll mx = 1e10;
        vector<ll> prime(mx + 1, 1);

        for(int i = 2; i*i < mx; i += (i == 2 || i == 3 ? (i == 2 ? 1 : 2) : (i % 6 == 1 ? 4 : 2)))
            if(prime[i])
                for(ll j = i*i; j < mx; j += i)
                    prime[j] = 0;
            
        auto is_pandigital = [&](ll n) -> bool {
            string s = to_string(n);

            sort(all(s));
            for(int i = 0; i < s.size(); i++)
                if(s[i] - '0' != i + 1)
                    return 0;
            return 1;
        };

        ll largest_pandigital_prime(0);
        for(ll i = 5; i < mx; i += (i % 6 == 1 ? 4 : 2))
            if(prime[i] && is_pandigital(i))
                largest_pandigital_prime = i;
        Debug(largest_pandigital_prime);
    };

    auto Solution_42 = [&]() {
        /*Trinagle sequence is defined as tn = n(n + 1)/2;
          By converting all n words to number for each character in alphabetic order.
          The value of a word is the sum of number for each char. Count how many the
          of words that are triangle number*/
        int n; cin >> n;
        vector<string> word_list;
        for(int i = 0; i < n; i++)
            cin >> word_list[i];

        auto is_triangle_number = [&](int t) -> bool {
            int x = ((int)(sqrt(8*t + 1) - 1) >> 1);
            return (x*(x + 1) >> 1 == t);
        };

        auto value = [&](string word) -> bool {
            int Val(0);
            for(char c : word)
                Val += (c - '0');
            
            return is_triangle_number(Val);
        };

        int triangle_word_count(0);
        for(string word : word_list)
            triangle_word_count += (value(word));
        Debug(triangle_word_count);
    };

    auto Solution_43 = [&]() {
        /*A number n is alled SDP if and only if the n is a 0 to 9 
          pandigital number and satisfiy the following condition.
          Suppose that dk is k-th digit of number n
          ~ 2  | d2d3d4
          ~ 3  | d3d4d5
          ~ 5  | d4d5d6
          ~ 7  | d5d6d7
          ~ 11 | d6d7d8
          ~ 13 | d7d8d9
          ~ 17 | d8d9d10
          Find the sum of all number n with this property*/
        vector<int> p = {2, 3, 5, 7, 11, 13, 17};
        auto is_SDP = [&](string s) -> bool {
            for(int i = 1; i < s.size() - 2; i++)
                if((100*(s[i] - '0') + 10*(s[i + 1] - '0') + (s[i] - '0')) % p[i - 1])
                    return 0;
            return 1;
        };

        string n = "1023456789";
        vector<int> SDP;
        ll valid_sum = 0;
        do {
            if(is_SDP(n)){
                ll x = stoi(n);
                SDP.push_back(x);
                valid_sum += x;
            }
        } while(next_permutation(all(n)));

        Debug(valid_sum);
        Debug(SDP);
    };

    //todo
    auto Solution_44 = [&]() {

    };

    auto Solution_45 = [&]() {
        /*⁡⁢⁢⁢Triangular sequence is define as Tn = n(n + 1)/2
          Pentagonal sequence is define as Pn = n(3n - 1)/2
          Hexagonal sequence is define as Hn = n(2n - 1)
          Find the first n number that are triangular, pentagonal, and hexagonal⁡*/
        int n; cin >> n;
        vector<int> THP;
        
        auto is_triangular = [&](ll t) -> bool {
            ll n = ((ll)(sqrt(8*t + 1) - 1) >> 1);
            return (n*(n + 1) >> 1 == t);
        };

        auto is_pentagonal = [&](ll p) -> bool {
            ll n = ((ll)(sqrt(24*p + 1) + 1)/6);
            return (n*(3*n - 1) >> 1 == p);
        };

        for(ll i = 1, x; THP.size() < n; i++){
            x = i*(2*i - 1);
            if(is_triangular(x) && is_pentagonal(x))
                THP.push_back(x);
        }

        Debug(THP);
    };

    auto Solution_46 = [&]() {
        /*⁡⁢⁢⁢Goldbach Conjecture say that every composite number can be written as the
          sum of x^2 + p where p is a prime number. What is the smallest odd composite
          number below n that can't be written that not satisify this condition⁡*/
        int n; cin >> n;
        vector<int> prime(n + 1, 1);
        vector<int> primes;

        for(int i = 2; i*i <= n; i += (i == 2 || i == 3 ? (i == 2 ? 1 : 2) : (i % 6 == 1 ? 4 : 2)))
            if(prime[i])
                for(int j = i*i; j <= n; j += i)
                    prime[j] = 0;
        
        vector<bool> goldbach(n + 1, 0);
        for(int x = 0; x*x <= n; x++)
            for(int p = 0; p < primes.size() && x*x + primes[p] <= n; p++)
                goldbach[x*x + p] = 1;
        
        for(int i = 9; i <= n; i += 2)
            if(!goldbach[i]){
                Debug(i);
                return;
            }
    };

    auto Solution_47 = [&]() {
        /*⁡⁢⁢⁢Find the first n consecutive number that have each n numbers have n primes factors below mx⁡*/
        ll n,mx; cin >> n >> mx;
        vector<bool> prime(mx + 1, 1);   
        vector<int> prime_factor(mx + 1, 0);

        for(ll i = 2; i*i <= mx; i += (i == 2 || i == 3 ? (i == 2 ? 1 : 2) : (i % 6 == 1 ? 4 : 2)))
            if(prime[i]){
                prime_factor[i]++;
                for(ll j = 2*i; j <= mx; j += i)
                    prime[j] = 0, prime_factor[j]++;
            }

        for(ll i = sqrt(mx) + 1; i <= mx; i++)
            if(prime[i]){
                prime_factor[i]++;
                for(ll j = 2*i; j <= mx; j += i)
                    prime_factor[j]++;
            }
        
        for(ll i = 2; i <= mx - n; i++){
            bool is_DFP = 1;
            vector<int> DFP;
            for(ll j = i ; j <= i + n && is_DFP; j++)
                is_DFP &= (prime_factor[j] == n), DFP.push_back(j);
            
            if(is_DFP){
                Debug(DFP);
                return;
            }
        }

        Debug(-1);
    };

    auto Solution_48 = [&]() {
        /*Find the last ten digits of 1^1 + 2^2 + ... + n^n*/
        int n; cin >> n;

        auto multiply_string = [&](string a, string b) -> string {
            int n = a.size(), m = b.size();
            string res(n + m, '0');

            for(int i = n - 1; i >= 0; i--){
                int carry = 0;
                for(int j = m - 1; j >= 0; j--){
                    int p = (a[i] - '0') * (b[j] - '0') + (res[i + j + 1] - '0') + carry;
                    carry = p/10;
                    res[i + j + 1] = char(p % 10 + '0');
                }
                res[i] = char(carry + '0');
            }

            while(res[0] == '0')
                res.erase(0, 1);

            return res;
        };

        auto add_string = [&](string a, string b) -> string {
             if(a.size() < b.size())
                swap(a, b);
            while(b.size() != a.size())
                b = "0" + b;
        
            int n = a.size(), carry = 0;
            string result;
            for(int i = n - 1; i > -1; i--){
                int digit = (a[i] - '0' + b[i] - '0');
                result = (char)(((digit % 10) + carry) % 10 + '0') + result;
                carry = (digit + carry)/10;
            }

            if(carry)
                result = to_string(carry) + result;

            return result;
        };

        string ans = "0";
        for(int i = 1; i <= n; i++){
            string I = to_string(i), temp = "1";
            for(int j = 0; j < i; j++)
                temp = multiply_string(temp, I);
            ans = add_string(ans, temp);
        }
        Debug(ans);
    };

    auto Solution_49 = [&]() {
        /*The sequence integer of p, q, r, is called prime perm if and only if
          all the element are prime and the sequence is in the form of arithmatic
          progression and p, q, r are a permutation of each other. There is exactly 
          two triple 4 digits of p,q,r that is in this condition. Find all of them*/
        int mx = 1e5;
        vector<bool> prime(mx + 1, 1), visited(mx + 1, 0);

        for(int i = 2; i*i <= mx; i += (i == 2 || i == 3 ? (i == 2 ? 1 : 2) : (i % 6 == 1 ? 4 : 2)))
            if(prime[i])
                for(int j = i*i; j <= mx; j += i)
                    prime[j] = 0;
        
        auto prime_perm = [&](int n) -> vector<int> {
            string s = to_string(n);
            vector<int> perm = {n};

            while(next_permutation(all(s))){
                int x = stoi(s);
                if(prime[x])
                    perm.push_back(x);
                visited[x] = 1;
            }    
            
            sort(all(perm));
            n = perm.size();
            for(int p = 0; p < n; p++)
                for(int q = p + 1; q < n; q++)
                    for(int r = q + 1; r < n; r++)
                        if(perm[q] - perm[p] == perm[r] - perm[q])
                            return {perm[p], perm[q], perm[r]};
            return {};
        };

        for(int i = 1002; i <= mx; i += (i % 6 == 1 ? 4 : 2))
            if(prime[i] && !visited[i]){
                auto P = prime_perm(i);
                if(P.size() == 3)
                    Debug(P);
            }
    };

    auto Solution_50 = [&]() {
        /*Find a prime number that are below n that can be 
          written as the sum of the most consecutive primes*/
        int n; cin >> n;
        vector<bool> prime(n + 1, 1);
        vector<int> primes;

        for(int i = 2; i*i <= n; i += (i == 2 || i == 3 ? (i == 2 ? 1 : 2) : (i % 6 == 1 ? 4 : 2)))
            if(prime[i]){
                primes.push_back(i);
                for(int j = i*i; j <= n; j += i)
                    prime[j] = 0;      
            }

        for(int i = sqrt(n) + 1; i <= n; i++)
            if(prime[i])
                primes.push_back(i);
        
        int LCP_leng(0), LCP;
        for(int i = 0, x, c; i < primes.size(); i++){
            x = primes[i], c = i;
            for(int j = i + 1; j < primes.size() && prime[x] && x + primes[j] <= n; j++)
                x += primes[j], c++;
            if(c - i > LCP_leng)
                LCP_leng = c - i, LCP = x;
        }

        Debug(LCP_leng, LCP);
    };

    auto Solution_51 = [&]() {

    };

    auto Solution_52 = [&]() {
        /*⁡⁢⁢⁢Find the smallest integer n such that n,2n,3n,4n,5n,6n contain the same digits⁡*/
        int mx = 1e7;
        auto is_permuted_multiples = [&](int x) -> bool {
            string s = to_string(x);
            sort(all(s));

            for(int i = 2; i <= 6; i++){
                string t = to_string(i*x);
                sort(all(t));
                if(t != s)
                    return 0;
            }

            return 1;
        };

        for(int i = 10; i < mx; i++)
            if(is_permuted_multiples(i)){
                Debug(i);
                return;
            }
    };

    auto Solution_53 = [&]() {
        /*How many value of nCr is greater that million for 1 <= n <= 100*/
        ll M(1e12), c(0), n(100);

        vector<vector<ll>> C(n + 1, vector<ll>(n + 1));

        for(int i = 0; i <= n; i++)
            C[i][0] = C[i][i] = 1;
        
        for(int i = 1; i <= n; i++)
            for(int j = 1; j < i; j++){
                C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
                C[i][j] %= M;
                c += (C[i][j] > 1e6);
            }
        Debug(c);
    };

    auto Solution_54 = [&]() {
        
    };

    auto Solution_55 = [&]() {
        /*Suppose we take some number, reverse and add, until its become palindrome. 
          The number that never produce a palindrome below fifty iteration is called
          a Lychrel Number. Find all Lychrel Number below one thousand*/
        int mx = 1e4;

        auto reverse_ = [&](ll n) -> ll {
            ll x(0);
            while(n){
                x *= 10;
                x += (n % 10);
                n /= 10;
            }
            return x;
        };

        auto is_palindrome = [&](ll n) -> bool {
            return (n == reverse_(n));
        };

        auto lychrel = [&](ll n) -> bool {
            for(int i = 0; i < 50; i++){
                n += reverse_(n);
                if(is_palindrome(n))
                    return 0;
            }
            return 1;
        };

        vector<int> lychrel_num;
        for(ll i = 1; i < mx; i++)
            if(lychrel(i))
                lychrel_num.push_back(i);
        Debug(lychrel_num.size());
        Debug(lychrel_num);
    };

    auto Solution_56 = [&]() {
        /*⁡⁢⁢⁢Considering number of the form a^b, where a,b < 100, what is the maximum digital sum?⁡*/
        auto multiply_string = [&](string a, string b) -> string {
            int n = a.size(), m = b.size();
            string res(n + m, '0');

            for(int i = n - 1; i >= 0; i--){
                int carry(0);
                for(int j = m - 1; j >= 0; j--){
                    int p = (a[i] - '0') * (b[j] - '0') + (res[i + j + 1] - '0') + carry;
                    carry = p/10;
                    res[i + j + 1] = char(p % 10 + '0');
                }
                res[i] = char(carry + '0');
            }

            while(res[0] == '0')
                res.erase(0, 1);

            return res;
        };

        auto sum_of_digit = [&](string s) -> int {
            int sum(0);
            for(char c : s)
                sum += (c - '0');
            return sum;
        };

        int max_digit_sum(0);
        for(int i = 2; i < 100; i++){
            string I = to_string(i), temp = "1";
            for(int j = 1; j < 100; j++){
                temp = multiply_string(temp, I);
                max_digit_sum = max(max_digit_sum, sum_of_digit(temp));
            }
        }

        Debug(max_digit_sum);
    };

    auto Solution_57 = [&]() {
        /*The sqrt(2) can be expressed as the infinite fraction of 1 + 1/(2 + 1/(2 + 1/(2 + ...)))
          In the first one thousand expansions, how many fraction contain a numerator with more 
          digits than the denominator ?*/
        int n = 1e3;
        vector<pair<string, string>> fraction(n + 1);

        auto multiple_two = [&](string a) -> string {
            int n = a.size(), carry = 0;
            string result;
            for(int i = n - 1; i > -1; i--){
                int digit = 2*(a[i] - '0');
                result = (char)(((digit % 10) + carry % 10) % 10 + '0') + result;
                carry = (digit + carry)/10;
            }

            if(carry)
                result = to_string(carry) + result;

            return result;
        };

        auto add_string = [&](string a, string b) -> string {
            if(a.size() < b.size())
                swap(a, b);
            while(b.size() != a.size())
                b = "0" + b;
        
            int n = a.size(), carry = 0;
            string result;
            for(int i = n - 1; i > -1; i--){
                int digit = (a[i] - '0' + b[i] - '0');
                result = (char)(((digit % 10) + carry) % 10 + '0') + result;
                carry = (digit + carry)/10;
            }

            if(carry)
                result = to_string(carry) + result;

            return result;
        };

        fraction[1] = {"3", "2"};
        ll valid_sum = 0;
        for(ll i = 2; i <= n; i++){
            auto [A, B] = fraction[i - 1];
            fraction[i] = {add_string(A, multiple_two(B)), add_string(A, B)};

            if(fraction[i].first.size() > fraction[i].second.size())
                valid_sum++;
        }

        Debug(valid_sum);
    };

    auto Solution_58 = [&]() {
        /*⁡⁢⁢⁢Considering spiral numbers that spiralling anticlockwise int the following way,  square spiral with side length 5 is formed.⁡
          ⁡⁢⁢⁢17 16 15 14 13 
          18 5  4  3  12
          19 6  1  2  11
          20 7  8  9  10
          21 22 23 24 25
          We can see that the amount of diagonal that are prime is 5 which is 3, 5, 7, 8, 17, 13. Which is in the ratio of 5/7 = 71 %
          Find the smallest side of length such that the the ratio of amount of diagonal that are prime falls below n % !⁡
          */
        auto is_prime = [&](int x) -> bool {
            if(!(x & 1) && x != 2)    
                return 0;

            for(int i = 3; i*i <= x; i += 2)
                if(!(x % i))
                    return 0;
            
            return 1;
        };

        int n; cin >> n;

        int diagonal_prime_count(0);
        for(int i = 3, p; ; i += 2){
            p = i*i;
            for(int j = 1; j < 4; j++)
                if(is_prime(p - j*(i - 1)))
                    diagonal_prime_count++;
            
            if(diagonal_prime_count/(double)(2*i - 1) < 10){
                Debug(i);
                return;
            }
        }
    };

    auto Solution_59 = [&]() {

    };

    auto Solution_60 = [&]() {
        
    };

    int number; cin >> number;
    switch(number){
        case 41 : Solution_41(); break;
        case 42 : Solution_42(); break;
        case 43 : Solution_43(); break;
        case 44 : Solution_44(); break;
        case 45 : Solution_45(); break;
        case 46 : Solution_46(); break;
        case 47 : Solution_47(); break;
        case 48 : Solution_48(); break;
        case 49 : Solution_49(); break;
        case 50 : Solution_50(); break;
        case 51 : Solution_51(); break;
        case 52 : Solution_52(); break;
        case 53 : Solution_53(); break;
        case 54 : Solution_54(); break;
        case 55 : Solution_55(); break;
        case 56 : Solution_56(); break;
        case 57 : Solution_57(); break;
        case 58 : Solution_58(); break;
        case 59 : Solution_59(); break;
        case 60 : Solution_60(); break;
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
