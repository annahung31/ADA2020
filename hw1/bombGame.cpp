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
        long long int varD=0;
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


long long int combine(vector<EVENT> eventSet, long long int front_idx, long long int mid_idx, long long int end_idx, vector<long long int>  &damage){
    vector< EVENT > leftSet(eventSet.begin()+front_idx, eventSet.begin()+mid_idx+1);
    vector< EVENT > rightSet(eventSet.begin()+mid_idx+1, eventSet.begin()+end_idx+1);

    for (long long int i=0; i<rightSet.size(); i++){
        if (rightSet[i].eventType==1){
            for (long long int j=0; j<leftSet.size(); j++){
                if (leftSet[j].eventType==0){
                    if (rightSet[i].varA <= leftSet[j].varA &&  leftSet[j].varA <= rightSet[i].varB && leftSet[j].varB <= rightSet[i].varC){
                        long long int idxP=leftSet[j].varE;
                        damage[idxP] += rightSet[i].varD;
                        
                    }
                }
            }
        }

    }
}

long long int fastCombine(vector<EVENT> eventSet, long long int front_idx, long long int mid_idx, long long int end_idx, vector<long long int>  &damage){
    vector< EVENT > leftSet(eventSet.begin()+front_idx, eventSet.begin()+mid_idx+1);
    vector< EVENT > rightSet(eventSet.begin()+mid_idx+1, eventSet.begin()+end_idx+1);
    vector< EVENT > tempA, tempP;
    
    //get player and sort
    for (long long int j=0; j<leftSet.size(); j++){
        if (leftSet[j].eventType==0){
            tempP.push_back(leftSet[j]);
        } 
    }
    sort(tempP.begin(), tempP.end(), sortP); 
    long long int nPlayer = tempP.size();
    

    // cout << "=====left player=====" << endl;
    // for (int i=0; i<tempP.size(); i++){
    //     cout << tempP[i].eventType << ":" << tempP[i].varA << " " << tempP[i].varB << " " << tempP[i].varC << " " << tempP[i].varD << " " << tempP[i].varE << endl;
    // }
     
    
    //get attack and sort
    for (long long int i=0; i<rightSet.size(); i++){
        if (rightSet[i].eventType==1){
            tempA.push_back(rightSet[i]);
        } 
    }
    sort(tempA.begin(), tempA.end(), sortA); 
    long long int nBomb = tempA.size();


    // cout << "=====right bomb=====" << endl;
    // for (int i=0; i<tempA.size(); i++){
    //     cout << tempA[i].eventType << ":" << tempA[i].varA << " " << tempA[i].varB << " " << tempA[i].varC << " " << tempA[i].varD << " " << tempA[i].varE << endl;
    // }
     



    while (nBomb!=0 && nPlayer!=0){
        // cout << nBomb << "," << nPlayer << endl;
        // cout << "Now: " << tempA[nBomb-1].varA << "-" << tempA[nBomb-1].varB << " to No. " << tempP[nPlayer-1].varE << endl;
        if (tempA[nBomb-1].varC >= tempP[nPlayer-1].varB){
            //cout << tempA[nBomb-1].varA << "-" << tempA[nBomb-1].varB << endl;
            add(tempA[nBomb-1].varA, tempA[nBomb-1].varB, tempA[nBomb-1].varD);
            tempA[nBomb-1].varE=1; //varE of bomb is a flag to indicate if it was used to added to array or not. 
            // cout << "flag now: " << tempA[nBomb-1].varE << endl;
            nBomb--;
        }
        else{
            long long int idxP=tempP[nPlayer-1].varE;
            damage[idxP] += get(tempP[nPlayer-1].varA); 
            //cout << "player " << idxP << " get " << tempP[nPlayer-1].varA << endl;
            nPlayer--;
        }
        

    }


    
    if (nPlayer!=0){
        while (nPlayer!=0){
            long long int idxP=tempP[nPlayer-1].varE;
            damage[idxP] += get(tempP[nPlayer-1].varA); 
            // cout << "player " << idxP << " get " << get(tempP[nPlayer-1].varA) << endl;
            nPlayer--;
        }


    }
    

    
    //reset array
    for (long long int i=0; i<tempA.size(); i++){
        // cout << "reset A:" << tempA[i].eventType << "," << tempA[i].varA << "-" << tempA[i].varB << "flag:" << tempA[i].varE << endl;
        if (tempA[i].varE ==1){
            // cout << "clean:" << tempA[i].varA << "-" << tempA[i].varB << endl;
            add(tempA[i].varA, tempA[i].varB, -1*tempA[i].varD);
            
        }
        else{
            break;
        }
    }
    

}





long long int getDamage(vector<EVENT> eventSet, long long int front_idx, long long int end_idx, vector<long long int>  &damage){
    
    long long int mid_idx = (front_idx + end_idx)/2;
    if (front_idx < mid_idx){
        //cout << front_idx << "," << end_idx << endl;
        // Divide
        getDamage(eventSet, front_idx, mid_idx, damage);
        getDamage(eventSet, mid_idx+1, end_idx, damage);

        fastCombine(eventSet, front_idx, mid_idx, end_idx, damage);
        
    }
    else{
        combine(eventSet, front_idx, mid_idx, end_idx, damage);

    }


}
    



int main(){ 
    long long int n,m, i, j, vara, varb, varc, vard, nP=0;
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
        }
        eventSet.push_back(iEvent);
        }
    
    
    // for (i=0; i<m; i++){

    //     cout << eventSet[i].eventType << ":" << eventSet[i].varA << " " << eventSet[i].varB << " " << eventSet[i].varC << " " << eventSet[i].varD << " " << eventSet[i].varE << endl;
    // }
     


    damage.assign(nP+1, 0);
    getDamage(eventSet, 0, eventSet.size()-1, damage);
    

    for (j=0;j<nP; j++){
        cout << damage[j] << endl;
    }

    return 0; 
}

