//
// Created by Ray Ap on 2021/7/19.
//

#include "Strassen.h"

int main() {
    Strassen<int> s1(5, 5);
    Strassen<int> s2(5, 5);
    s1.print(s1 + s2);
    return 0;
}