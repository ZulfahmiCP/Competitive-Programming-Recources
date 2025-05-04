#include <bits/stdc++.h>
using namespace std;

int main() {

    int t; cin >> t;

    while(t--){
        vector<vector<int>> value = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
            {1, 2, 3, 3, 3, 3, 3, 3, 2, 1},
            {1, 2, 3, 4, 4, 4, 4, 3, 2, 1},
            {1, 2, 3, 4, 5, 5, 4, 3, 2, 1},
            {1, 2, 3, 4, 5, 5, 4, 3, 2, 1},
            {1, 2, 3, 4, 4, 4, 4, 3, 2, 1},
            {1, 2, 3, 3, 3, 3, 3, 3, 2, 1},
            {1, 2, 2, 2, 2, 2, 2, 2, 2, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
        };

        vector<string> S(10);

        for(int i = 0; i < 10; i++)
            cin >> S[i];

        int point = 0;

        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++)
                if(S[i][j] == 'X')
                    point += value[i][j];
        
        cout << point << '\n';
    }

    return 0;
}