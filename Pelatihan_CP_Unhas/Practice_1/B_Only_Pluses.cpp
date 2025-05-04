#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, a, b, c; cin >> t;
    
    while(t--){
        cin >> a >> b >> c;

        int ans = 0;

        for(int i = 0; i <= 5; i++) 
            for(int j = 0; j <= 5; j++)
                for(int k = 0; k <= 5; k++)
                    if(i + j + k == 5)
                        ans = max(ans, (a + i) * (b + j) * (c + k));
        
        cout << ans << '\n';
    }

    return 0;
}