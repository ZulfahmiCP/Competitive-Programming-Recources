#include <bits/stdc++.h>
using namespace std;

int main() {

    int n; cin >> n;
    vector<int> cnt(5, 0);

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        cnt[x]++;
    }

    // semua grup berisi 4 orang
    int ans = cnt[4];

    // 2 grup yang berisi 2 orang
    ans += cnt[2] / 2;
    // jika tersisa 1 grup 2 orang 
    // akan digabungkan dengan 2 grup berisi 1 orang
    cnt[2] %= 2;

    // ambil grup 3 orang dan grup 1 orang
    int x = min(cnt[3], cnt[1]);
    ans += x;
    // kurangi jumlahnya
    cnt[3] -= x;
    cnt[1] -= x;

    // grup 3 orang tidak bisa digabungkan 
    // dengan grup manapun lagi, ambil semua
    ans += cnt[3];

    // sisa dari 1 grup 2 orang akan digabungkan 
    // dengan grup 1 orang
    if(cnt[2] > 0){
        ans++;
        // ambil 2 grup berisi 1 orang, untuk mengatasi
        // jika jumlah grup 1 orang kurang dari 2
        // cukup dengan max(0, cnt[1] - 2)
        cnt[1] = max(0, cnt[1] - 2);
        cnt[2]--;
    } 

    // 4 grup 1 orang dijadikan satu
    ans += ceil(cnt[1] / 4.0);

    cout << ans << '\n';

    return 0;
}