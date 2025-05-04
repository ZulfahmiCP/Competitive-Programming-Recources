#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n; cin >> t;
    while(t--){
        cin >> n;
        
        int ans = n / 4;
        if(n % 4 == 2)
            ans++;
        cout << ans << '\n';
    }

    return 0;
}