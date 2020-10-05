#include "helper.h"

#include<bits/stdc++.h>
#include<vector>
#include<algorithm>
using namespace std;

class EVENT{
    public:
        string eventType;
        int  varA;
        int  varB;
        int  varC;
        int  varD;
};






int main(){ 
    int n,m, i, j, vara, varb, varc, vard, jStop;
    string iEventType;
    cin >> n >> m;          

    EVENT iEvent;
    vector<EVENT> eventSet;

    for (i=0; i<n; i++){
        cin >> iEventType;
        iEvent.eventType = iEventType;
        if (iEventType == "P"){
            cin >> vara >> varb;
            iEvent.varA = vara;
            iEvent.varB = varb;
        }
        else{
            cin >> vara >> varb >> varc >> vard;
            iEvent.varA = vara;
            iEvent.varB = varb;
            iEvent.varC = varc;
            iEvent.varD = vard;
        }
 
        }
    



    return 0; 
}