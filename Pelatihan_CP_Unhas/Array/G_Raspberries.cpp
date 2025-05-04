#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n, k; cin >> t;

    while(t--){
        cin >> n >> k;
        vector<int> A(n);

        for(int i = 0; i < n; i++)
            cin >> A[i];

        int ans = k;

        for(int i = 0; i < n; i++){
            if(A[i] % k == 0)
                ans = 0;
            else 
                ans = min(ans, k - (A[i] % k));
        }

        if(k == 4){
            int even = 0;
            for(int i = 0; i < n; i++)
                if(A[i] % 2 == 0)
                    even++;

            if(even == 0)
                ans = min(ans, 2);
            else if(even == 1)
                ans = min(ans, 1);
            else 
                ans = 0;
        }

        cout << ans << '\n';
    }

    return 0;
}