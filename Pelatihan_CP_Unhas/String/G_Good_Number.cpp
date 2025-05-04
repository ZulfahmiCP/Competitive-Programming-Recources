#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, k; cin >> t >> k;
    string s;

    int ans = 0;

    while(t--){
        cin >> s;
        int n = s.size();
        vector<int> cnt(k + 1, 0);

        bool valid = true;

        for(int i = 0; i < n; i++){
            int digit = s[i] - '0';

            if(digit <= k)
                cnt[digit]++;
        }

        for(int i = 0; i <= k; i++)
            if(cnt[i] == 0)
                valid = false;

        if(valid)
            ans++;
    }    

    cout << ans << '\n';

    return 0;
}