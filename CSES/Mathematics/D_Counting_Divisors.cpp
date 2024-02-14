#include <iostream>
using namespace std;
int main(){
 
    int t; cin >> t;
    while(t--){
        int n, hsil = 0; cin >> n;
        for(int i = 1; i*i <= n; i++){
            if(n % i == 0 && i*i != n){
                hsil+=2;
            } else if(i*i == n){
                hsil++;
            }
        } cout << hsil << '\n';
    }
 
    return 0;
}
