

#include <bits/stdc++.h> 
#include "helper.h"
using namespace std; 
using namespace DLX;


int main(){

    /* 
     Example problem 
  
     X = {1,2,3,4,5,6,7} 
     set-1 = {1,4,7} 
     set-2 = {1,4} 
     set-3 = {4,5,7} 
     set-4 = {3,5,6} 
     set-5 = {2,3,6,7} 
     set-6 = {2,7} 
     set-7 = {1,4} 
  
     Solutions : {6 ,4, 2} and {6, 4, 7} 
    */

    int sz = 7;
    Init(sz);
    vector<vector<int>> sets{{1,4,7},
                            {1,4},
                            {4,5,7},
                            {3,5,6},
                            {2,3,6,7},
                            {2,7},
                            {1,4}};


    for (int i =0; i < sz; i++){
        AddRow(i, sets[i]);
    }

    vector<int> ans;
    ans = Solver();
    for (int i=0; i < ans.size(); i++){
        cout << ans[i]+1 << " ";
    }


    return 0;
}