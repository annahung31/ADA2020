#include "helper.h"

#include<bits/stdc++.h>
#include<vector>
#include<algorithm>
using namespace std;

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

    /*
    int i, j;
    for (i=0; i <leftSet.size(); i++){
        cout << "left:" << leftSet[i].eventType << leftSet[i].varA << leftSet[i].varB << leftSet[i].varC << leftSet[i].varD << endl;
    }
    for (j=0; j <rightSet.size(); j++){
        cout << "right:" << rightSet[j].eventType << rightSet[j].varA << rightSet[j].varB << rightSet[j].varC << rightSet[j].varD << endl;
    }
    */
    
    for (int i=0; i<rightSet.size(); i++){
        if (rightSet[i].eventType=="A"){
            for (int j=0; j<leftSet.size(); j++){
                if (leftSet[j].eventType=="P"){
                    cout << "bomb work on " << leftSet[j].varA << leftSet[j].varB << endl;
                }
            }
        }

    }

}


int getDamage(vector<EVENT> eventSet, int front_idx, int end_idx){
    if (front_idx < end_idx){
        // Divide
        int mid_idx = (front_idx + end_idx)/2;
        getDamage(eventSet, front_idx, mid_idx);
        getDamage(eventSet, mid_idx+1, end_idx);
        // conquer
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

    return 0; 
}