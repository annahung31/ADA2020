

#include <bits/stdc++.h>
#include<vector>
#include<algorithm>
using namespace std;

bool sortcol( const vector<int>& v1, 
               const vector<int>& v2 ) { 
 return v1[0] < v2[0]; 
} 

 
int directCal(vector< vector<int> > pointSet, long long int n, long long int &closestDistance){
    long long int i, j, temp=0;

    for (i=0; i<pointSet.size(); i++){
        for (j=i+1; j<pointSet.size(); j++){
            temp = (pointSet[i][0] - pointSet[j][0])*(pointSet[i][0] - pointSet[j][0]) + (pointSet[i][1] - pointSet[j][1])*(pointSet[i][1] - pointSet[j][1]);
            //cout << "temp:" << temp << endl;
            //cout << "closestDistance:" << closestDistance << endl;
            if(temp < closestDistance){
                closestDistance = temp;
            } 
            
        }
    }
}

int closestPair(vector< vector<int> > pointSet, long long int n, long long int &closestDistance){
    //if (n<=10){
    directCal(pointSet, n, closestDistance);
    //}
}



int main(){ 
    
    long long int n, i, j, value, closestDistance=INT_MAX;
    cin >> n;          

    vector<int> a_point;
    a_point.assign(2, 0);  

    vector< vector<int> > pointSet;
    pointSet.assign(n, a_point);  

    for (i=0; i<n; i++){
        for (j=0; j<2; j++){
            cin >> value;
            pointSet[i][j] = value;
        }
    }


    //sort the pointSet by x coordinate.
    sort(pointSet.begin(), pointSet.end(), sortcol); 
    closestPair(pointSet, n, closestDistance);
    
    closestDistance = closestDistance * (-1);
    cout << closestDistance << endl;
    return 0; 
}