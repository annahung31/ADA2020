//Reference: https://www.geeksforgeeks.org/exact-cover-problem-algorithm-x-set-1/
//https://www.geeksforgeeks.org/exact-cover-problem-algorithm-x-set-2-implementation-dlx/?ref=rp
//https://www.cnblogs.com/grenet/p/3163550.html


#include <bits/stdc++.h> 
#include "helper.h"
using namespace std; 
using namespace DLX;

#define BOARDWIDTH 9
#define BLOCKWIDTH 3
#define RANGE 9
#define NUMBLOCK 9
#define A_RANGE BOARDWIDTH * BOARDWIDTH
#define B_RANGE BOARDWIDTH * RANGE
#define C_RANGE BOARDWIDTH * RANGE
#define D_RANGE NUMBLOCK * RANGE


int moves[BOARDWIDTH*BOARDWIDTH*RANGE+1][3];
int ans_board[BOARDWIDTH][BOARDWIDTH];
int color_board[BOARDWIDTH][BOARDWIDTH];
int color_target[127];
int color_no_cells[200];
int color_map[128];

int array[100];



struct cage
{
	int sum = 0, capacity = 0;
	vector<int> cells;
	vector< vector<int>> possible_divisions;
    int possible_num[10];
};
cage Cage[128];


vector< vector<int>> partitions(int target, int curr, int* array, int idx, int& quota, vector< vector<int>> possible_divisions)
{
    bool valid = true;
    vector<int> a_set;
    if (curr + array[idx] == target){
        
        for (int i=0; i <= idx; i++){
            // cout << array[i] << " ";
            if (array[i] > 9){
                valid = false;
                break;
            }
            else{
                a_set.push_back(array[i]);
            }
        }

        if (valid && a_set.size() == quota){
            possible_divisions.push_back(a_set);
        }

        // cout << endl;       
        return possible_divisions;
    }
    else if (curr + array[idx] > target){
        return possible_divisions;
    }
    else{
        for(int i = array[idx]+1; i < target; i++){
            array[idx+1] = i;
            possible_divisions = partitions(target, curr + array[idx], array, idx+1, quota, possible_divisions);
        }
    }
    return possible_divisions;
}


int block(int i, int j){
    return int(i / BLOCKWIDTH) * BLOCKWIDTH + int(j / BLOCKWIDTH);
}

vector<int> cal_id(int i, int j, int num){
    int id_a, id_b, id_c, id_d, color, color_idx, id_cc;
    color = color_board[i][j];
    color_idx = color_map[color] - 1;


    id_a = BOARDWIDTH * (i) + j;
    id_b = A_RANGE + RANGE * (i) + num - 1;
    id_c = A_RANGE + B_RANGE + RANGE * (j) + num - 1;
    id_d = A_RANGE + B_RANGE + C_RANGE + 
             RANGE * (block(i, j)) + num - 1;
    id_cc = A_RANGE + B_RANGE + C_RANGE + D_RANGE + 
            RANGE * (color_idx) + num - 1;
    


    vector<int> dlxID{id_a+1, id_b+1, id_c+1, id_d+1, id_cc+1};  // +1 because DLX set start from 1

    // display for debugging
    // for (int i=0; i < dlxID.size(); i++){
    //     cout << dlxID[i] << " ";
    // }
    // cout << "\n";

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
    // savefile();
}

void build_matrix(){

    int set_id;
    set_id = 0;
    vector<int> dlxID;
    for (int i =0; i < BOARDWIDTH; i++){
        for (int j =0; j < BOARDWIDTH; j++){
            int color = color_board[i][j];
            
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
}


int main(){

    
    // get input
    char cc;
    for (int i = 0; i < BOARDWIDTH; i++){
        for (int j = 0; j < BOARDWIDTH; j++){
            cin >> cc;
            color_board[i][j] = int(cc);
            Cage[int(cc)].cells.push_back(BOARDWIDTH * (i) + j);
            Cage[int(cc)].capacity++;
            
        }
    }

    int target, num_color;
    num_color = 0;
    while (cin >> cc >> target){
        Cage[int(cc)].sum = target;
        color_map[int(cc)] = num_color + 1;   // use num_color as color_id
        num_color++;        
    }

    for (int i = 0; i < 128; i++){
        if (color_map[i] != 0){
            int N = Cage[i].sum;
            int quota = Cage[i].capacity;   

            int array[100];
            vector< vector<int>> cage_possible_divisions;

            for(int j = 1; j < N; j++){
                array[0] = j;
                Cage[i].possible_divisions = partitions(N, 0, array, 0, quota, cage_possible_divisions);
                
                // record possible num
                for (int k = 0; k < Cage[i].possible_divisions.size(); k++){
                    for (int t = 0; t < Cage[i].possible_divisions[k].size(); t++){
                        int num = Cage[i].possible_divisions[k][t];
                        Cage[i].possible_num[num] = 1;
                    }                    
                }
            }
        }
    }



    // build sparse matrix
    int sz;
    sz = A_RANGE + B_RANGE + C_RANGE + D_RANGE + num_color * RANGE;

    Init(sz);      

    build_matrix();

    //display range
    // cout << "| 1 ---" << A_RANGE << " | ";
    // cout << A_RANGE + 1 << " --- " << A_RANGE + B_RANGE << " | ";
    // cout << A_RANGE + B_RANGE + 1 << " --- " << A_RANGE + B_RANGE + C_RANGE << "|";
    // cout << A_RANGE + B_RANGE + C_RANGE + 1 << " --- " << A_RANGE + B_RANGE + C_RANGE + D_RANGE << "|";
    // cout << A_RANGE + B_RANGE + C_RANGE + D_RANGE + 1 << " --- " << A_RANGE + B_RANGE + C_RANGE + D_RANGE + num_color * RANGE << "|";
    // cout << "\n";




    // solve
    vector<int> ans;
    ans = Solver();

    //display result
    print_board(ans);



    // cout << ans.size() << "\n";
    // for (int i=0; i < ans.size(); i++){
    //     cout << ans[i] << " ";
    // }
    // cout << "\n";


    return 0;
}




