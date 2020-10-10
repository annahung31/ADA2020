

#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;


typedef struct POINT POINT;

struct POINT
{
    long long int x;          
    long long int y;      
};



bool sortX( POINT& v1, 
            POINT& v2 ) { 
 return v1.x < v2.x; 
} 



bool sortY( POINT& v1, 
            POINT& v2 ) { 
 return v1.y < v2.y; 
} 

long long int distance(POINT pointA, POINT pointB){
    return (pointA.x - pointB.x)*(pointA.x - pointB.x) + (pointA.y - pointB.y)*(pointA.y - pointB.y);
}


void bruteForce(vector< POINT >& Px, vector< POINT >& Py, long long int& closestDistance){
    long long int i, j, temp;
    for (i=0; i<Px.size(); i++){
        for (j=i+1; j<Px.size(); j++){
            temp = distance(Px[i], Px[j]);
            if(temp < closestDistance){
                closestDistance = temp;
            } 
            
        }
    }

}


void closestPair(vector< POINT >& Px, vector< POINT >& Py, long long int& closestDistance){

    // if (Px.size() <=3){
    bruteForce(Px, Py, closestDistance);
    // }

}



int main(){ 
    
    long long int n, i, x, y, closestDistance=3e18; //INT_MAX is 10e9, not big enough
    cin.tie(0), cout.sync_with_stdio(0);
    cin >> n;          
  
    vector< POINT > pointSet;
    
    for (i=0; i<n; i++){
        cin >> x >> y;
        POINT a_point;
        a_point.x = x;
        a_point.y = y;
        pointSet.push_back(a_point);
        
    }


    vector< POINT > Px(pointSet);
    vector< POINT > Py(pointSet);
    sort(Px.begin(), Px.end(), sortX);
    sort(Py.begin(), Py.end(), sortY);

    closestPair(Px, Py, closestDistance);
    cout << (-1)*closestDistance << endl;

    return 0; 
}