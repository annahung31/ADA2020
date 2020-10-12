

#include "helper.h"
#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
using namespace Memory;


class EVENT{
    public:
        int eventType=0;
        long long int varA=0;
        long long int varB=0;
        long long int varC=0;
        int varD=0;
        long long int varE=0; 
};


bool sortP( const EVENT& v1, 
               const EVENT& v2 ) { 
 return v1.varB < v2.varB; 
} 


bool sortA( const EVENT& v1, 
               const EVENT& v2 ) { 
 return v1.varC < v2.varC; 
} 




void combine(vector<EVENT>& eventSet, long long int st, long long int mid, long long int ed, vector<long long int>  &damage){

    long long int i;
    vector<EVENT> PSet, ASet;
    //construct PSet, ASet
    for (i=st; i<=mid; i++){
        
        if (eventSet[i].eventType == 0){
            // cout << "get P" << endl;
            PSet.push_back(eventSet[i]);
        }
    }
    sort(PSet.begin(), PSet.end(), sortP);

    for (i=mid+1; i<=ed; i++){
        
        if (eventSet[i].eventType == 1){
            // cout << "get A" << endl;
            ASet.push_back(eventSet[i]);
        }
    }
    sort(ASet.begin(), ASet.end(), sortA);

    // cout << "===round===" << endl;
    // cout << "====P===" << endl;
    // for (i=0; i<PSet.size(); i++){
    //     cout << "P:" << PSet[i].varA << " " << PSet[i].varB << endl;
    // }


    // cout << "====A===" << endl;
    // for (i=0; i<ASet.size(); i++){
    //     cout << "A:" << ASet[i].varA << " " << ASet[i].varB << " " << ASet[i].varC << " " << ASet[i].varD << endl;
    // }

    if (ASet.size()==0 or PSet.size()==0){
        // cout << "empty" << endl;
        return;
    }

    long long int AID, PID;
    AID = ASet.size()-1;
    while (AID>=0){
        // cout << "===cp:===" << endl;
        // cout << "A: " << ASet[AID].varA << " " << ASet[AID].varB << " " << ASet[AID].varC << " " << ASet[AID].varD << endl;
        // cout << "P: " << PSet.back().varA << " " << PSet.back().varB << endl;
        if (ASet[AID].varC >= PSet.back().varB){
            add(ASet[AID].varA, ASet[AID].varB, ASet[AID].varD);
            // cout << "attack: " << ASet[AID].varA << " " << ASet[AID].varB << " " << ASet[AID].varD << endl;
            ASet[AID].varE = 1;
            AID--;
        }
        else{
            PID = PSet.back().varE;
            // cout << "failed: get player " << PSet.back().varA << " " << PSet.back().varB << " : " << get(PSet.back().varA) << endl;
            damage[PID] += get(PSet.back().varA);
            PSet.pop_back();
            if (PSet.empty()){
                break;
            }
        }

    }

    while (PSet.size() !=0){
        PID = PSet.back().varE;
        
        damage[PID] += get(PSet.back().varA);
        // cout << "get player " << PSet.back().varA << " " << PSet.back().varB << " : " << get(PSet.back().varA) << endl;
        PSet.pop_back();
    }
    

    
    //reset array
    for (i=0; i<ASet.size(); i++){
        // cout << "reset A:" << ASet[i].eventType << "," << ASet[i].varA << "-" << ASet[i].varB << " flag:" << ASet[i].varE << endl;
        if (ASet[i].varE ==1){
            // cout << "clean:" << ASet[i].varA << "-" << ASet[i].varB << endl;
            add(ASet[i].varA, ASet[i].varB, -1*ASet[i].varD);
        }

    }

}


void getDamage(vector<EVENT>& eventSet, long long int st, long long int ed, vector<long long int>  &damage){
    if (st == ed){
        return;
    } 

    long long int mid = (st+ed)/2;
    getDamage(eventSet, st, mid, damage);
    getDamage(eventSet, mid+1, ed, damage);

    combine(eventSet, st, mid, ed, damage);

    return;    
}



int main(){ 
    long long int n,m, i, j, vara, varb, varc, nP=0;
    int vard;
    string iEventType;
    cin >> n >> m;          
    EVENT iEvent;
    
    vector<EVENT> eventSet;

    vector<long long int> damage;
    for (i=0; i<m; i++){
        cin >> iEventType;
        if (iEventType == "P"){
            
            iEvent.eventType = 0;
            cin >> vara >> varb;
            iEvent.varA = vara;
            iEvent.varB = varb;
            iEvent.varC = 0;
            iEvent.varD = 0;
            iEvent.varE = nP;
            nP++;
        }
        else{
            cin >> vara >> varb >> varc >> vard;
            
            iEvent.eventType = 1;
            iEvent.varA = vara;
            iEvent.varB = varb;
            iEvent.varC = varc;
            iEvent.varD = vard;
            iEvent.varE = 0;
        }
        eventSet.push_back(iEvent);
        }
    
    
    // for (i=0; i<m; i++){

    //     cout << eventSet[i].eventType << ":" << eventSet[i].varA << " " << eventSet[i].varB << " " << eventSet[i].varC << " " << eventSet[i].varD << " " << eventSet[i].varE << endl;
    // }
     


    damage.assign(nP+1, 0);
    getDamage(eventSet, 0, eventSet.size()-1, damage);
    

    for (j=0;j<nP; j++){
        cout << damage[j] << "\n";
    }

    return 0; 
}

