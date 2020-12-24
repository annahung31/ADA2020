//Reference: https://www.geeksforgeeks.org/exact-cover-problem-algorithm-x-set-1/
//https://www.geeksforgeeks.org/exact-cover-problem-algorithm-x-set-2-implementation-dlx/?ref=rp
//https://www.cnblogs.com/grenet/p/3163550.html


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

int moves[BOARDWIDTH*BOARDWIDTH*RANGE+1][3];
int ans_board[BOARDWIDTH][BOARDWIDTH];




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
                                   
    vector<int> dlxID{id_a+1, id_b+1, id_c+1, id_d+1};  // +1 because DLX set start from 1


    return dlxID;

}


void savefile(){
    // write output into file
    fstream outfile;

    outfile.open("out.txt", ios::out);

    for (int i = 0; i < BOARDWIDTH; i++){
        for (int j = 0; j < BOARDWIDTH; j++){
            outfile << ans_board[i][j];
        }
        outfile << "\n";
    }

}


void print_board(vector<int> ans){
    
    for (int i=0; i < ans.size(); i++){
        ans_board[moves[ans[i]][0]][moves[ans[i]][1]] = moves[ans[i]][2];
    }

    for (int i = 0; i < BOARDWIDTH; i++){
        for (int j = 0; j < BOARDWIDTH; j++){
            cout << ans_board[i][j];
        }
        cout << "\n";
    }
    
    savefile();

}



int main(){

    /*
    Example: 4x4 board, number range = 4, empty in the beginning
    */

    // build sparse matrix
    int sz, set_id;
    sz = A_RANGE + B_RANGE + C_RANGE + D_RANGE;
    Init(sz);
    vector<int> dlxID;
    
    set_id = 0;
    for (int i =0; i < BOARDWIDTH; i++){
        for (int j =0; j < BOARDWIDTH; j++){
            for (int k=1; k <= RANGE; k++){
                dlxID = cal_id(i,j,k);
                moves[set_id][0] = i;
                moves[set_id][1] = j;
                moves[set_id][2] = k;
                AddRow(set_id, dlxID);
                set_id++;
            }

        }
    }

    vector<int> ans;
    ans = Solver();
    print_board(ans);




    return 0;
}
