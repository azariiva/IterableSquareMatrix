#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

#include "DenseMatrixValue.hpp"
#include "../SquareMatrix/SquareMatrix.hpp"

template <typename T> class DenseMatrixValue;

template <typename T> class DenseMatrix : public SquareMatrix<T,DenseMatrixValue<T> >
{
public:
    typedef ::SquareMatrix<T,DenseMatrixValue<T> > SquareMatrix;
    typedef typename SquareMatrix::SquareMatrixSelector SquareMatrixSelector;

private:
    typedef typename SquareMatrix::Value Value;

public:
    DenseMatrix(size_t, size_t);
    DenseMatrix(const DenseMatrix&);
    // DenseMatrix(const typename SquareMatrix::SquareMatrixSelector&);
    ~DenseMatrix();
    DenseMatrix& operator=(const DenseMatrix&);
    // DenseMatrix& operator=(const typename SquareMatrix::SquareMatrixSelector&);
    inline const Value& get(size_t, size_t) const;
    inline Value& get(size_t, size_t);
    DenseMatrix dot(const DenseMatrix&);

private:
    DenseMatrix& perform_operation(void (*op)(Value&, const Value&), const SquareMatrix& m);
    DenseMatrix& perform_operation(void (*op)(Value&, const Value&), const Value& val);

private:
    Value **m_matrix;
};

#include "../../templates/DenseMatrix/DenseMatrix.tcc"

#endif