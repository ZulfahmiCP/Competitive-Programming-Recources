#include <bits/stdc++.h>
using namespace std;

int main() {

    int t,n; cin >> t;
    while(t--){
        cin >> n;
        int sum = 0;

        for(int i = 0; i < n; i++){
            int x; cin >> x;
            sum += x;
        }

        cout << ((sum % 2 == 0) ? "YES" : "NO") << '\n';
    }

    return 0;
}