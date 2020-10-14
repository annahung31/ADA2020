

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

void case1(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    long long int l, r, i, MAX, MIN, ml, mr;
    int flag=1;

    MAX = max(candies[mid], candies[mid-1]);
    MIN = min(candies[mid], candies[mid-1]);

    //case 1 :  max min |
    vector<long long int> Ml(k, 0), Mr(k, 0);

    l=mid-1; r=mid+1;
    ml = (prefixSum[l-1] + MAX + MIN) % k;
    Ml[ml] +=1;
    while (l>=st){
        
        if (flag==1){
            if (MAX >= candies[r] && candies[r] >= MIN){
                mr = prefixSum[r] % k;
                Mr[mr] +=1;
                
                if (r <= ed-1){
                    r++;
                }
                else{
                    flag=0;
                }
            }
            else{

                if (l>0){
                    l--;
                    MAX = max(MAX, candies[l]);
                    MIN = min(MIN, candies[l]);
                    // cout << "Current MAX: " << MAX << ", MIN:" << MIN << "\n";

                    if (l==0){
                        ml = (0 + MAX + MIN) % k;
                    }
                    else{
                        ml = (prefixSum[l-1] + MAX + MIN) % k;
                    }
                    Ml[ml] +=1;
                }
                else{
                    break;
                }

            }
        }

        else{
            if (l>0){
                l--;
                MAX = max(MAX, candies[l]);
                MIN = min(MIN, candies[l]);
                // cout << "Current MAX: " << MAX << ", MIN:" << MIN << "\n";

                if (l==0){
                    ml = (0 + MAX + MIN) % k;
                }
                else{
                    ml = (prefixSum[l-1] + MAX + MIN) % k;
                }
                Ml[ml] +=1;
            }
            else{
                break;
            }

        }
        
    }

    for (i=0; i<k; i++){
        nPair += Ml[i] * Mr[i];
    }

    return;

}



void case2(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    long long int l, r, i, MAX, MIN, ml, mr;
    int flag=1;

    MAX = max(candies[mid+1], candies[mid+2]);
    MIN = min(candies[mid+1], candies[mid+2]);

    //case 2 :   | max min
    vector<long long int> Ml(k, 0), Mr(k, 0);

    l=mid; r=mid+2;
    mr = (prefixSum[r] - MAX - MIN) % k;
    Mr[mr] +=1;
    while (r<=ed){
        // cout << "r @ " << candies[r] << "\n";
        if (flag==1){
            // cout << "==see left: l @ " << candies[l] << "\n"; 
            if (MAX >= candies[l] && candies[l] >= MIN){
                // cout << "in the rage" << "\n";
                if (l==0){
                    ml = 0;
                    flag = 0;
                }
                else{
                    ml = prefixSum[l-1] % k;
                }
                Ml[ml] +=1;

                if (l > 0){
                    l--;
                }
                else{
                    flag=0;
                }
                // cout << "l become " << l << "\n";
            }
            else{
                // cout << "not in the range" << "\n"; 

                if (r < ed){
                    r++;
                    
                    MAX = max(MAX, candies[r]);
                    MIN = min(MIN, candies[r]);
                    // cout << "Current MAX: " << MAX << ", MIN:" << MIN << "\n";
                    mr = (prefixSum[r] - MAX - MIN) % k;
                    Mr[mr] +=1;
                }
                else{
                    break;
                }

            }
        }
        
        else{
            if (r < ed){
                r++;
                
                MAX = max(MAX, candies[r]);
                MIN = min(MIN, candies[r]);
                // cout << "Current MAX: " << MAX << ", MIN:" << MIN << "\n";
                mr = (prefixSum[r] - MAX - MIN) % k;
                Mr[mr] +=1;
            }
            else{
                break;
            }
        }

    }

    for (i=0; i<k; i++){
        // cout << i << " : " << Ml[i] << ", " << Mr[i] << "\n";
        nPair += Ml[i] * Mr[i];
    }

    return;

}



void combine(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int mid, long long int ed){
    case1(candies, prefixSum, nPair, k, st, mid, ed);
    case2(candies, prefixSum, nPair, k, st, mid, ed);
}

void getPair(vector<long long int>& candies, vector<long long int>& prefixSum, long long int& nPair, long long int& k, long long int st, long long int ed){
    
    if (ed-st < k){
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

    // for (i=0; i<n; i++){
    //     cout << prefixSum[i] << " ";
    // }
    // cout << "\n";

    // if (n<=200 && k <= 200){
    //     nPair = findPair(candies, k);
    // }
    // else{
    //     getPair(candies, prefixSum, nPair, k, 0, n-1);
    // }
    getPair(candies, prefixSum, nPair, k, 0, n-1);
    
    cout << nPair << endl;
    return 0; 
    }
