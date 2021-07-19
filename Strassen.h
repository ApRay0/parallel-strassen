//
// Created by Ray Ap on 2021/7/19.
//

#ifndef STRASSEN_H
#define STRASSEN_H

#include "iostream"

template <class T>
class Strassen{
public:
    Strassen(int _row_size, int _col_size){
        this->row_size = _row_size;
        this->col_size = _col_size;
        this->size = _row_size * _col_size;
        this->matrix = new T[this->size] ();
    };

    Strassen operator+(const Strassen<T>& rhs){
        Strassen<T> res(rhs.row_size, rhs.col_size);
        for (int i = 0; i < this->size; i++) {
            res.matrix[i] = this->matrix[i] + rhs.matrix[i];
        }
        return res;
    };
//    Strassen operator * (const Strassen<T>& rhs);

    void print(const Strassen<T>& s){
        for (int i = 0; i < s.row_size; i++) {
            for (int j = 0; j < s.col_size; j++) {
                std::cout << s.matrix[i * s.col_size + j] << " ";
            }
            std::cout << "\n";
        }
    };


private:
    int row_size;
    int col_size;
    int size;
    T* matrix;

};

#endif //STRASSEN_H
