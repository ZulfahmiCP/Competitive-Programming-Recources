#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n; cin >> t;
    string s;

    while(t--){
        cin >> s;
        n = s.size();
        reverse(s.begin(), s.end());

        int ans = n;
        vector<string> possible = {"00", "25", "50", "75"};

        for(int i = 0; i < 4; i++){
            string p = possible[i];
            int k = 1, j = 0;

            for(; j < n; j++){
                if(k == -1)
                    break;
                if(s[j] == p[k])
                    k--;
            }

            if(k == -1)
                ans = min(ans, j - 2);
        }

        cout << ans << '\n';
    }

    return 0;
}