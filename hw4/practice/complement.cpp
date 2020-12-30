// Reference: http://www.cplusplus.com/reference/algorithm/set_difference/



#include <bits/stdc++.h> 
using namespace std; 




int main() {

    vector<int> v1 {1,2,3,4,5,6,7,8,9};
    vector<int> v2 {1,2,4,5};
    vector<int> diff;
    //not need to sort since it already sorted
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                    inserter(diff, diff.begin()));

    for (auto i : diff) cout << i << ' ';
    cout << '\n';
}
