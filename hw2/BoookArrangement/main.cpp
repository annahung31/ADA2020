
#include<bits/stdc++.h>

using namespace std;

long long int books[100001];
long long int tempbooks[100001];


void solu(long long int i, long long int j, long long int& ed, long long int& insertNum, vector< vector<long long int>>& output){
    // cout << "check i:" << i << "," << books[i] << ", j:" << j << "," << books[j] << "\n";
    if (i < ed && j < ed){
        return;
    }
    if(i == ed && j == ed-1){
        output.push_back({i, -1, 1});
        books[i]--;
        insertNum += books[i];
        output.push_back({i+1, i, books[i]});
        books[i] = 0;
        return;
    }


    if (books[i] > books[j]){
        output.push_back({i, j, books[j]});
        books[i] = books[i] - books[j];
        books[j] = 0;

        if (i == ed+1){
            insertNum = insertNum + books[i] -1;
            output.push_back({i, j, books[i]-1});
            output.push_back({i, -1, 1});
            books[i] = 0;
        }
        else{
            insertNum += books[i];
            output.push_back({i, j, books[i]});
            books[i] = 0;
        }

        solu(j-1, j-2, ed, insertNum, output);
    }
    else{
        if (books[i] != 0){
            output.push_back({i, -1, 1});
            //cout << i << endl;
            books[i]--;
            output.push_back({j, i, books[i]});
            books[j] = books[j] - books[i];
            books[i] = 0;

        }
        else{
            insertNum++;
            output.push_back({i, -1, 1});
            
        }
        solu(j, j-1, ed, insertNum, output);

    }


}  


void printSeq(vector< vector<long long int>>& output){
    long long int i, j;
    for (i = 0; i < output.size(); i++){
        if (output[i][1] == -1){
            cout << output[i][0] << " ";
        }
        else{
            for (j = 0; j < output[i][2]; j++){
                cout << output[i][0] << " ";
                cout << output[i][1] << " ";
            }
        }
        
    }
    cout << "\n";
}


int main(){ 
    
    long long int n, flag, i, value, ed, st, insertNum = 0, InsertNumA = 0; 
    vector< vector<long long int>> outputA;
    vector< vector<long long int>> outputB;
    cin >> n;          


    for (i = 1; i <= n; i++){
            cin >> value;
            books[i] = value;
            tempbooks[i] = value;
    }
    
    cin >> flag;


    //remove front zeros and back zeros
    for (i = 1; i <= n; i++){
        ed = i;
        if (books[i] != 0) break;
    }

    for (i = n; i >= 1; i--){
        st = i;
        if (books[i] != 0) break;
    }
  
    if (st == ed){
        cout << books[st] - 1 << endl;
        if (flag == 1){

            outputA.push_back({st, -1, 1});
            
            if (st == 1){
                outputA.push_back({st+1, st, books[st] - 1});
            }
            else {
                outputA.push_back({st-1, st, books[st] - 1});
            }

            
            printSeq(outputA);
        }

        return 0;
    }
    else{

        solu(st, st-1, ed, insertNum, outputA);

        InsertNumA = insertNum;
        insertNum = 0;

        for (i = 1; i <= n; i++){
                books[i] = tempbooks[i];
        }



        //case 2
        if (books[st-1] != 0){
            books[st-1]--;
            outputB.push_back({st-1, -1, 1});
            solu(st, st-1, ed, insertNum, outputB);
        }
        else{
            // solu(st, st-1, ed, insertNum, outputB);
            insertNum = InsertNumA;

        }



        if (InsertNumA > insertNum){
            cout << insertNum << "\n";
            if (flag == 1){
                printSeq(outputB);
            }
        }
        else{
            cout << InsertNumA << "\n";
            if (flag == 1){
                printSeq(outputA);
            }
        }


        return 0; 

    }
    }

