
#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;


class MOVE{
    public:
        string moveType;
        int moveI=0;
        int moveJ=0;
};

class STEP{
    public:
        long long int sweetness=(-1)*1e10;
        string moveType;
        int fromX=0;
        int fromY=0;
        
};

class RESULT{
    public:
        long long int sweetness=0;
        int nMove=0;
        vector< MOVE> moves;
};


class MAXSWEET{
    public:
        long long int sweetness=(-1)*1e10;
        int x=0;
        int y=0;
};



STEP recordSTEP(long long int sweetness,string moveType, int fromX, int fromY){
    STEP step;
    step.sweetness = sweetness;
    step.fromX=fromX;
    step.fromY=fromY;
    step.moveType=moveType;
    return step;
};


MOVE recordMove(string moveType, int i, int j){
    MOVE move;
    move.moveType=moveType;
    move.moveI=i;
    move.moveJ=j;
    return move;
};


void updateMAX(vector< MAXSWEET>& maxSweet, vector<vector<vector<STEP>>>& dp, long long int d, int i, int j){
    // cout << "( " << i-1 << "," << j-1 << ") bigger" << endl;
    if (maxSweet[d].sweetness <= dp[d][i][j].sweetness){
        maxSweet[d].sweetness = dp[d][i][j].sweetness;
        maxSweet[d].x = i;
        maxSweet[d].y = j;
        }
}


RESULT getSweet(vector< vector<long long int> > farm, int n, int m, int k, long long int c){
    STEP step;
    vector<vector<vector<STEP>>> dp(k+2,  vector<vector<STEP>>(n+1, vector<STEP>(m+1, step)));
    RESULT output;
    
    vector< MAXSWEET> maxSweet(k+2);
    // cout << "maxSweet size:" << maxSweet.size() << endl;
    int i, j; long long int d;


    for (d=1; d<=k+1; d++){
        // cout << "=============" << endl;

        for (i=1; i<n+1; i++){
            for (j=1; j<m+1; j++){
                

                if (i==1 && j==1){
                    if (d==1){
                        dp[d][1][1] = recordSTEP(farm[0][0], "Move", 0, 0);
                    }
                    else{
                        dp[d][1][1] = recordSTEP(maxSweet[d-1].sweetness+farm[0][0]-c*(d-1), "Jump", maxSweet[d-1].x, maxSweet[d-1].y);
                    }
                }

                else{
                    if (dp[d][i-1][j].sweetness>= dp[d][i][j-1].sweetness && dp[d][i-1][j].sweetness> maxSweet[d-1].sweetness){
                        // cout << "Move" << "," << i-1-1 << "," << j-1 <<  endl;
                        dp[d][i][j] = recordSTEP(dp[d][i-1][j].sweetness + farm[i-1][j-1]-c*(d-1), "Move", i-1, j);
                    }
                    else if (dp[d][i][j-1].sweetness>= dp[d][i-1][j].sweetness && dp[d][i][j-1].sweetness > maxSweet[d-1].sweetness){
                        // cout << "Move" << "," << i-1 <<  "," << j-1-1 <<  endl;        
                        dp[d][i][j] = recordSTEP(dp[d][i][j-1].sweetness + farm[i-1][j-1]-c*(d-1), "Move", i, j-1);
                    }
                    else{
                        // cout << "dd ";            
                        // cout << "Jump" <<  "," << maxSweet[d-1].x-1 <<  "," << maxSweet[d-1].y-1 << " sw: " <<maxSweet[d-1].sweetness + farm[i-1][j-1] - c*(d-1)<<  endl;
                        dp[d][i][j] = recordSTEP(maxSweet[d-1].sweetness + farm[i-1][j-1] - c*(d-1), "Jump", maxSweet[d-1].x, maxSweet[d-1].y);

                    }
                    updateMAX(maxSweet, dp, d, i, j);

                }
                // printf("%4lld", dp[d][i][j].sweetness);
                // cout << dp[d][i][j].sweetness << " ";
                // cout << "d:" << d-1 << ", i: " << i-1 << ", j: " << j-1 << ", dp:" << dp[d][i][j].sweetness << endl;

            }
            // cout << endl;
        }
        // cout << endl;
        // cout << "maxSweet of " << d-1 << " : " << maxSweet[d].sweetness << " @" << maxSweet[d].x-1 << " , " << maxSweet[d].y-1 << endl;  

        if (maxSweet[d].sweetness < maxSweet[d-1].sweetness){
            d = d-1;
            break;
        }

    }


    i=n; j=m;

    // cout << "d:" << d-1 << endl;
    // d--;
    if (d<k+1){
        d = d;
    }
    else{
        d--;
    }
    output.sweetness = dp[d][n][m].sweetness;
    // cout << "output sw: " << output.sweetness << endl;
    int tempi, tempj;
    while (i>=1 && j >=1){
        
        if (i==1 && j==1){
            break;
        }

        
        if (dp[d][i][j].moveType=="Move"){
            output.moves.insert(output.moves.begin(), recordMove("Move", i, j));
            tempi=i, tempj=j;
            i = dp[d][tempi][tempj].fromX;
            j = dp[d][tempi][tempj].fromY;
            // cout << "Move from " << i-1 << " , " << j-1 << endl;
        }
        else{
            // cout << "Jump: " << i << " , " << j << endl;
            output.moves.insert(output.moves.begin(), recordMove("Jump", i, j));
            tempi=i; tempj=j;
            i = dp[d][tempi][tempj].fromX;
            j = dp[d][tempi][tempj].fromY;
            d--;

            // cout << "Jump from " << d-1  << ": " <<  i-1 << " , " << j-1 << endl;
        }
        
        output.nMove++;
    }


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



    output = getSweet(farm, n ,m, k, c);
    cout << output.sweetness << endl;
    cout << output.nMove << endl;
    for (i=0; i<output.moves.size(); i++){
        cout << output.moves[i].moveType << " " << output.moves[i].moveI-1 << " " << output.moves[i].moveJ-1 << endl;
    }


    return 0;
}
