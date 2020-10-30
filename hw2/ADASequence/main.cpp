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

    if (i == j) return 1;
    if (i > j) return 0;
    if (i + 1 == j && a[i] == a[j]) return 2;

    if (subLPS[i][j] != -1) return subLPS[i][j];

    if (a[i] == a[j]){
        
        subLPS[i][j] = solu(i+1, j-1) + 2;
        status[i][j] = 0;
    }
    else{
        if (solu(i+1, j) >= solu(i, j-1)){
            subLPS[i][j] = solu(i+1, j);
            status[i][j] = 1;
        }
        else{
            subLPS[i][j] = solu(i, j-1);
            status[i][j] = 2;
        }
    }
}

void backTrace(long long int i, long long int j){

    if (i > j) return;
    if (i == j){
        // cout << i+1 << " ";  //middle
        lps.push_back(i);
        score += s[i];
    } 
        
    else if (status[i][j] == 0){
        // cout << i+1 << " ";
        lps.push_back(i);
        score += s[i];

        backTrace(i+1, j-1);

        // cout << j+1 << " ";
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
    
    long long int n, k, D, i, j, value; 
    score = 0;
    cin >> n >> k >> D;     

    for (i = 0; i <= n; i++){
            cin >> value;
            a[i] = value;           
    }

    for (i = 0; i <= n; i++){
            cin >> value;
            c[i] = value;           
    }

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

    cout << score << endl;
    cout << 0 << endl;
    cout << lps.size() << endl;
    for (i = 0; i < lps.size(); i++){
        cout << lps[i]+1 << " ";
    }

    return 0; 
    }

