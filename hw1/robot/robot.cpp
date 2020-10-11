
#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;


class MOVE{
    public:
        string moveType;
        int moveI=0;
        int moveJ=0;
};


class RESULT{
    public:
        long long int sweetness=0;
        int nMove=1;
        vector< MOVE> moves;
};


MOVE recordMove(string moveType, int i, int j){
    MOVE move;
    move.moveType=moveType;
    move.moveI=i;
    move.moveJ=j;
    return move;
}


RESULT getSweet(vector< vector<long long int> > farm, int n, int m){
    vector<vector<long long int>> dp(n, vector<long long int>(m, 0));
    RESULT output;
    dp[0][0] = farm[0][0];
    int i, j;
    //init: O(n)
    for (i=1; i<n; i++){
        dp[i][0] = dp[i-1][0] + farm[i][0];
    }

    for (j=1; j<m; j++){
        dp[0][j] = dp[0][j-1] + farm[0][j];
    }

    // O(m*n)
    for (i=1; i<n; i++){
        for (j=1; j<m; j++){
            // cout << i << "," << j << endl;

            if (dp[i-1][j] > dp[i][j-1]){
                dp[i][j] = dp[i-1][j] + farm[i][j];
                if (i==1 && j==1){
                    output.moves.push_back(recordMove("Move", i-1, j));
                }
                
            }
            else{
                dp[i][j] = dp[i][j-1] + farm[i][j];
                if (i==1 && j==1){
                    output.moves.push_back(recordMove("Move", i, j-1));
                }

            }
            output.moves.push_back(recordMove("Move", i, j));
            output.nMove++;
            
        }
    }



    output.sweetness = dp[n - 1][m - 1];
    
    return output;
}


int main(){ 
    long long int c,  value;
    int n, m, k, i, j;
    RESULT output;
    cin >> n >> m >> k >> c;   

    vector<long long int> a_line;
    a_line.assign(m, 0);

    vector< vector<long long int> > farm;
    farm.assign(n, a_line);  

    for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            cin >> value;
            farm[i][j] = value;
        }
    }



    output = getSweet(farm, n ,m);
    cout << output.sweetness   << endl;
    cout << output.nMove   << endl;
    for (i=0; i<output.moves.size(); i++){
        cout << output.moves[i].moveType << " " << output.moves[i].moveI << " " << output.moves[i].moveJ << endl;
    }


    return 0;
}