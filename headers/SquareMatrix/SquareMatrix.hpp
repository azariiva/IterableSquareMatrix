#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename T, typename value_T> class SquareMatrix {
protected:
    typedef T Value;

public:
    typedef ::SquareMatrixSelector<value_T,SquareMatrix> SquareMatrixSelector;
    typedef ::SquareMatrixValueSelector<value_T,SquareMatrix> SquareMatrixValueSelector;
    typedef ::SquareMatrixSelectorTemplate<SquareMatrix,SquareMatrixValueSelector> SquareMatrixSelectorTemplate;
    
public:
    SquareMatrix() {};
    SquareMatrix(size_t, size_t);
    SquareMatrix(const SquareMatrix&);
    virtual ~SquareMatrix();
    virtual SquareMatrix& operator=(const SquareMatrix&);

    virtual Value& get(size_t, size_t) = 0;
    virtual const Value& get(size_t, size_t) const = 0;
    inline void set(size_t, size_t, const Value&);

    inline size_t num_rows() const;
    inline size_t num_columns() const;

    inline SquareMatrixValueSelector operator[](size_t);
    inline SquareMatrixValueSelector operator[](size_t) const;
    inline SquareMatrixValueSelector operator*();
    inline SquareMatrixValueSelector operator*() const;
    inline SquareMatrixSelector transpose();
    inline SquareMatrixSelector transpose() const;

    /*
    ** Арифметические операции вида:
    ** SquareMatrix.op(SquareMatrix)
    */
    SquareMatrix& operator+=(const SquareMatrix&);
    SquareMatrix& operator-=(const SquareMatrix&);
    SquareMatrix& operator*=(const SquareMatrix&);
    SquareMatrix& operator/=(const SquareMatrix&);


     /*
    ** Арифметические операции вида:
    ** SquareMatrix.op(double)
    */
    SquareMatrix& operator*=(const Value&);
    SquareMatrix& operator/=(const Value&);

    virtual bool operator==(const SquareMatrix&) const;
    virtual bool operator!=(const SquareMatrix&) const;

private:
    virtual SquareMatrix& perform_operation(void (*)(Value&,const Value&), const SquareMatrix&) = 0;
    virtual SquareMatrix& perform_operation(void (*)(Value&,const Value&), const Value&) = 0;

protected:
    size_t m_num_rows;
    size_t m_num_columns;
};

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(SquareMatrix<T, value_T>& matrix, size_t idx);

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(const SquareMatrix<T, value_T>& matrix, size_t idx);

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(size_t idx, SquareMatrix<T, value_T>& matrix);

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(size_t idx, const SquareMatrix<T, value_T>& matrix);

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator-(SquareMatrix<T, value_T>& matrix, size_t idx);

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator-(const SquareMatrix<T, value_T>& matrix, size_t idx);

#include "../../templates/SquareMatrix/SquareMatrix.tcc"

#endif