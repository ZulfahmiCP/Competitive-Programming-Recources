#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n; cin >> t;
    while(t--){
        cin >> n;
        int a = 0, b = 0, ans = 0;

        for(int i = 0; i < n; i++){
            int x; cin >> x;
            if(x == 1)
                a++;
            else 
                b++;
        }

        while(a - b < 0 || b % 2 == 1){
            ans++;
            a++;
            b--;
        }

        cout << ans << '\n';
    }

    return 0;
}