#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

#include "DenseMatrixValue.hpp"
#include "SquareMatrix.hpp"
#include <cstddef>

template <typename T>
class DenseMatrix : public SquareMatrix<T>
{
public:
    DenseMatrix(size_t, size_t);
    DenseMatrix(const DenseMatrix&);
    ~DenseMatrix();
    DenseMatrix& operator=(const DenseMatrix&);

    const T& get(size_t, size_t) const;
    void set(size_t, size_t, const T&) const;

    bool operator==(const DenseMatrix&) const;
    bool operator!=(const DenseMatrix&) const;

private:
    DenseMatrix& perform_operation(void (*)(T&,T), const DenseMatrix&);
    DenseMatrix& perform_operation(void (*)(T&,T), const T&);

private:
    T** m_matrix = nullptr;
};

#endif