#include<bits/stdc++.h>
using namespace std;

long long int a[201];
long long int c[201];
long long int s[201];
long long int subLPS[201][201];
long long int status[201][201];
vector<long long int> lps;
long long int score;

long long int solu(long long int i, long long int j){
    long long int tempMax;
    if (i == j) return s[i];
    if (i > j) return 0;

    if (subLPS[i][j] != -1) return subLPS[i][j];

    if (a[i] == a[j] && solu(i+1, j-1) + s[i] + s[j] > solu(i+1, j) && solu(i+1, j-1) + s[i] + s[j] > solu(i, j-1)){
        subLPS[i][j] = solu(i+1, j-1) + s[i] + s[j];
        status[i][j] = 0;
        return subLPS[i][j];        
        }
    
    else{
        if (solu(i+1, j) > solu(i, j-1)){
            subLPS[i][j] = solu(i+1, j);
            status[i][j] = 1;
            return subLPS[i][j];
        }
        else{
            subLPS[i][j] = solu(i, j-1);
            status[i][j] = 2;
            return subLPS[i][j];
        }
    }
}

void backTrace(long long int i, long long int j){

    if (i > j) return;
    if (i == j){
        lps.push_back(i);
        score += s[i];
    } 
        
    else if (status[i][j] == 0){
        lps.push_back(i);
        score += s[i];

        backTrace(i+1, j-1);

        lps.push_back(j);
        score += s[j];
    }

    else if (status[i][j] == 1){
        backTrace(i+1, j);
    }
    else {
        backTrace(i, j-1);
    }
}

int main(){ 
    
    long long int n, k, D, i, j, t, value; 
    score = 0;
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
    }


    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            subLPS[i][j] = -1;
        }
    }       

    


    solu(0, n-1);
    
    backTrace(0, n-1);

    cout << score << endl;
    cout << 0 << endl;
    cout << lps.size() << endl;
    for (i = 0; i < lps.size(); i++){
        cout << lps[i]+1 << " ";
    }

    return 0; 
    }

