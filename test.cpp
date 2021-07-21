//
// Created by Ray Ap on 2021/7/19.
//

#include "Strassen.h"
#include "iostream"

using namespace std;

int main() {
    Strassen<int> A(4, 4);
    Strassen<int> B(2, 2);
    Strassen<int> C(2, 2);
    A.random_init();
    B.random_init();
    C.sub_submatrix(C, A, {1,2}, B, {1, 1});
    A.print();
    B.print();
    C.print();
    return 0;
}