#include<bits/stdc++.h>
using namespace std;
#include <algorithm>
long long int a[201];
long long int c[201];
long long int s[201];
long long int subLPS[201][201][601];
long long int status[201][201][601];
vector<long long int> lps;
long long int changePair[1001][2];
long long int score;
long long int op;



long long int solu(long long int i, long long int j, long long int m, long long int& k, long long int& D){
   long long int changeOp, equFree, subLeft, subRight;
    if (m < 0) return 3e11;
    if (i == j && m == s[i]){
        if (subLPS[i][j][m] <= k && m > score){
            score = m;
        }
        return 0;
    } 
    if (i == j && m != s[i]) return 3e11;
    if (i > j && m == 0) return 0;
    if (i > j && m != 0) return 3e11;

    if (subLPS[i][j][m] != -1) return subLPS[i][j][m];

    subLeft = solu(i+1, j, m, k, D);
    subRight = solu(i, j-1, m, k, D);

    if (abs(a[i] - a[j]) <= D){
        equFree = solu(i+1, j-1, m-s[i]-s[j], k, D);

        subLPS[i][j][m] = min({equFree, subLeft, subRight});

        if (subLPS[i][j][m] == equFree) status[i][j][m] = 0;
        else if (subLPS[i][j][m] == subLeft) status[i][j][m] = 1;
        else status[i][j][m] = 2;
        
        if (subLPS[i][j][m] <= k && m > score){
            score = m;
        }
        return subLPS[i][j][m];
    }
    else{
        if (k > 0) changeOp = solu(i+1, j-1, m-s[i]-s[j], k, D)+ min({c[i], c[j]});
        else changeOp = 3e11;
        
        subLPS[i][j][m] = min({changeOp, subLeft, subRight});

        if (subLPS[i][j][m] == changeOp) status[i][j][m] = 3;
        else if (subLPS[i][j][m] == subLeft) status[i][j][m] = 1;
        else status[i][j][m] = 2;


        if (subLPS[i][j][m] <= k && m > score){
            score = m;
        }
        return subLPS[i][j][m];
    }
    

}

void backTrace(long long int i, long long int j, long long int m){

    if (i > j) return;
    if (i == j){
        lps.push_back(i);
        
    } 
        
    else if (status[i][j][m] == 0){
        lps.push_back(i);
        backTrace(i+1, j-1, m - s[i] - s[j]);
        lps.push_back(j);
    }

    else if (status[i][j][m] == 1) backTrace(i+1, j, m);
    else if (status[i][j][m] == 2) backTrace(i, j-1, m);
    else {
        op += 1;
        if (c[i] > c[j]){
            changePair[op][0] = j;
            changePair[op][1] = a[i];
        }
        else{
            changePair[op][0] = i;
            changePair[op][1] = a[j];            
        }
        lps.push_back(i);
        backTrace(i+1, j-1, m - s[i] - s[j]);
        lps.push_back(j);

    }
}



int main(){ 
    
    long long int n, k, D, i, j, t, m, value, sumS; 
    score = 0;
    sumS = 0;
    cin >> n >> k >> D;     

    for (i = 0; i < n; i++){
            cin >> value;
            a[i] = value;           
    }

    for (j = 0; j < n; j++){
            cin >> value;
            c[j] = value;           
    }

    for (t = 0; t < n; t++){
            cin >> value;
            s[t] = value;         
            sumS += value;  
    }


    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            for (t = 0; t <= sumS; t++){
                subLPS[i][j][t] = -1;
            }
            
        }
    }       

    //loop m 
    for (m = sumS; m >= 1; m--){
        solu(0, n-1, m, k, D);
    }
    
    backTrace(0, n-1, score);
  
    cout << score << endl;
    cout << op << endl;
    

    for (j = 1; j <= op; j++){
        cout << changePair[j][0]+1 << " " << changePair[j][1] << "\n";
    }

    cout << lps.size() << endl;
    for (i = 0; i < lps.size(); i++){
        cout << lps[i]+1 << " ";
    }

    return 0; 
    }

