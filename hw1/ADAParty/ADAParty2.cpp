

#include <bits/stdc++.h>
#include<vector>
#include<algorithm>
#include <numeric>
using namespace std;


long long int max(long long int x, long long int y){
    if (x > y){
        return x;
    }
    else{
        return y;
    }
};

long long int min(long long int x, long long int y){
    if (x > y){
        return y;
    }
    else{
        return x;
    }
};

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




void case4(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    long long int l, r, i, MAXl, MINl, MAXr, MINr, ml, mr, rBorder;
    
    //case 2 : | max min 
    vector<long long int> Mr(k, 0);

    r=mid+1;
    rBorder = r;
    MAXl = candies[mid];
    MINl = candies[mid];
    MAXr = candies[r];
    MINr = candies[r];
    for (l=mid; l>=0; l--){
        if (l==0){
            ml = (0 + MINl)%k;
        }
        else{
            ml = (prefixSum[l-1]+MINl) % k;
        }

        if (r<=ed){
            if (MAXl <= MAXr && MINl <= MINr){
                rBorder = r;
                for (i=rBorder; i<=r; i++){
                    mr = (prefixSum[r]-MAXr) % k;
                    Mr[mr] +=1;
                }
                nPair += Mr[ml];
                }
            else{
                if (r<=ed){
                    r++;
                }
                }
            
        }
        else{
            nPair += Mr[ml];
        }
    }
}



void case3(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    long long int l, r, i, MAXl, MINl, MAXr, MINr, ml, mr, minBorder, maxBorder;
    
    //case 3 :  max | min 
    vector<long long int> Mr(k, 0);

    r=mid+1;
    minBorder = r;
    maxBorder = r;
    MAXl = candies[mid];
    MINl = candies[mid];
    MAXr = candies[r];
    MINr = candies[r];
    for (l=mid; l>=0; l--){
        if (l==0){
            ml = (0 + MAXl)%k;
        }
        else{
            ml = (prefixSum[l-1]+MAXl) % k;
        }
        
        //find min border
        if (MINl < candies[l]){
            MINl = candies[l];
            if (MINl <= MINr){
                r = minBorder;
                while (r<=ed){
                    if (MINr <= MINr){
                        r++;
                    }
                    else{
                        minBorder = r;
                        break;
                    }
                }
            }
        }

        //find max border
        if (MAXl > candies[l]){
            MAXl = candies[l];
            if (MAXl >= MAXr){
                r = maxBorder;
                while (r<=ed){
                    if (MAXl >= MAXr){
                        r++;
                    }
                    else{
                        maxBorder = r;
                        break;
                    }
                }
            }
        }





        
        
    }
}






void case2(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    long long int l, r, i, MAXl, MINl, MAXr, MINr, ml, mr, rBorder;
    
    //case 2 : | max min 
    vector<long long int> Mr(k, 0);

    r=mid+1;
    rBorder = r;
    MAXl = candies[mid];
    MINl = candies[mid];
    MAXr = candies[r];
    MINr = candies[r];
    for (l=mid; l>=0; l--){
        if (l==0){
            ml = 0;
        }
        else{
            ml = (prefixSum[l-1]) % k;
        }

        if (r<=ed){
            if (MAXl <= MAXr && MINl >= MINr){
                rBorder = r;
                for (i=rBorder; i<=r; i++){
                    mr = (prefixSum[r]-MAXr-MINr) % k;
                    Mr[mr] +=1;
                }
                nPair += Mr[ml];
                }
            else{
                if (r<=ed){
                    r++;
                }
                }
            
        }
        else{
            nPair += Mr[ml];
        }
    }
}






void case1(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    long long int l, r, i, MAXl, MINl, MAXr, MINr, ml, mr, rBorder;
    
    //case 1 :  max min |
    vector<long long int> Mr(k, 0);

    r=mid+1;
    rBorder = r;
    MAXl = candies[mid];
    MINl = candies[mid];
    MAXr = candies[r];
    MINr = candies[r];
    for (l=mid; l>=0; l--){
        if (l==0){
            ml = (0 + MAXl + MINl) % k;
        }
        else{
            ml = (prefixSum[l-1] + MAXl + MINl) % k;
        }

        if (r<=ed){
            if (MAXl >= MAXr && MINl <=MINr){
                rBorder = r;
                for (i=rBorder; i<=r; i++){
                    mr = prefixSum[r] % k;
                    Mr[mr] +=1;
                }
                nPair += Mr[ml];
                }
            else{
                if (r<=ed){
                    r++;
                }
                }
            
        }
        else{
            nPair += Mr[ml];
        }
    }


}

void combine(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    cout << st << "-" << mid << "-" << ed << "\n";
    case1(candies, prefixSum, nPair, k, st, mid, ed);
    case2(candies, prefixSum, nPair, k, st, mid, ed);
    case3(candies, prefixSum, nPair, k, st, mid, ed);
    // case4(candies, prefixSum, nPair, k, st, mid, ed);
}

void getPair(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int ed){
    
    if (ed-st < k or ed-st < 3){
        // cout << "too small" << "\n";
        return;
    }
    
    long long int mid = (st+ed)/2;
    getPair(candies, prefixSum, nPair, k, st, mid);
    getPair(candies, prefixSum, nPair, k, mid+1, ed);

    combine(candies, prefixSum, nPair, k, st, mid, ed);

}



int main(){ 
    
    cin.tie(nullptr), cout.sync_with_stdio(0);

    long long int n, k, i, value, nPair; 
    
    cin >> n >> k;          

    vector<long long int> candies, prefixSum;
    candies.assign(n, 0);  
    prefixSum.assign(n, 0);
    for (i=0; i<n; i++){
            cin >> value;
            candies[i] = value;
            if (i==0){
                prefixSum[i]=candies[i];
            }
            else{
                prefixSum[i]=prefixSum[i-1] + candies[i];
            }
    }

    for (i=0; i<n; i++){
        cout << prefixSum[i] << " ";
    }
    cout << "\n";

    // if (n<=200 && k <= 200){
    //     nPair = findPair(candies, k);
    // }
    // else{
    //     getPair(candies, prefixSum, nPair, k, 0, n-1);
    // }
    getPair(candies, prefixSum, nPair, k, 0, n-1);
    
    cout << nPair+n-1 << endl;
    return 0; 
    }
