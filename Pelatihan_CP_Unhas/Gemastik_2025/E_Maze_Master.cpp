#include <bits/stdc++.h>
using namespace std;

int main() {

    int n,m; cin >> n >> m;
    vector<string> S(n);
    
    vector<pair<int, int>> dir = {
        {-1, 0}, // (x, y) -> (x - 1, y) -> atas
        {1, 0},  // (x, y) -> (x + 1, y) -> bawah 
        {0, -1}, // (x, y) -> (x, y - 1) -> kiri 
        {0, 1},  // (x, y) -> (x, y + 1) -> kanan
    };

    for(auto &s : S) 
        cin >> s;

    int ans = 0;

    for(int r = 0; r < n; r++){
        for(int c = 0; c < m; c++){
            // titik awal = (r, c)
            // kalau (r, c) = # skip
            if(S[r][c] == '#') continue;
            
            // dist[i][j] = jarak terpendek dari (r, c) ke (i, j)
            // dist[i][j] = -1 artinya (i, j) belum dikunjungi
            vector<vector<int>> dist(n, vector<int>(m, -1));

            queue<pair<int, int>> bfs;
            bfs.push({r, c});
            dist[r][c] = 0;

            // selama masih ada titik yang mau diproses
            while(!bfs.empty()){
                auto [i, j] = bfs.front();
                bfs.pop();

                for(auto [id, jd] : dir){
                    id += i, jd += j;
                    // coba semua atas, bawah, kiri, kanan dari (i, j)

                    // barisnya di luar jangkauan, skip
                    if(id < 0 || id >= n) continue;

                    // kolomnya di luar jangkauan, skip
                    if(jd < 0 || jd >= m) continue; 

                    // (id, jd) = #, skip
                    if(S[id][jd] == '#') continue;

                    // (id, jd) sudah dikunjungi
                    if(dist[id][jd] != -1) continue;
                    
                    // jarak bertambah 1
                    dist[id][jd] = dist[i][j] + 1;

                    // masukkan lagi buat diproses
                    bfs.push({id, jd});
                }
            }

            for(int i = 0; i < n; i++)
                for(int j = 0; j < m; j++)
                    ans = max(ans, dist[i][j]);
        }
    }

    cout << ans << '\n';

    return 0;
}