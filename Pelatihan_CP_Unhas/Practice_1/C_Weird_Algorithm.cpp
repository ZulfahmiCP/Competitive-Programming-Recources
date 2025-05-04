#include <bits/stdc++.h>
using namespace std;

void f(long long n) {
    cout << n << ' ';

    if(n == 1) 
        return;

    if(n % 2 == 1)
        f(3 * n + 1);
    else 
        f(n / 2);
}

int main() {

    long long n; cin >> n;
    f(n);

    return 0;
}