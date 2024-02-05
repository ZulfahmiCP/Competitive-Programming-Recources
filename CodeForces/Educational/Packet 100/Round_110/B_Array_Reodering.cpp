#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void FastIO();
int gcd(int a, int b);
int main() {
    
    FastIO();
    int t,n,x,e; cin >> t;
    long long s;
    vector<int> odd;
    while(t--){
        cin >> n; e = 0;
        for(int i = 0; i < n; i++){
            cin >> x;
            if(x & 1) odd.push_back(x);
            else e++;
        } s = (n*(n - 1) - (n - e)*(n - e - 1))/2;
        for(int i = 0; i < n - e; i++){
            for(int j = i+1; j < n - e; j++){
                if(gcd(odd[i], odd[j]) > 1) s++;
            }
        } cout << s << '\n';
        odd.clear();
    }
    
	return 0;
}
void FastIO(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
int gcd(int a, int b){
    if(!b) return a;
    return gcd(b,a % b);
}