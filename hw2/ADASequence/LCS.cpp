#include<bits/stdc++.h>
using namespace std;


int s1[20];
int s2[20];
int subLCS[20][20];
int status[20][20];
int lcs[20];


void solu(int n, int m){
    int i, j, l, lcs_count = 0;

    for (i = 1; i <= n; i++){
        for (j = 1; j <= m; j++){
            if (s1[i] == s2[j]){
                subLCS[i][j] = subLCS[i-1][j-1] + 1;
                status[i][j] = 0;
            }
            else{
                if (subLCS[i-1][j] < subLCS[i][j-1]){
                    subLCS[i][j] = subLCS[i][j-1];
                    status[i][j] = 1;
                }
                else{
                    subLCS[i][j] = subLCS[i-1][j];
                    status[i][j] = 2;
                }
            }
        }
    }

    
    //backtracking
    i = n; j = m;
    l = subLCS[i][j];
    while (l > 0){
        if (i == 0 || j == 0) break;
        
        if (status[i][j] == 0){
            lcs[l] = s1[i];
            lcs_count++;
            i--;
            j--;
            l--;
        }
        else if (status[i][j] == 1){
            j--;
        }
        else if (status[i][j] == 2){
            i--;
        }
    }

    for (i = 1; i <= lcs_count; i++){
        cout << lcs[i] << " ";
    }
    cout << endl;


}


int main(){ 
    
    int n, m, i, value; 
    
    cin >> n;          
    for (i = 1; i <= n; i++){
            cin >> value;
            s1[i] = value;
            
            
    }
    
    cin >> m;          
    for (i = 1; i <= m; i++){
            cin >> value;
            s2[i] = value;
           
            
    }

    for (i = 0; i <= n; i++) subLCS[i][0] = 0;
    for (i = 0; i <= m; i++) subLCS[0][i] = 0;        

    

    solu(n ,m);
    
    

    return 0; 
    }
