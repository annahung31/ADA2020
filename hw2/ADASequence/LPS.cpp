#include<bits/stdc++.h>
using namespace std;

int s[20];
int subLPS[20][20];
int status[20][20];
int lps[20];

int solu(int i, int j){

    if (i == j) return 1;
    if (i > j) return 0;
    if (i + 1 == j && s[i] == s[j]) return 2;

    if (subLPS[i][j] != -1) return subLPS[i][j];

    if (s[i] == s[j]){
        
        subLPS[i][j] = solu(i+1, j-1) + 2;
        status[i][j] = 0;
    }
    else{
        if (solu(i+1, j) > solu(i, j-1)){
            subLPS[i][j] = solu(i+1, j);
            status[i][j] = 1;
        }
        else{
            subLPS[i][j] = solu(i, j-1);
            status[i][j] = 2;
        }
    }
}

void backTrace(int i, int j){

    if (i > j) return;
    if (i == j) cout << s[i];  //middle
        
    else if (status[i][j] == 0){
        cout << s[i];
        backTrace(i+1, j-1);
        cout << s[j];
    }

    else if (status[i][j] == 1){
        backTrace(i+1, j);
    }
    else {
        backTrace(i, j-1);
    }
}

int main(){ 
    
    int n, i, j, value; 
    
    cin >> n;          
    for (i = 0; i <= n; i++){
            cin >> value;
            s[i] = value;           
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            subLPS[i][j] = -1;
        }
    }       

    solu(0, n-1);
    backTrace(0, n-1);
    cout << "\n length: " <<  subLPS[0][n-1] << endl;
    return 0; 
    }
