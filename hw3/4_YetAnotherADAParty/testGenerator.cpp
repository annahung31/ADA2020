
#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;



int main(){

    srand( time(NULL) );
    fstream tfile;
    int x = rand() %(100 - 1+1)+1;
    string fileName = "g1_test_" + to_string(x)+ ".txt";
    tfile.open(fileName, ios::out);

    int n, m, k, c, i, j;
    int kMAX = 10;
    long long int MAX = 1e8;
    long long int MIN = (-1) *1e8;

    
    c = rand() % (MAX - MIN + 1) + MIN;
    k = rand() % (kMAX - 1 + 1) + 1;
    cin >> n >> m;
    tfile << n << " " << m << " " << k << " " << c << "\n";
    


    for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            long long int x = rand() % (MAX - MIN + 1) + MIN;
            tfile << x << " ";
        }
        tfile << "\n";
    }

    return 0;

}