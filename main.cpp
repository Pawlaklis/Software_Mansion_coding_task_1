#include <iostream>
#include <algorithm>
#include <vector>

void generatePrime(bool *isPrime, int size){
    for (int i = 2; i < size; ++i) {
        isPrime[i] = true;
    }
    for (int i = 2; i * i <= size; ++i) {
        if (isPrime[i]){
            for (int j = i*i; j <= size; j = i + j) {
                isPrime[j] = false;
            }
        }
    }
}

int binsearch(int *array, int b, int n, int k){
    if (n < b)
        return -1;
    if (array[b+(n-b)/2] == k)
        return b+(n-b)/2;
    else if (array[b+(n-b)/2] > k)
        return binsearch(array, b, b+(n-b)/2 - 1, k);
    return binsearch(array, b+(n-b)/2 + 1, n, k);

}

std::vector<int> program(int *A, int *B, int sizeA, int sizeB){
    std::sort(B, B + sizeB);

    int max = B[sizeB - 1];
    bool isPrime[max];

    generatePrime(isPrime, max);

    int howManySize = 0;
    int howMany[sizeB];

    int strike = 1;
    for (int i = 0; i < sizeB - 1; ++i) {
        if (B[i] != B[i + 1]){
            B[howManySize] = B[i];
            howMany[howManySize++] = strike;
            strike = 1;
        } else
            strike++;
    }
    B[howManySize] = B[sizeB - 1];
    howMany[howManySize++] = strike;

    std::vector<int> C;

    for (int i = 0; i < sizeA; ++i) {
        int k = binsearch(B, 0, howManySize, A[i]);
        if (k == -1){
            C.push_back(A[i]);
        } else if(!isPrime[howMany[k]]){
            C.push_back(A[i]);
        }
    }
    return C;
}


int main() {
    int A[9] = {2,3,9,2,5,1,3,7,10};
    int B[13] = {2,1,3,4,3,10,6,6,1,7,10,10,10};
    std::vector<int> C;


    C = program(A, B, 9 ,13);

    for (int i = 0; i < C.size(); ++i) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;



    return 0;
}
