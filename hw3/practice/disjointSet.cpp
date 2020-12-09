
#include <bits/stdc++.h> 
using namespace std; 




class DisjointSet { 
    
public: 
    int NUM, groups, *g, *size;
    // Constructor to create and 
    // initialize sets of n items 
    DisjointSet(int NUM, int groups){
        g = new int[NUM];
        size = new int[groups];
        this->NUM = NUM;
        this->groups = groups;
        

    }


    void initialize(){
        for (int i=0; i< NUM; i++){
            g[i] = i;
    
        }
                
    };

    void push(int x, int gx){
        g[x] = gx;
        size[gx]++;
    }

    int find(int x){
        return g[x];
    }

    bool equivalence(int x, int y){
        return g[x] == g[y];
    }

    void g_union(int x, int y){
        bool eq = equivalence(x, y);
        if (eq) return;

        groups--;
        int gx = g[x]; int gy = g[y];
        for (int i = 0; i < NUM; i++){
            if (g[i] == gx){
                g[i] = gy;  // 把 gx 合併進 gy
                size[gx]--;
                size[gy]++;
            } 
   
        }
    }

    int cardinality(int gx){
        return size[gx];
    }

    bool singleton(int x)
    {
        return size[g[x]] == 1;
    }

};






int main(){
    int NUM = 8;
    int groups = 4;
    DisjointSet dset(NUM, groups); 
    dset.push(0,0);
    dset.push(1,1);
    dset.push(2,2);
    dset.push(3,3);
    dset.push(4,2);
    dset.push(5,1);
    dset.push(6,0);
    dset.push(7,2);
    
    cout << "group id of 0: " << dset.find(0) << "\n";
    cout << "group id of 1: " << dset.find(1) << "\n";
    cout << "size of group 1: "<<  dset.cardinality(1) << "\n";

    dset.g_union(0, 1);  // 把 node 0 和 1 各自所在的 set 合併
    cout << "node 0 and 1 are in same group? " << dset.equivalence(0, 1) << "\n";
    cout << "total num of groups: " << dset.groups << "\n";
    cout << "size of group 1: " << dset.cardinality(1) << "\n";

    cout << "group 3 only contain one element? " <<  dset.singleton(3)  << "\n";

   
    return 0;
}