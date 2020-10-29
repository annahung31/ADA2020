
#include<bits/stdc++.h>

using namespace std;


long long int cell[1002];
long long int dp[28][1002];

void solu(long long int n, long long int k, long long int A, long long int B, long long int& defense_level){
    long long int kk, i, j, temp, temp_j, zero = 0;

    for (kk = 0; kk <= k; kk++){
        for (i = 0; i <= n; i++){
            dp[kk][i] = 0;
        }
    }

    for (i = 1; i <= n; i++){
        dp[1][i] = cell[i];
        defense_level = max(defense_level, dp[1][i]);
    }

    for (kk = 2; kk <= k; kk++){
        for (i = kk; i <= n; i++){
            dp[kk][i] = cell[i];
            temp = -1e10;
            for (j = kk-1; j < i; j++){

                temp = max(temp, dp[kk-1][j] + cell[i] + A * max({zero, B - (i - j)}));
            }

            dp[kk][i] = temp;
            defense_level = max(defense_level, dp[kk][i]);
        }
    }

}



int main(){ 
    

    long long int n, k, A, B, i, value, defense_level=0; 
    
    cin >> n >> k >> A >> B;          

    cell[0] = 0;
    for (i=1; i<=n; i++){
            cin >> value;
            cell[i] = value;
            
    }
    
    


    solu(n, k, A, B, defense_level);
    cout << defense_level << "\n";

    return 0; 
    }
