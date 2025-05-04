#include <bits/stdc++.h>
using namespace std;

int main() {

    string s; cin >> s;
    int n = s.size();

    bool valid = false;

    for(int i = 0; i + 7 <= n; i++)
        if(s.substr(i, 7) == "0000000" || s.substr(i, 7) == "1111111")
            valid = true;

    cout << (valid ? "YES" : "NO") << '\n';

    return 0;
}