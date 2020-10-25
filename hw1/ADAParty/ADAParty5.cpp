

#include <bits/stdc++.h>
#include<vector>
#include<algorithm>
#include <numeric>
using namespace std;



long long int candies[5000000];
long long int prefixSum[5000001];
long long int maxr[5000000], minr[5000000], maxl[5000000], minl[5000000];
long long int count_array[5000000];


// long long int findPair(long long int k){
    
//     long long int i, l, sum, nPair=0;
//     vector<long long int> temp;

//     for (i=2; i<=candies.size(); i++){
//         for (l=0; l<=candies.size()-i; l++){
//             //extract seq [l:l+i]
//             temp.assign(candies.begin()+l, candies.begin()+l+i);
//             //cout << "temp:" << temp.front() << temp.back() << endl;
//             //sort, get off max, min
//             if (temp.size() <3){
//                 nPair += 1;
//             }
//             else{

//                 sort(temp.begin(), temp.end());
//                 sum = accumulate(temp.begin()+1, temp.end()-1,
//                                decltype(temp)::value_type(0));
                
//                 if (sum % k == 0){
//                     nPair +=1;
//                 }

//             }
//         }
//     }


//     return nPair;
//     }


void combine(long long int& nPair, long long int& k, long long int st, 
                                            long long int mid, long long int ed){
    /*
    to find     ith prefixSum: prefixSum[i+1]
    to find (i-1)th prefixSum: prefixSum[i]
     */
    // cout <<"=======" << "\n";
    // cout << st << "-" << mid << "-" << ed << "\n";
    int l, r, it, c, all_r, mx_r, mn_r;
    it = 0;
    vector <int> clean_count;

    minl[mid] = maxl[mid] = candies[mid];
    for (l=mid-1; l>=st; l--){
        minl[l] = min(minl[l+1], candies[l]);
        maxl[l] = max(maxl[l+1], candies[l]);
    }


    minr[mid+1] = maxr[mid+1] = candies[mid+1];
    for (r = mid+2; r <= ed; r++){
        minr[r] = min(minr[r-1], candies[r]);
        maxr[r] = max(maxr[r-1], candies[r]);
    }

    // for (r=mid+1; r<=ed; r++){
    //     cout << "[" <<minr[r] << ", "<< maxr[r] << "],  ";
    // }
    // cout << endl;


    // for (l=mid; l>=st; l--){
    //     cout << "[" << minl[l] << ", "<< maxl[l] << " ],  ";
    // }
    // cout << endl;


    //===================================================================
    //case 1  max, min |
    r = mid; 
    for (l = mid; l >= st; l--){
        // cout << "l:" << l << endl;
        while (r+1 <=ed && minl[l] < minr[r+1] && maxr[r+1] < maxl[l]){
            count_array[ prefixSum[r+2] % k ]++;
            
            
            // record which to clean 
            // vector<int>::iterator it = find(clean_count.begin(), clean_count.end(), prefixSum[r+2] % k);
            // if (it == clean_count.end()){
            //     clean_count.push_back(prefixSum[r+2] % k);
            // }
            clean_count.push_back(prefixSum[r+2] % k);
            
            r++;
        }
        nPair += count_array[ (prefixSum[l] + minl[l] + maxl[l]) % k ];

    }

    for (c=it; c < clean_count.size(); c++){
        if (clean_count[c] >= 0){
            count_array[clean_count[c]] = 0;
        }
        it++;
    }  

    // while (!clean_count.empty()){
    //     if (clean_count.back() >=0){
    //         count_array[clean_count.back()] = 0;
    //     }
        
    //     clean_count.pop_back();
    // }
    // cout << "====case 1: " << nPair << endl;


    //===================================================================
    //case 2  min | max
    mn_r = mid, mx_r = mid + 1;
    // [mx_r, r] & [mid + 1, mn_r]
    for (l = mid; l >= st; l--) {
        // cout << "l:" << l << endl;
        // move mx_r
        while (mx_r != ed + 1 && maxl[l] > maxr[mx_r]) {
            
            // max no longer satisfied
            if (mx_r <= mn_r) {
                // cout << "max not satisfied, rm:" << mx_r << endl;
                count_array[(prefixSum[mx_r+1] - maxr[mx_r]) % k]--;
                // cout << "count_array:" << count_array[0] << "," << count_array[1] << "," << count_array[2] << endl;

            }
            mx_r++;
        }
        // move mn_r
        while (mn_r != ed && minr[mn_r + 1] > minl[l]) {
            // min is satisfied
            mn_r++;
            if (mx_r <= mn_r) {
                // cout << "min satisfied, add:" << mx_r << " : " <<(prefixSum[mn_r+1] - maxr[mn_r]) % k  << endl;
                count_array[(prefixSum[mn_r+1] - maxr[mn_r]) % k]++;
                // cout << "count_array:" << count_array[0] << "," << count_array[1] << "," << count_array[2] << endl;

                //check where to clean
                // vector<int>::iterator it = find(clean_count.begin(), clean_count.end(), (prefixSum[mn_r+1] - maxr[mn_r]) % k);
                // if (it == clean_count.end()){
                //     clean_count.push_back((prefixSum[mn_r+1] - maxr[mn_r]) % k);
                // }
                clean_count.push_back((prefixSum[mn_r+1] - maxr[mn_r]) % k);
                
            }
        }
        // cout << "choose: " << (prefixSum[l] + minl[l]) % k << endl;
        nPair += count_array[(prefixSum[l] + minl[l]) % k];
        // cout << "nPair:" << nPair << endl;
    }

    // while (!clean_count.empty()){
    //     if (clean_count.back() >=0){
    //         count_array[clean_count.back()] = 0;
    //     }
        
    //     clean_count.pop_back();
    // }
    for (c=it; c < clean_count.size(); c++){
        if (clean_count[c] >= 0){
            count_array[clean_count[c]] = 0;
        }
        it++;
    }    
    // cout << "====case 2: " << nPair << endl;

    // ===================================================================
    //case 4  max | min
    mn_r = mid + 1, mx_r = mid;
    // [mx_r, r] & [mid + 1, mn_r]
    for (l = mid; l >= st; l--) {
        // cout << "l:" << l << endl;
        // move mn_r
        while (mn_r != ed + 1 && minl[l] < minr[mn_r]) {
            
            // min no longer satisfied
            if (mn_r <= mx_r) {
                // cout << "min not satisfied, rm:" << mn_r << endl;
                count_array[(prefixSum[mn_r+1] - minr[mn_r]) % k]--;
                // cout << "count_array:" << count_array[0] << "," << count_array[1] << "," << count_array[2] << endl;

            }
            mn_r++;
        }
        // move mx_r
        while (mx_r != ed && maxr[mx_r + 1] < maxl[l]) {
            // max is satisfied
            mx_r++;
            if (mn_r <= mx_r) {
                // cout << "max satisfied, add:" << mx_r << " : " << prefixSum[mx_r+1] << "," <<minr[mx_r] << "," << (prefixSum[mx_r+1] - minr[mx_r]) % k  << endl;
                count_array[(prefixSum[mx_r+1] - minr[mx_r]) % k]++;
                // cout << "count_array:" << count_array[0] << "," << count_array[1] << "," << count_array[2] << endl;

                //check where to clean
                // vector<int>::iterator it = find(clean_count.begin(), clean_count.end(), (prefixSum[mx_r+1] - minr[mx_r]) % k);
                // if (it == clean_count.end()){
                //     clean_count.push_back((prefixSum[mx_r+1] - minr[mx_r]) % k);
                // }
                clean_count.push_back((prefixSum[mx_r+1] - minr[mx_r]) % k);
            }
        }
        // cout << "choose: " << (prefixSum[l] + maxl[l]) % k << endl;
        nPair += count_array[(prefixSum[l] + maxl[l]) % k];
        // cout << "nPair:" << nPair << endl;
    }

    // while (!clean_count.empty()){
    //     if (clean_count.back() >=0){
    //         count_array[clean_count.back()] = 0;
    //     }
    //     clean_count.pop_back();
    // }
    for (c=it; c < clean_count.size(); c++){
        if (clean_count[c] >= 0){
            count_array[clean_count[c]] = 0;
        }
        it++;
    }  
    // cout << "====case 4: " << nPair << endl;
    




    //===================================================================
    //case 3   | max, min
    // cout << "case 3 nPair:" << nPair << endl;
    all_r = mid; mn_r = mid + 1;
    for (l = mid; l >= st; l--){
        // cout << "l: " << l << endl;

        // cout << minl[l] << "," << maxl[l]  << "," << minr[count_r+1] << "," << maxr[count_r+1] << endl;

        while (all_r + 1 <= ed){
            all_r++;
            // cout << "all_r: " << all_r+1 << endl;
            count_array[ (prefixSum[all_r+1] - minr[all_r] -maxr[all_r]) % k ]++;
            // // record which to clean 
            // vector<int>::iterator it = find(clean_count.begin(), clean_count.end(), (prefixSum[all_r+1] - minr[all_r] -maxr[all_r]) % k);
            // if (it == clean_count.end()){
            //     clean_count.push_back((prefixSum[all_r+1] - minr[all_r] -maxr[all_r]) % k);
            // }
            clean_count.push_back((prefixSum[all_r+1] - minr[all_r] -maxr[all_r]) % k);
            
        }


        while (mn_r != ed + 1){
            if ((minr[mn_r] > minl[l]) or (maxr[mn_r] < maxl[l])){
                //max or min not satisfied
                count_array[ (prefixSum[mn_r+1] - minr[mn_r] - maxr[mn_r]) % k ]--;
                mn_r++;
            }
            else{
                break;
            }
        }


        nPair += count_array[ (prefixSum[l]) % k ];
        // cout << "nPair:" << nPair <<  endl;
    }


    // while (clean_count.size() !=0){
    //     // cout << "clean: " << clean_count.back() << ", ori:" << count_array[clean_count.back()] << endl;
    //     if (clean_count.back() >=0){
    //         count_array[clean_count.back()] = 0;
    //     }
    //     clean_count.pop_back();
    // }

    for (c=it; c < clean_count.size(); c++){
        if (clean_count[c] >= 0){
            count_array[clean_count[c]] = 0;
        }
        it++;
    }  

    // for (int c = 0; c < k; c++){
    //     count_array[c] = 0;
    // }

    // cout << "====case 3: " << nPair << endl;


}




void getPair(long long int& nPair, long long int& k, 
                    long long int st, long long int ed){
    
    // if (ed-st < k or ed-st < 3){
    if (ed==st){
        return;
    }
    
    long long int mid = (st+ed)/2;
    getPair(nPair, k, st, mid);
    getPair(nPair, k, mid+1, ed);

    combine(nPair, k, st, mid, ed);

}



int main(){ 
    
    cin.tie(nullptr), cout.sync_with_stdio(0);

    long long int n, k, i, value, nPair=0; 
    
    cin >> n >> k;          

    for (i=0; i<n; i++){
            cin >> value;
            candies[i] = value;
            prefixSum[i+1]=prefixSum[i] + candies[i];
            
    }

    // for (i=0; i<n; i++){
    //     cout << candies[i] << " ";
    // }
    // cout << "\n";

    // for (i=0; i<n; i++){
    //     cout << prefixSum[i+1] << " ";
    // }
    // cout << "\n";

    for (i=0; i<k; i++){
        count_array[i]=0;
        
    }

    // if (n<=200 && k <= 200){
    //     nPair = findPair(candies, k);
    // }
    // else{
    //     getPair(candies, prefixSum, nPair, k, 0, n-1);
    // }
    getPair(nPair, k, 0, n-1);
    
    cout << nPair << endl;
    return 0; 
    }
