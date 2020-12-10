
#include <bits/stdc++.h> 
using namespace std;
 
// Data structure for Min Heap
struct PriorityQueue 
{
private:
    // vector to store heap elements
    vector<int> A;
 
    // return parent of A[i]
    // don't call this function if i is already a root node
    int PARENT(int i){ 
        return (i - 1) / 2; 
    }
 
    // return left child of A[i]    
    int LEFT(int i){ 
        return (2 * i + 1); 
    }
 
    // return right child of A[i]    
    int RIGHT(int i){ 
        return (2 * i + 2); 
    }

    void heapify_down(int i)
    {
        // get left and right child of node at index i
        int left = LEFT(i);
        int right = RIGHT(i);
 
        int smallest = i;
 
        if (left < size() && A[left] < A[i])
            smallest = left;
 
        if (right < size() && A[right] < A[smallest])
            smallest = right;
 
        if (smallest != i) {
            swap(A[i], A[smallest]);
            heapify_down(smallest);
        }
    }
 
    // Recursive Heapify-up algorithm
    void heapify_up(int i)
    {
        if (i && A[PARENT(i)] > A[i]){
            swap(A[i], A[PARENT(i)]);
            heapify_up(PARENT(i));
        }
    }
    
public:
    unsigned int size(){
        return A.size();
    }
 
    bool empty(){
        return size() == 0;
    }
    
    // insert key into the heap
    void push(int key)
    {
        A.push_back(key);
        int index = size() - 1;
        heapify_up(index);
    }
 
    // function to remove element with lowest priority (present at root)
    void pop(){
        A[0] = A.back();
        A.pop_back();
        heapify_down(0);
        
    }
 
    // function to return element with lowest priority (present at root)
    int top(){
        return A.at(0);       
    }

    void decreaseKey(int i, int new_val){
        A[i] = new_val; 
        while (i != 0 && A[PARENT(i)] > A[i]){ 
            swap(A[i], A[PARENT(i)]);
            i = PARENT(i); 
        } 
    } 
};
 
// Min Heap C++ Implementation
int main()
{
    PriorityQueue pq;
    
    // Note - Priority is decided by element's value
    
    pq.push(3);
    pq.push(2);
    pq.push(15);
    pq.push(11);
    
    cout << "Size is " << pq.size() << endl;    
    
    cout << pq.top() << " ";
    pq.pop();
 
    cout << pq.top() << " ";
    pq.pop();

    pq.decreaseKey(11, 1);

    cout << pq.top() << " ";
    pq.pop();
    cout << endl << std::boolalpha << pq.empty();

 
    return 0;
}


