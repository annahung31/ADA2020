

#include <bits/stdc++.h>
#include<vector>
#include<algorithm>
#include <numeric>
using namespace std;


long long int findPair(vector<long long int> candies, long long int k){
    
    long long int i, l, sum, nPair=0;
    vector<long long int> temp;

    for (i=2; i<=candies.size(); i++){
        for (l=0; l<=candies.size()-i; l++){
            //extract seq [l:l+i]
            temp.assign(candies.begin()+l, candies.begin()+l+i);
            //cout << "temp:" << temp.front() << temp.back() << endl;
            //sort, get off max, min
            if (temp.size() <3){
                nPair += 1;
            }
            else{

                sort(temp.begin(), temp.end());
                sum = accumulate(temp.begin()+1, temp.end()-1,
                               decltype(temp)::value_type(0));
                
                if (sum % k == 0){
                    nPair +=1;
                }

            }
            //sum, check dividable by k
        }
    }


    return nPair;
    }


int main(){ 
    
    cin.tie(nullptr), cout.sync_with_stdio(0);

    long long int n, k, i, value, nPair; 
    
    cin >> n >> k;          

    vector<long long int> candies;
    candies.assign(n, 0);  

    for (i=0; i<n; i++){
            cin >> value;
            candies[i] = value;
        
    }

    
    nPair = findPair(candies, k);
    cout << nPair << endl;
    return 0; 
    }
