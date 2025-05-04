#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n, x; cin >> t;
    
    while(t--){
        cin >> n >> x;
        vector<int> A(n);

        for(int i = 0; i < n; i++)
            cin >> A[i];

        int ans = A[0];

        for(int i = 1; i < n; i++)
            ans = max(ans, A[i] - A[i - 1]);

        ans = max(ans, 2 * (x - A[n - 1]));

        cout << ans << '\n';
    }
    

    return 0;
}