#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;
    string s; cin >> s;
    int eight = 0;

    for(int i = 0; i < n; i++)
        if(s[i] == '8')
            eight++;
    
    cout << min(eight, n / 11) << '\n';

    return 0;
}