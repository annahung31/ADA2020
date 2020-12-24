//Reference: https://www.geeksforgeeks.org/exact-cover-problem-algorithm-x-set-1/
//https://www.geeksforgeeks.org/exact-cover-problem-algorithm-x-set-2-implementation-dlx/?ref=rp

#include <bits/stdc++.h> 
#include "helper.h"
using namespace std; 
using namespace DLX;

#define BOARDWIDTH 4
#define BLOCKWIDTH 2
#define RANGE 4
#define NUMBLOCK 4
#define A_RANGE BOARDWIDTH * BOARDWIDTH
#define B_RANGE BOARDWIDTH * RANGE
#define C_RANGE BOARDWIDTH * RANGE
#define D_RANGE NUMBLOCK * RANGE


int block(int i, int j){
    return int(i / BLOCKWIDTH) * BLOCKWIDTH + int(j / BLOCKWIDTH);
}


vector<int> cal_id(int i, int j, int num){
    int id_a, id_b, id_c, id_d;
    id_a = BOARDWIDTH * (i) + j;
    id_b = A_RANGE + BOARDWIDTH * (i) + num - 1;
    id_c = A_RANGE + B_RANGE + BOARDWIDTH * (j) + num - 1;
    id_d = A_RANGE + B_RANGE + C_RANGE + 
            (block(i, j)) * BLOCKWIDTH * BLOCKWIDTH + num - 1;
                                   
    vector<int> dlxID{id_a, id_b, id_c, id_d};

    // for (int i=0; i < dlxID.size(); i++){
    //     cout << dlxID[i] << " ";
    // }
    // cout << "\n";

    return dlxID;

}





int main(){

    /*
    Example: 4x4 board, number range = 4, empty in the beginning
    Start by fill in 1,2,3,4 in the first row
    */


    // build sparse matrix
    int sz, column, row, num;
    sz = A_RANGE + B_RANGE + C_RANGE + D_RANGE;
    Init(sz);

    // fill in 1 in (0,0)
    // row = 0; column = 0; num = 1;
    vector<int> dlxID;
    dlxID = cal_id(0,0,1);
    AddRow(0, dlxID);
    dlxID = cal_id(0,1,2);
    AddRow(1, dlxID);
    dlxID = cal_id(0,2,3);
    AddRow(2, dlxID);
    dlxID = cal_id(0,3,4);
    AddRow(3, dlxID);



    vector<int> ans;
    ans = Solver();
    for (int i=0; i < ans.size(); i++){
        cout << ans[i]+1 << " ";
    }





    // // write output into file
    // fstream outfile;
    // outfile.open("out.txt", ios::out);

    // outfile << 215647398 << "\n";
    // outfile << 368952174 << "\n";
    // outfile << 794381652 << "\n";
    // outfile << 586274931 << "\n";
    // outfile << 142593867 << "\n";
    // outfile << 973816425 << "\n";
    // outfile << 821739546 << "\n";
    // outfile << 659428713 << "\n";
    // outfile << 437165289 << "\n";
    


    return 0;
}