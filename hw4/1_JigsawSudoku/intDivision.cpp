// C++ implementation of the approach 
#include <bits/stdc++.h> 
using namespace std; 

vector< vector<int>> possible_divisions;

void partitions(int target, int curr, int* array, int idx, int& quota)
{
    bool valid = true;
    vector<int> a_set;
    if (curr + array[idx] == target)
    {
        
        for (int i=0; i <= idx; i++){
            // cout << array[i] << " ";
            if (array[i] > 9){
                valid = false;
                break;
            }
            else{
                a_set.push_back(array[i]);
            }
        }

        if (valid && a_set.size() == quota){
            possible_divisions.push_back(a_set);
        }

        // cout << endl;       
        return;
    }
    else if (curr + array[idx] > target)
    {
        return;
    }
    else
    {
        for(int i = array[idx]+1; i < target; i++)
        {
            array[idx+1] = i;
            partitions(target, curr + array[idx], array, idx+1, quota);
        }
    }
}

int main(){
    int array[100];
    int N = 15;
    int quota = 3;
    for(int i = 1; i <= N; i++)
    {
        array[0] = i;
        partitions(N, 0, array, 0, quota);
    }

    for (int i = 0; i < possible_divisions.size(); i++){
        
        for (int j = 0; j < possible_divisions[i].size(); j++){
            cout << possible_divisions[i][j] << " ";
        }
        
        cout << "\n";
    }

}