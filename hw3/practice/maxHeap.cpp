// code from https://www.techiedelight.com/min-heap-max-heap-implementation-c/


#include <bits/stdc++.h> 
using namespace std; 
using ll = long long;

struct maxHeap{
    private:
    
        vector <ll> A;

        ll PARENT(ll i){
            return (i-1) / 2;
        }

        ll LEFT(ll i){
            return (2 * i +1);
        }

        ll RIGHT(ll i){
            return (2 * i +2);
        }

        void heapify_down(ll i){
            ll left = LEFT(i);
            ll right  = RIGHT(i);
            ll largest = i;

            if (left < size() && A[left] > A[i])
                largest = left;
            
            if (right < size() && A[right] > A[largest])
                largest = right;
            
            if (largest != i) {
                swap(A[i], A[largest]);
                heapify_down(largest);
            }
        }    

        void  heapify_up(ll i){
            if (i && A[PARENT(i)] < A[i]){
                swap(A[i], A[PARENT(i)]);
                heapify_up(PARENT(i));
            }
        }   

    public:
        ll size(){
            return A.size();
        }

        bool empty(){
            return size() == 0;
        }

        void push(ll key){
            A.push_back(key);

            ll index = size() - 1;
            heapify_up(index);
        }

        void pop(){
            A[0] = A.back();
            A.pop_back();
            heapify_down(0);
        }

        ll top(){
            return A.at(0);
        }


        ll delete_key(ll k){
            ll r = A[k];
            A[k] = A[size() -1];          
            ll p = PARENT(k);
            if(k == 0 || A[k] < A[p])
                heapify_down(k);
            else
                heapify_up(k);
            return r;
        }

};


int main(){
    maxHeap heap;

    heap.push(3);
    heap.push(2);
    heap.push(10);

    cout << "size:" << heap.size() << "\n";



    ll r = heap.delete_key(3);
    cout << "delete " << r << "\n";
    cout << heap.top() << " ";
    heap.pop();

    heap.push(1);
    cout << heap.top() << " ";
    return 0;
}