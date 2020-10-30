
#include<bits/stdc++.h>

using namespace std;


long long int cell[100002];
long long int dp[2][100002];
long long int M1[100002];
long long int M2[100002];

void solu(long long int n, long long int k, long long int A, long long int B, long long int& defense_level){
    long long int kk, i, j, temp, temp1, temp2;


    for (kk = 0; kk < 2; kk++){
        for (i = 0; i <= n; i++){
            dp[kk][i] = 0;
        }
    }


    M1[0] = 0; M2[i] = 0;
    for (i = 1; i <= n; i++){
        dp[0][i] = cell[i];
        defense_level = max(defense_level, cell[i]);
        M1[i] = max(M1[i-1], cell[i]);
        M2[i] = max(M2[i-1], cell[i]);
    }

    for (kk = 2; kk <= k; kk++){
        for (i = kk; i <= n; i++){
            if (i == kk){
                M1[i-1] = dp[0][i-1];
                M2[i-1] = dp[0][i-1] + A * (i - 1);
            }

            dp[1][i] = cell[i];
            // get M[k][i]
            temp1 = M1[i-1] + cell[i]; 
            temp2 = M2[i-1] + A * B - A * i + cell[i];
            if (temp1 >= temp2){
                dp[1][i] = temp1;
                temp = temp1;
            }
            else{
                dp[1][i] = temp2;
                temp = temp2;
            }

            M1[i] = max(M1[i-1], dp[0][i]);
            M2[i] = max(M2[i-1], dp[0][i] + A * i);

            defense_level = max(defense_level, temp);
        }
        // put dp[1] to dp[0]
        for (i = 0; i <= n; i++){
            dp[0][i] = dp[1][i];
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
