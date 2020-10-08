
#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;






int main(){ 
    long long int n, m, k, c, i, j, value;
    cin >> n >> m >> k >> c;   

    vector<long long int> a_line;
    a_line.assign(m, 0);

    vector< vector<long long int> > farm;
    farm.assign(n, a_line);  

    for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            cin >> value;
            farm[i][j] = value;
        }
    }





    return 0;
}