#ifndef DENSE_MATRIX_VALUE_HPP
#define DENSE_MATRIX_VALUE_HPP

#include "./DenseMatrix.hpp"
#include "../SquareMatrix/SquareMatrixValue.hpp"
#include "../SquareMatrix/SquareMatrix.hpp"
#include "../SquareMatrix/SquareMatrixSelector.hpp"

template <typename T> class DenseMatrix;

template <typename T> class DenseMatrixValue : public ::SquareMatrixValue<T,SquareMatrix<T,DenseMatrixValue<T> > >
{
private:
    typedef ::SquareMatrixValue<T,SquareMatrix<T,DenseMatrixValue<T> > > SquareMatrixValue;
    typedef typename ::DenseMatrix<T> DenseMatrix;
    typedef typename DenseMatrix::SquareMatrix::SquareMatrixValueSelector SquareMatrixValueSelector;
    typedef typename SquareMatrixValue::Value Value;

public:
    DenseMatrixValue(const typename SquareMatrixValueSelector::SquareMatrixSelectorTemplate& s);
    DenseMatrixValue(size_t, size_t, bool, const DenseMatrix *);
    inline operator Value() const;
    SquareMatrixValue& perform_operation(void (*)(Value&, const Value&), const Value&);
    SquareMatrixValue& operator=(const Value&);
};

#include "../../templates/DenseMatrix/DenseMatrixValue.tcc"

#endif