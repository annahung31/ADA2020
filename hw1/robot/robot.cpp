
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
        long long int sweetness=0;
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
        long long int sweetness=(-1)*1e9;
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



RESULT getSweet(vector< vector<long long int> > farm, int n, int m, int k, long long int c){
    STEP step;
    vector<vector<vector<STEP>>> dp(k+1,  vector<vector<STEP>>(n, vector<STEP>(m, step)));
    RESULT output;
    
    vector< MAXSWEET > maxSweet(k+1);
    dp[0][0][0].sweetness = farm[0][0];
    int i, j;
    long long int d=0;
    // init: O(n)
    for (i=1; i<n; i++){
        
        dp[0][i][0] = recordSTEP(dp[0][i-1][0].sweetness + farm[i][0], "Move", i-1, 0);

        if (maxSweet[0].sweetness < dp[0][i][0].sweetness){
            maxSweet[0].sweetness = dp[0][i][0].sweetness;
            maxSweet[0].x = i;
            maxSweet[0].y = 0;
        }

    }

    for (j=1; j<m; j++){
        dp[0][0][j] = recordSTEP(dp[0][0][j-1].sweetness + farm[0][j], "Move", 0, j-1);

            if (maxSweet[0].sweetness < dp[0][0][j].sweetness){
                maxSweet[0].sweetness = dp[0][0][j].sweetness;
                maxSweet[0].x = 0;
                maxSweet[0].y = j;
            }
    
    
    }

    // O(m*n)
    for (i=1; i<n; i++){
        for (j=1; j<m; j++){
            if (dp[0][i-1][j].sweetness > dp[0][i][j-1].sweetness){
                // cout << i << "," << j << " move from " <<  i-1 << "," << j << endl;
                dp[0][i][j] = recordSTEP(dp[0][i-1][j].sweetness + farm[i][j], "Move", i-1, j);
            }
            else{
                // cout << i << "," << j << " move from " <<  i << "," << j-1 << endl;                
                dp[0][i][j] = recordSTEP(dp[0][i][j-1].sweetness + farm[i][j], "Move", i, j-1);

            }

            if (maxSweet[0].sweetness < dp[0][i][j].sweetness){
                maxSweet[0].sweetness = dp[0][i][j].sweetness;
                maxSweet[0].x = i;
                maxSweet[0].y = j;
            }

        }
    }



    // cout << "Max sweetness:" << maxSweet[0].sweetness << " @ "  << maxSweet[0].x << "," << maxSweet[0].y << "\n";

     
    for (d=1; d<=k; d++){
        
        dp[d][0][0] = recordSTEP(farm[0][0]-c*d, "Move", 0, 0);


        for (i=1; i<n; i++){
            // cout << "d:" << d << ", i: " << i << endl;
            if (dp[d][i-1][0].sweetness + farm[i][0]-c*d < maxSweet[d-1].sweetness+farm[i][0]-c*d){
                dp[d][i][0] = recordSTEP(maxSweet[d-1].sweetness+farm[i][0]-c*d, "Jump", maxSweet[d-1].x, maxSweet[d-1].y);
            }
            else{
                dp[d][i][0] = recordSTEP(dp[d][i-1][0].sweetness + farm[i][0]-c*d, "Move", i-1, 0);
            }

            if (maxSweet[d].sweetness < dp[d][i][0].sweetness){
                maxSweet[d].sweetness = dp[d][i][0].sweetness;
                maxSweet[d].x = i;
                maxSweet[d].y = 0;
            }

        }

        for (j=1; j<m; j++){
            // cout << "d:" << d << ", j: " << j << endl;
            if (dp[d][0][j-1].sweetness + farm[0][j]-c*d < maxSweet[d-1].sweetness+farm[0][j]-c*d){
            
                dp[d][0][j] = recordSTEP(maxSweet[d-1].sweetness+farm[0][j]-c*d, "Jump", maxSweet[d-1].x, maxSweet[d-1].y);
            }
            else{
                dp[d][0][j] = recordSTEP(dp[d][0][j-1].sweetness + farm[0][j]-c*d, "Move", 0, j-1);
            }

            if (maxSweet[d].sweetness < dp[d][0][j].sweetness){
                maxSweet[d].sweetness = dp[d][0][j].sweetness;
                maxSweet[d].x = 0;
                maxSweet[d].y = j;
            }

        }

        for (i=1; i<n; i++){
            for (j=1; j<m; j++){
                // cout << "d:" << d << ", i: " << i << ", j: " << j << endl;
                if (dp[d][i-1][j].sweetness-c*d > dp[d][i][j-1].sweetness-c*d && dp[d][i-1][j].sweetness-c*d > maxSweet[d-1].sweetness-c*d){
                    
                    dp[d][i][j] = recordSTEP(dp[d][i-1][j].sweetness + farm[i][j]-c*d, "Move", i-1, j);
                }
                else if (dp[d][i][j-1].sweetness-c*d > dp[d][i-1][j].sweetness-c*d && dp[d][i][j-1].sweetness-c*d > maxSweet[d-1].sweetness-c*d){
                                   
                    dp[d][i][j] = recordSTEP(dp[d][i][j-1].sweetness + farm[i][j]-c*d, "Move", i, j-1);
                }
                else{
                    dp[d][i][j] = recordSTEP(maxSweet[d-1].sweetness-c*d+farm[i][j], "Jump", maxSweet[d-1].x, maxSweet[d-1].y);

                }


                if (maxSweet[d].sweetness < dp[d][i][j].sweetness){
                    maxSweet[d].sweetness = dp[d][i][j].sweetness;
                    maxSweet[d].x = i;
                    maxSweet[d].y = j;
                }
                
            }
        }
        // cout << "maxSweet of " << d << " : " << maxSweet[d].sweetness << " @" << maxSweet[d].x << " , " << maxSweet[d].y << endl;  

        if (maxSweet[d].sweetness < maxSweet[d-1].sweetness){
            d = d-1;
            break;
        }

    }




    i=n - 1; j=m - 1;
    if (d < k){
        d = d;
    }
    else{
        d = k;
    }
    output.sweetness = dp[d][n - 1][m - 1].sweetness;
    int tempi, tempj;
    while (i>=0 && j >=0){
        
        if (i==0 && j==0){
            break;
        }

        
        if (dp[d][i][j].moveType=="Move"){
            output.moves.insert(output.moves.begin(), recordMove("Move", i, j));
            tempi=i, tempj=j;
            i = dp[d][tempi][tempj].fromX;
            j = dp[d][tempi][tempj].fromY;
            // cout << "Move from " << i << " , " << j << endl;
        }
        else{
            // cout << "Jump: " << i << " , " << j << endl;
            output.moves.insert(output.moves.begin(), recordMove("Jump", i, j));
            tempi=i; tempj=j;
            i = dp[d][tempi][tempj].fromX;
            j = dp[d][tempi][tempj].fromY;
            d--;
            // cout << "Jump from " << d  << ": " <<  i << " , " << j << endl;
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
        cout << output.moves[i].moveType << " " << output.moves[i].moveI << " " << output.moves[i].moveJ << endl;
    }


    return 0;
}
