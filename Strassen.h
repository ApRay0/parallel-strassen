//
// Created by Ray Ap on 2021/7/19.
//

#ifndef STRASSEN_H
#define STRASSEN_H

#include "iostream"
#define THRESHOLD 16


template <class T>
class Strassen{
public:
    T* matrix;
    int row_size;
    int col_size;
    int size;

    Strassen(int _row_size, int _col_size){
        this->row_size = _row_size;
        this->col_size = _col_size;
        this->size = _row_size * _col_size;
        this->matrix = new T[this->size] ();
    };

    inline Strassen operator+(const Strassen<T>& rhs){
        Strassen<T> res(rhs.row_size, rhs.col_size);
        for (int i = 0; i < this->size; i++) {
            res.matrix[i] = this->matrix[i] + rhs.matrix[i];
        }
        return res;
    };

    inline Strassen operator-(const Strassen<T>& rhs){
        Strassen<T> res(rhs.row_size, rhs.col_size);
        for (int i = 0; i < this->size; i++) {
            res.matrix[i] = this->matrix[i] - rhs.matrix[i];
        }
        return res;
    };

    inline Strassen operator*(const Strassen<T>& rhs){
        Strassen<T> res(this->row_size, rhs.col_size);
        for (int i = 0; i < this->row_size; i++) {
            for (int j = 0; j < rhs.col_size; j++) {
                for (int k = 0; k < this->col_size; k++) {
                    res.matrix[i * rhs.col_size + j] += this->matrix[i * this->col_size + k] * rhs.matrix[k * rhs.col_size + j];
                }
            }
        }
        return res;
    };


    void random_init() {
        for (int i = 0; i < this->size; i++) {
            this->matrix[i] = rand() % 10;
        }
    };

    inline void null_init() {
        memset(this->matrix, 0, size * sizeof(T));
    }

    inline int get_row_size() {
        return this->row_size;
    };

    inline int get_col_size() {
        return this->col_size;
    };

    void print() {
        for (int i = 0; i < this->row_size; i++) {
            for (int j = 0; j < this->col_size; j++) {
                std::cout << this->matrix[i * this->col_size + j] << " ";
            }
            std::cout << "\n";
        }
    }

    inline void fill11(const Strassen<T>& A) {
        for (int i = 0; i < A.row_size; i++) {
            for (int j = 0; j < A.col_size; j++) {
                this->matrix[i * this->col_size + j] = A[i * A.col_size + j];
            }
        }
    }

    inline void fill12(const Strassen<T>& A) {
        for (int i = 0; i < A.row_size; i++) {
            for (int j = 0; j < A.col_size; j++) {
                this->matrix[i * this->col_size + j + A.col_size] = A[i * A.col_size + j];
            }
        }
    }

    inline void fill21(const Strassen<T>& A) {
        for (int i = 0; i < A.row_size; i++) {
            for (int j = 0; j < A.col_size; j++) {
                this->matrix[(i + A.row_size) * this->col_size + j] = A[i * A.col_size + j];
            }
        }
    }

    inline void fill22(const Strassen<T>& A) {
        for (int i = 0; i < A.row_size; i++) {
            for (int j = 0; j < A.col_size; j++) {
                this->matrix[(i + A.row_size) * this->col_size + j + A.col_size] = A[i * A.col_size + j];
            }
        }
    }

    inline void sub_submatrix(Strassen<T>& C, const Strassen<T>& A, std::pair<int, int> pos_of_A, const Strassen<T>& B, std::pair<int, int> pos_of_B) {
        int row_A = pos_of_A.first - 1;
        int col_A = pos_of_A.second - 1;
        int row_B = pos_of_B.first - 1;
        int col_B = pos_of_B.second - 1;
        for (int i = 0; i < C.row_size; i++) {
            for (int j = 0; j < C.col_size; j++) {
                C.matrix[i * C.row_size + j] = A.matrix[(i + row_A * C.row_size) * A.col_size + (j + col_A * C.col_size)]
                                             - B.matrix[(i + row_B * C.row_size) * B.col_size + (j + col_B * C.col_size)];
            }
        }
    }

    inline void add_submatrix(Strassen<T>& C, const Strassen<T>& A, std::pair<int, int> pos_of_A, const Strassen<T>& B, std::pair<int, int> pos_of_B) {
        int row_A = pos_of_A.first - 1;
        int col_A = pos_of_A.second - 1;
        int row_B = pos_of_B.first - 1;
        int col_B = pos_of_B.second - 1;
        for (int i = 0; i < C.row_size; i++) {
            for (int j = 0; j < C.col_size; j++) {
                C.matrix[i * C.row_size + j] = A.matrix[(i + row_A * C.row_size) * A.col_size + (j + col_A * C.col_size)]
                                               + B.matrix[(i + row_B * C.row_size) * B.col_size + (j + col_B * C.col_size)];
            }
        }
    }

//    void normal_mutiple(const Strassen<T>& A, const Strassen<T>& B, Strassen<T>& C) {
//        C.null_init();
//        for (int i = 0; i < A.row_size; i++) {
//            for (int j = 0; j < B.col_size; j++) {
//                for (int k = 0; k < A.col_size; k++) {
//                    C.matrix[i * B.col_size + j] += A.matrix[i * A.col_size + k] * B.matrix[k * B.col_size + j];
//                }
//            }
//        }
//    }

    //usage: C = A * B
    Strassen strassen_multiple(Strassen<T>& C, const Strassen<T>& A, const Strassen<T>& B) {
        Strassen<T> res(A.row_size, B.col_size);
        if (A.col_size < THRESHOLD || B.row_size < THRESHOLD || B.col_size < THRESHOLD) {
            return A * B;
        }
        //temporary matrix
        Strassen<T> X1(A.row_size / 2, A.col_size / 2), X2(A.col_size / 2, B.col_size / 2);
        //S3 = A11 - A21    X1
        sub_submatrix(X1, A, {1, 1}, A, {2,1}, X1);
        //T3 = B22 - B12    X2
        sub_submatrix(X2, B, {2, 2}, B, {1, 2}, X2);
        //P7 = S3 * T3      C21

        //S1 = A21 + A22    X1
        add_submatrix(X1, A, {2,1}, A, {2,2}, X1);
        //T1 = B12 - B11    X2
        sub_submatrix(X2, B, {1,2}, B, {1, 1}, X2);
        //P5 = S1 * T1      C22

        //S2 = S1 - A11     X1
        sub_submatrix(X1, X1, {1, 1}, A, {1, 1});
        //T2 = B22 - T1     X2
        sub_submatrix(X2, B, {2,2}, X2, {1, 1});
        //P6 = S2 * T 2     C12

        //S4 = A12 - S2     X1
        sub_submatrix(X1, A, {1, 2}, X1, {1, 1});
        //P3 = S4 * B22     C11

        //P1 = A11 * B11    X1

        //U2 = P1 + P6      C12

        //U3 = P1 + P6      C21

        //U4 = U2 + P5      C12

        //U7 = U3 + P5      C22

        //U5 = U4 + P3      C12

        //T4 = T2 - B21     X2

        //P4 = A22 * T4     C11

        //U6 = U3 - P4      C21

        //P2 = A12 * B21    C11

        //U1 = P1 + P2      C11

        return res;
    }


};



#endif //STRASSEN_H
