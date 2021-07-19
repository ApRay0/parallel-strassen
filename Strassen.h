//
// Created by Ray Ap on 2021/7/19.
//

#ifndef STRASSEN_H
#define STRASSEN_H

template <class T>
class Strassen{
public:
    Strassen(int _row_size, int _col_size);

    Strassen operator+(const Strassen<T>& rhs);
//    Strassen operator * (const Strassen<T>& rhs);

    void print(const Strassen<T>& s);


private:
    int row_size;
    int col_size;
    int size;
    T* matrix;

};

#endif //算法_STRASSEN_H
