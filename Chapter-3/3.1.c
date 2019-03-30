#include <time.h>
#include <stdio.h>

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while(low <= high && mid != x) {
        mid = (low + high) / 2;
        if(x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    
    return mid == x ? mid : -1; 
}

int binsearch_(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while(low <= high && mid != x) {
        mid = (low + high) / 2;
        if(x < v[mid])
            high = mid - 1;
        else if (x >= v[mid])
            low = mid + 1;
        else return mid;
    }
    
    return -1; 
}

int main(){
    unsigned size = 1000;
    int collection[size];
    for(unsigned i = i; i < size; ++i){
        collection[i] = i * size / 3;
    }
    clock_t start = clock();
    binsearch(1249, collection, size);
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

    clock_t start_ = clock();
    binsearch_(1249, collection, size);
    clock_t stop_ = clock();
    double elapsed_ = (double)(stop_ - start_) * 1000.0 / CLOCKS_PER_SEC;

    printf("Time elapsed in ms: \nwith one conditions: %f\nwith two conditions: %f\n", elapsed, elapsed_);
}