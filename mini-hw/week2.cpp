

#include<bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;




void merge(vector<int>& arr, int& count, int st, int mid, int ed){
    /*
    Merge two sorted list, and count the number of reverse pair. 
    Inside the pair, one point is from left list (arr[l]) and another point is 
    from right list (arr[r]). 
     */
    int l, r; 
    l=st; r=mid+1;  
    // Use two pointer to indecate the point that are currently discussing.
    // l for left list, r for right list.
    while (l<=mid && r<=ed){
        if (arr[l] > arr[r]){   // if arr[l] > arr[r], that means this is a reverse pair.
            /*
            because the lists are sorted, if arr[l] > arr[r],
            than arr[k]>arr[r] for all  l < k <= mid. 
             */
            count += mid-l+1;
            r++;                
        }
        else{
            l++;  // use next left point to compare.
        }
    }
    sort(arr.begin()+st,  arr.begin()+ed+1);
    return;
}

void reverseCount(vector<int>& arr, int& count, int st, int ed){
    if (st == ed){
        return;
    }
    //divide: divide the input arr into two part.
    int mid=(st+ed)/2;

    //conquer
    reverseCount(arr, count, st, mid);
    reverseCount(arr, count, mid+1, ed);

    //combine
    merge(arr, count, st, mid, ed);
    return;
}



int main(){
    int n, i, value, count=0;
    cin >> n;

    vector<int> arr;

    for (i=0; i<n; i++){
        cin >> value;
        arr.push_back(value);
    }

    reverseCount(arr, count, 0, arr.size()-1);

    cout << count << endl;
    return 0;

}