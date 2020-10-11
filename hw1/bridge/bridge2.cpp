

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


long long int min(long long int x, long long int y){
    if (x > y){
        return y;
    }
    else{
        return x;
    }
}




long long int distance(POINT pointA, POINT pointB){
    return (pointA.x - pointB.x)*(pointA.x - pointB.x) + (pointA.y - pointB.y)*(pointA.y - pointB.y);
}


long long int bruteForce(vector< POINT >& pointSet, long long int st, long long int ed){
    long long int i, j, temp=3e18;
    for (i=st; i<=ed; i++){
        for (j=i+1; j<=ed; j++){
            if(distance(pointSet[i], pointSet[j]) < temp){
                temp = distance(pointSet[i], pointSet[j]);
            } 
            
        }
    }
    return temp;

}




long long int stripPointDistance(vector< POINT >& stripPointSet, long long int d){
    long long int sMin = d;
    // cout << "st d:" << sMin << endl;
    for (long long int i=0; i<stripPointSet.size(); i++){
        long long int j = 0;
        while (j<=7 && i+j<stripPointSet.size()-1){
            
            j++;
            if (distance(stripPointSet[i], stripPointSet[i+j])<sMin){
                sMin = distance(stripPointSet[i], stripPointSet[i+j]);
            
        }

            
        }
    }
    // cout << "st d out:" << sMin << endl;
    return sMin;
}



long long int closestPair(vector< POINT >& pointSet, long long int st, long long int ed){
    
    if (ed - st <3){
        // cout << bruteForce(pointSet, st, ed) << endl;
        return bruteForce(pointSet, st, ed);
    }
    
    // Divide
    long long int mid_idx = (st + ed)/2;
    long long int dl = closestPair(pointSet, st, mid_idx);
    long long int dr = closestPair(pointSet, mid_idx+1, ed);
    long long int d = min(dl, dr);
    
    
    
    
    //get strips

    vector<POINT> stripPointSet;

    for (long long int i=st; i<=ed; i++){
        if ((pointSet[i].x - pointSet[mid_idx].x)*(pointSet[i].x - pointSet[mid_idx].x)< d){
            POINT a_point;
            a_point.x = pointSet[i].x;
            a_point.y = pointSet[i].y;
            stripPointSet.push_back(a_point);
        }
    }

    if (stripPointSet.empty()){
        //cout << "empty" << endl;
        return d;
    }
    sort(stripPointSet.begin(), stripPointSet.end(), sortY); 
    long long int ds = stripPointDistance(stripPointSet, d);
    
    // cout << st << "," << mid_idx << "," << ed << "::dl:" << dl << ", dr:" << dr <<  ", ds:" << ds << endl;
    return min(ds, d);
    

}



int main(){ 
    
    long long int n, i, x, y, closestDistance; //INT_MAX is 10e9, not big enough
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



    sort(pointSet.begin(), pointSet.end(), sortX);

    closestDistance = closestPair(pointSet, 0, pointSet.size()-1);
    cout << (-1)*closestDistance << endl;

    return 0; 
}