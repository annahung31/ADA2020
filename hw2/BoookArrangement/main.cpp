
#include<bits/stdc++.h>

using namespace std;

int books[100001];

vector<int> output;


void solu(int i, int j, int& insertNum){
    cout << "cp: " << i << "," << j << endl;
    if (books[i] == 0){
        solu(j, j-1, insertNum);
    }
    if (books[j] == 0 && j > 0){
        while (books[i] != 0){
            output.push_back(i);
            cout << i << endl;
            books[i]--;
            output.push_back(j);
            cout << j << endl;
            insertNum++;
        }
        solu(j-1, j-2, insertNum);
    }
    if (i == 0 && j < 0){
        return;
    }
    if(i == 1 && j == 0){
        output.push_back(i);
        books[i]--;
        while (books[i] != 0){
            output.push_back(i+1);
            cout << i + 1 << endl;
            insertNum++;
            output.push_back(i);
            cout << i << endl;
            books[i]--;
        }
        return;
    }
    
    if (books[i] > books[j]){
        while (books[j] != 0){
            output.push_back(i);
            cout << i << endl;
            books[i]--;
            output.push_back(j);
            cout << j << endl;
            books[j]--;
        }
        while (books[i] != 0){
            output.push_back(i);
            cout << i << endl;
            books[i]--;
            output.push_back(j);
            cout << j << endl;
            insertNum++;
        }
        solu(j-1, j-2, insertNum);
    }
    else{
        output.push_back(i);
        cout << i << endl;
        books[i]--;
        while (books[i] != 0){
            output.push_back(j);
            cout << j << endl;
            books[j]--;
            output.push_back(i);
            cout << j << endl;
            books[i]--;
        }
        solu(j, j-1, insertNum);
    }


}  



int main(){ 
    
    int n, flag, i, value, insertNum = 0; 
    
    cin >> n;          


    for (i = 1; i <= n; i++){
            cin >> value;
            books[i] = value;
    }
    
    cin >> flag;


    solu(n, n-1, insertNum);

    // books[n-1]--;
    // output.push_back(n-1);
    // solu(n, n-1, insertNum);



    cout << insertNum << "\n";
    if (flag == 1){
        for (i = 0; i < output.size(); i++){
            cout << output[i] << " ";
        }
        cout << "\n";
    }

    return 0; 
    }
