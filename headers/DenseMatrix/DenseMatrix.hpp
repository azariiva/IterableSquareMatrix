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
    typedef typename SquareMatrix::SquareMatrixSelectorTemplate SquareMatrixSelectorTemplate;
    typedef typename SquareMatrix::Value Value;
    friend DenseMatrixValue<T>;
    
public:
    DenseMatrix(size_t, size_t);
    DenseMatrix(const DenseMatrix&);
    DenseMatrix(const SquareMatrixSelectorTemplate&);
    ~DenseMatrix();
    DenseMatrix& operator=(const DenseMatrix&);
    DenseMatrix& operator=(const SquareMatrixSelectorTemplate&);
    inline const Value& get(size_t, size_t) const;
    inline DenseMatrixValue<T> get(size_t, size_t);
    DenseMatrix dot(const DenseMatrix&) const;

private:
    DenseMatrix& perform_operation(void (*op)(Value&, const Value&), const SquareMatrix& m);
    DenseMatrix& perform_operation(void (*op)(Value&, const Value&), const Value& val);

private:
    Value **m_matrix;
};

template <typename T>
DenseMatrix<T> operator+(const typename DenseMatrix<T>::SquareMatrix&, const typename DenseMatrix<T>::SquareMatrix&);
template <typename T>
DenseMatrix<T> operator-(const typename DenseMatrix<T>::SquareMatrix&, const typename DenseMatrix<T>::SquareMatrix&);
template <typename T>
DenseMatrix<T> operator*(const typename DenseMatrix<T>::SquareMatrix&, const typename DenseMatrix<T>::SquareMatrix&);
template <typename T>
DenseMatrix<T> operator/(const typename DenseMatrix<T>::SquareMatrix&, const typename DenseMatrix<T>::SquareMatrix&);
template <typename T>
DenseMatrix<T> dot(const typename DenseMatrix<T>::SquareMatrix&, const typename DenseMatrix<T>::SquareMatrix&);

// TODO: High test neccesity
template <typename T>
DenseMatrix<T> operator*(const typename DenseMatrix<T>::SquareMatrix&, const T&);
template <typename T>
DenseMatrix<T> operator*(const T&, const typename DenseMatrix<T>::SquareMatrix&);
template <typename T>
DenseMatrix<T> operator/(const typename DenseMatrix<T>::SquareMatrix&, const T&);

#include "../../templates/DenseMatrix/DenseMatrix.tcc"

#endif