

#include <bits/stdc++.h>
using namespace std;

bool sortcol( const vector<long long int>& v1, 
               const vector<long long int>& v2 ) { 
 return v1[0] < v2[0]; 
} 

// return a vector set with vector[0] to have smallest y.
bool sortY( const vector<long long int>& v1, 
               const vector<long long int>& v2 ) { 
 return v1[1] < v2[1]; 
} 

long long int min(long long int x, long long int y){
    if (x > y){
        return y;
    }
    else{
        return x;
    }
}


long long int distance(vector<long long int> pointA, vector<long long int> pointB){
    return (pointA[0] - pointB[0])*(pointA[0] - pointB[0]) + (pointA[1] - pointB[1])*(pointA[1] - pointB[1]);
}
 
long long int directCal(vector< vector<long long int> >& pointSet, long long int front_idx, long long int end_idx){
    long long int i, j, closestDistance=3e18, temp;

    for (i=front_idx; i<=end_idx; i++){
        for (j=i+1; j<=end_idx; j++){
            //cout << "point A:" << pointSet[i][0] << "," << pointSet[i][1] << endl;
            //cout << "point A:" << pointSet[j][0] << ","  << pointSet[j][1] << endl;
            temp = distance(pointSet[i], pointSet[j]);
            //cout << "temp:" << temp << endl;
            //cout << "closestDistance:" << closestDistance << endl;
            if(temp < closestDistance){
                closestDistance = temp;
            } 
            
        }
    }
    //cout << "directCal:" << closestDistance << endl;
    return closestDistance;
}


/*

long long int stripPointDistance(vector< vector<long long int> >& stripPointSet, long long int d){
    long long int sMin = d;

    for (long long int i=0; i<stripPointSet.size(); i++){
        for (long long int j=i+1; j<stripPointSet.size(); j++){
            if (distance(stripPointSet[j], stripPointSet[i])<=sMin){
                sMin = distance(stripPointSet[j], stripPointSet[i]);
            }
            else{
                break;
            }
            
        }
    }

    return sMin;
}


 */


long long int stripPointDistance(vector< vector<long long int> >& stripPointSet, long long int d){
    long long int sMin = d;

    for (long long int i=0; i<stripPointSet.size(); i++){
        long long int j = 0;
        while (j<=7 && i+j<stripPointSet.size()-1){
            j++;
            if (distance(stripPointSet[i], stripPointSet[i+j])<sMin){
                sMin = distance(stripPointSet[i], stripPointSet[i+j]);
        }
        }
    }
    return sMin;
}





long long int closestPair(vector< vector<long long int> >& pointSet, long long int front_idx, long long int end_idx){
    //cout << front_idx << "," << end_idx << endl;
    //front_idx=0, end_idx=2 的時候卡住
    if (end_idx - front_idx <=2){
        long long int d = directCal(pointSet, front_idx, end_idx);
        return d;
    }
    
    
    // Divide
    long long int mid_idx = (front_idx + end_idx)/2;
    long long int dl = closestPair(pointSet, front_idx, mid_idx);
    long long int dr = closestPair(pointSet, mid_idx+1, end_idx);
    long long int d = min(dl, dr);
    
    
    //get strips
    vector<long long int> a_stripPoint;
    a_stripPoint.assign(2, 0);  
    vector< vector<long long int> > stripPointSet;

    for (long long int i=front_idx; i<=end_idx; i++){
        if ((pointSet[i][0] - pointSet[mid_idx][0])*(pointSet[i][0] - pointSet[mid_idx][0]) < d){
            a_stripPoint[0]=pointSet[i][0];
            a_stripPoint[1]=pointSet[i][1];
            stripPointSet.push_back(a_stripPoint);
        }
    }

    sort(stripPointSet.begin(), stripPointSet.end(), sortY); 
    long long int ds = stripPointDistance(stripPointSet, d);

    
    return min(ds, d);
    
}



int main(){ 
    
    long long int n, i, j, value, closestDistance=3e18; //INT_MAX is 10e9, not big enough
    cin.tie(0), cout.sync_with_stdio(0);
    cin >> n;          

    vector<long long int> a_point;
    a_point.assign(2, 0);  

    vector< vector<long long int> > pointSet;
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