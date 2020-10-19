
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

class MAXEnd{
    public:
        long long int sweetness=(-1)*1e10;
        long long int d=0;
};



class MAXSWEET{
    public:
        long long int sweetness=(-1)*1e10;
        int x=0;
        int y=0;
};


long long int max(long long int x, long long int y, long long int z){
    long long a[] = {x, y, z};
    sort(a, a + 3);
    return a[2]; 
}



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



void updateMAX(vector< MAXSWEET>& maxSweet, vector<vector<vector<long long>>>& dp, long long d, int i, int j){
    // cout << "( " << i-1 << "," << j-1 << ") bigger" << endl;
    if (maxSweet[d].sweetness < dp[d][i][j]){
        maxSweet[d].sweetness = dp[d][i][j];
        maxSweet[d].x = i;
        maxSweet[d].y = j;
        }
}


RESULT getSweet(vector< vector<long long int> > farm, int n, int m, int k, long long int c){
    STEP step;

    vector<vector<vector<long long>>> dp(k+2,  vector<vector<long long>>(n+1, vector<long long>(m+1, (-1)*1e10)));
    RESULT output;
    MAXEnd maxEnd;
    vector< MAXSWEET> maxSweet(k+2);
    // cout << "maxSweet size:" << maxSweet.size() << endl;
    int i, j; long long d, currMax;

    
    for (d=1; d<=k+1; d++){
        for (i=1; i<n+1; i++){
            for (j=1; j<m+1; j++){   
                if (d == 1 && i == 1 && j == 1){
                    dp[1][1][1] = farm[0][0];
                }
                else{
                    // cout << d-1 << ":" << i-1 << ":" << j-1 << "[ ";
                    // cout << dp[d][i-1][j] << " , " << dp[d][i][j-1] << " , " << maxSweet[d-1].sweetness << endl;
                    currMax = max(dp[d][i-1][j], dp[d][i][j-1], maxSweet[d-1].sweetness);
                    dp[d][i][j] = currMax + farm[i-1][j-1] - c * (d-1);
                }

                updateMAX(maxSweet, dp, d, i, j);
                // printf("%13lld", dp[d][i][j]);
            }
            // cout << endl;
        }
        // cout << endl;
        // cout << "maxSweet of " << d-1 << " : " << maxSweet[d].sweetness << " @" << maxSweet[d].x-1 << " , " << maxSweet[d].y-1 << endl;  

        if (dp[d][n][m] > maxEnd.sweetness){
            maxEnd.sweetness = dp[d][n][m];
            maxEnd.d = d;
        }
        
    }


    i=n; j=m;
    d = maxEnd.d;
    // 用終點來 compare，找最大，往回 trace
    output.sweetness = dp[d][n][m];

    while (i >= 1 && j >= 1){
        if (i == 1 && j == 1){
            break;
        }
        // cout << "=====" << endl;
        // cout << "now  i:" << i-1 << " j: " << j-1 << endl;
        // cout << dp[d][i-1][j] << " , " << dp[d][i][j-1] << " , " << maxSweet[d-1].sweetness << endl;
        currMax = max(dp[d][i-1][j], dp[d][i][j-1], maxSweet[d-1].sweetness);
        if (currMax == maxSweet[d-1].sweetness){
            output.moves.insert(output.moves.begin(), recordMove("Jump", i, j));
            d--;
            i = maxSweet[d].x;
            j = maxSweet[d].y;
            // cout << "(" << i << "," << j << ")" << endl;
        }
        else if (currMax == dp[d][i][j-1]){
            output.moves.insert(output.moves.begin(), recordMove("Move", i, j));
            i = i;
            j = j-1;
            
        }
        else{
            output.moves.insert(output.moves.begin(), recordMove("Move", i, j));
            i = i-1; 
            j = j;    
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
