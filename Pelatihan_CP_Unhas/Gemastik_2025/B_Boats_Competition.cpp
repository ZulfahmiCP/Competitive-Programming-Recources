#include <bits/stdc++.h>
using namespace std;

int main() {

    int t; cin >> t;

    while(t--){
        int n; cin >> n;
        vector<int> cnt(n + 1, 0);

        for(int i = 0; i < n; i++){
            int x; cin >> x;
            cnt[x]++;
        }

        int ans = 0;

        for(int s = 2; s <= 2 * n; s++){
            int banyak = 0;

            for(int i = 1, j; i <= (s / 2); i++){
                j = s - i;

                if(j > n) continue;

                if(i == j) 
                    banyak += cnt[i] / 2;
                else
                    banyak += min(cnt[i], cnt[j]); 
            }

            ans = max(ans, banyak);
        }
        
        cout << ans << '\n';
    }

    return 0;
}