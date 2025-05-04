#include <bits/stdc++.h>
using namespace std;

int main() {

    int t; cin >> t;
    string s, yes = "yes", YES = "YES";

    while(t--){
        cin >> s;
        bool valid = true;

        for(int i = 0; i < 3; i++)
            if(s[i] != yes[i] && s[i] != YES[i])
                valid = false;
        
        cout << (valid ? "YES" : "NO") << '\n';
    }

    return 0;
}