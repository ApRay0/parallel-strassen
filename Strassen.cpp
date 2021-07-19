//
// Created by Ray Ap on 2021/7/19.
//

#include "Strassen.h"
#include "iostream"


template <class T>
Strassen<T>::Strassen(int _row_size, int _col_size) {
    this->row_size = _row_size;
    this->col_size = _col_size;
    this->size = _row_size * _col_size;
    this->matrix = new (T[size]);
}

template <class T>
Strassen<T> Strassen<T>::operator+(const Strassen<T> &rhs) {
    Strassen<T> res(rhs.row_size, rhs.col_size);
    for (int i = 0; i < size; i++) {
        res[i] = this->matrix[i] + rhs.matrix[i];
    }
    return res;
}

template <class T>
void Strassen<T>::print(const Strassen<T> &s) {
    for (int i = 0; i < s.row_size; i++) {
        for (int j = 0; j < s.col_size; j++) {
            std::cout << s[i * col_size + j] << "\n";
        }
        std::cout << "\n";
    }
}