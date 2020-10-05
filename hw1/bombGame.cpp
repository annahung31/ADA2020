#include "helper.h"

#include<bits/stdc++.h>
#include<vector>
#include<algorithm>
using namespace std;
using namespace Memory;

class EVENT{
    public:
        string eventType;
        int  varA=0;
        int  varB=0;
        int  varC=0;
        int  varD=0;
};

int combine(vector<EVENT> eventSet, int front_idx, int mid_idx, int end_idx){
    vector< EVENT > leftSet(eventSet.begin()+front_idx, eventSet.begin()+mid_idx+1);
    vector< EVENT > rightSet(eventSet.begin()+mid_idx+1, eventSet.begin()+end_idx+1);

    for (int i=0; i<rightSet.size(); i++){
        if (rightSet[i].eventType=="A"){
            for (int j=0; j<leftSet.size(); j++){
                if (leftSet[j].eventType=="P"){
                    if (rightSet[i].varA <= leftSet[j].varA &&  leftSet[j].varA <= rightSet[i].varB && leftSet[j].varB <= rightSet[i].varC){
                        add(leftSet[j].varA, leftSet[j].varA, rightSet[i].varD);
                    }
                }
            }
        }

    }
}

//這裡的 time complex 太高了，要想辦法降低。 會真正用到 add()


int getDamage(vector<EVENT> eventSet, int front_idx, int end_idx){
    if (front_idx < end_idx){
        // Divide
        int mid_idx = (front_idx + end_idx)/2;
        getDamage(eventSet, front_idx, mid_idx);
        getDamage(eventSet, mid_idx+1, end_idx);
        
        combine(eventSet, front_idx, mid_idx, end_idx);
        
    }
}



int main(){ 
    int n,m, i, j, vara, varb, varc, vard, jStop;
    string iEventType;
    cin >> n >> m;          

    EVENT iEvent;
    vector<EVENT> eventSet;

    for (i=0; i<m; i++){
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
        eventSet.push_back(iEvent);
        }
    getDamage(eventSet, 0, eventSet.size()-1);
    
    for (i=0; i<m; i++){
        
        if (eventSet[i].eventType=="P"){
            cout << get(eventSet[i].varA) << endl;
        }
    }

    return 0; 
}

