#include <bits/stdc++.h>
using namespace std;

int main() {

    int t, n, k; cin >> t;
    string s; 

    while(t--){
        cin >> n >> k >> s;
        vector<int> cnt(26, 0);

        for(int i = 0; i < n; i++)
            cnt[s[i] - 'a']++;

        int odd = 0;

        for(int i = 0; i < 26; i++)
            if(cnt[i] % 2 == 1)
                odd++;

        odd = max(0, odd - 1); // maksimal 1 karakter munculnya ganjil

        cout << (odd <= k ? "YES" : "NO") << '\n';
    }

    return 0;
}