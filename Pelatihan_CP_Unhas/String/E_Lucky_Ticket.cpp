#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;
    string s; cin >> s;

    bool valid = true;

    for(int i = 0; i < n; i++)
        if(s[i] != '4' && s[i] != '7')
            valid = false;

    int sum1 = 0, sum2 = 0;

    for(int i = 0; i < n / 2; i++)
        sum1 += (s[i] - '0');

    for(int i = n / 2; i < n; i++)
        sum2 += (s[i] - '0');

    if(sum1 != sum2)
        valid = false;

    cout << (valid ? "YES" : "NO") << '\n';

    return 0;
}