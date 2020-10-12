
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

long long int max(long long int x, long long int y){
    if (x > y){
        return x;
    }
    else{
        return y;
    }
};


STEP recordSTEP(long long int sweetness, int fromX, int fromY){
    STEP step;
    step.sweetness = sweetness;
    step.fromX=fromX;
    step.fromY=fromY;
    return step;
};





MOVE recordMove(string moveType, int i, int j){
    MOVE move;
    move.moveType=moveType;
    move.moveI=i;
    move.moveJ=j;
    return move;
};


RESULT getSweet(vector< vector<long long int> > farm, int n, int m){
    vector<vector<STEP>> dp(n, vector<STEP>(m));
    RESULT output;
    MAXSWEET maxSweet;
    dp[0][0].sweetness = farm[0][0];
    int i, j;
    //init: O(n)
    for (i=1; i<n; i++){
        dp[i][0] = recordSTEP(dp[i-1][0].sweetness + farm[i][0], i-1, 0);
    }

    for (j=1; j<m; j++){
        dp[0][j] = recordSTEP(dp[0][j-1].sweetness + farm[0][j], 0, j-1);
    }

    // O(m*n)
    for (i=1; i<n; i++){
        for (j=1; j<m; j++){
            if (dp[i-1][j].sweetness > dp[i][j-1].sweetness){
                // cout << i << "," << j << " move from " <<  i-1 << "," << j << endl;
                dp[i][j] = recordSTEP(dp[i-1][j].sweetness + farm[i][j], i-1, j);
            }
            else{
                // cout << i << "," << j << " move from " <<  i << "," << j-1 << endl;                
                dp[i][j] = recordSTEP(dp[i][j-1].sweetness + farm[i][j], i, j-1);

            }

            if (maxSweet.sweetness < dp[i][j].sweetness){
                maxSweet.sweetness = dp[i][j].sweetness;
                maxSweet.x = i;
                maxSweet.y = j;
            }

        }
    }

    for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            cout << dp[i][j].sweetness << " ";
        }
        cout << "\n";
    }

    cout << "Max sweetness:" << maxSweet.sweetness << " @ "  << maxSweet.x << "," << maxSweet.y << "\n";




    i=n - 1; j=m - 1;
    while (i>=0 && j >=0){
        if (i==0 && j==0){
            break;
        }
        output.moves.push_back(recordMove("Move", i, j));
        int tempi=i, tempj=j;
        i = dp[tempi][tempj].fromX;
        j = dp[tempi][tempj].fromY;

        output.nMove++;
    }

    output.sweetness = dp[n - 1][m - 1].sweetness;
    
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
    // cout << output.sweetness << endl;
    // cout << output.nMove << endl;
    // for (i=output.moves.size()-1; i>=0; i--){
    //     cout << output.moves[i].moveType << " " << output.moves[i].moveI << " " << output.moves[i].moveJ << endl;
    // }


    return 0;
}