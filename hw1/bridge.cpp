

#include <bits/stdc++.h>
#include<vector>
#include<algorithm>
using namespace std;

bool sortcol( const vector<int>& v1, 
               const vector<int>& v2 ) { 
 return v1[0] < v2[0]; 
} 

// return a vector set with vector[0] to have smallest y.
bool sortY( const vector<int>& v1, 
               const vector<int>& v2 ) { 
 return v1[1] < v2[1]; 
} 

int min(int x, int y){
    if (x > y){
        return y;
    }
    else{
        return x;
    }
}


int distance(vector<int> pointA, vector<int> pointB){
    return (pointA[0] - pointB[0])*(pointA[0] - pointB[0]) + (pointA[1] - pointB[1])*(pointA[1] - pointB[1]);
}
 
int directCal(vector< vector<int> > pointSet, long long int n){
    long long int i, j, closestDistance=3e18, temp=0;


    for (i=0; i<pointSet.size(); i++){
        for (j=i+1; j<pointSet.size(); j++){
            temp = distance(pointSet[i], pointSet[j]);
            //cout << "temp:" << temp << endl;
            //cout << "closestDistance:" << closestDistance << endl;
            if(temp < closestDistance){
                closestDistance = temp;
            } 
            
        }
    }

    return closestDistance;
}



int stripPointDistance(vector< vector<int> > stripPointSet, int d){
    int sMin = d;

    for (int i=0; i<stripPointSet.size(); i++){
        for (int j=i+1; j<stripPointSet.size(); j++){
            if (stripPointSet[j][1]-stripPointSet[i][1]<=d){
                sMin = min(distance(stripPointSet[j], stripPointSet[i]), sMin);
            }
            else{
                break;
            }
        }
    }

    return sMin;
}


int closestPair(vector< vector<int> > pointSet, long long int front_idx, long long int end_idx){
    if (end_idx - front_idx <=2){
        int d = directCal(pointSet, end_idx - front_idx+1);
        return d;
    }
    // Divide
    int mid_idx = (front_idx + end_idx)/2;
    int dl = closestPair(pointSet, front_idx, mid_idx);
    int dr = closestPair(pointSet, mid_idx+1, end_idx);
    int d = min(dl, dr);

    
    //get strips
    vector<int> a_stripPoint;
    a_stripPoint.assign(2, 0);  
    vector< vector<int> > stripPointSet;

    for (int i=front_idx; i<=end_idx; i++){
        if (pointSet[i][0] >= pointSet[mid_idx][0]-d or pointSet[i][0] <= pointSet[mid_idx][0]+d){
            a_stripPoint[0]=pointSet[i][0];
            a_stripPoint[1]=pointSet[i][1];
            stripPointSet.push_back(a_stripPoint);
        }
    }

    sort(stripPointSet.begin(), stripPointSet.end(), sortY); 
    int ds = stripPointDistance(stripPointSet, d);

    return min(ds, d);
}



int main(){ 
    
    long long int n, i, j, value, closestDistance=3e18; //INT_MAX is 10e9, not big enough
    cin.tie(0), cout.sync_with_stdio(0);
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
    closestDistance = closestPair(pointSet, 0, n-1);
    
    closestDistance = closestDistance * (-1);
    cout << closestDistance << endl;
    return 0; 
}