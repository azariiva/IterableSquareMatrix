#ifndef SQUARE_MATRIX_VALUE_HPP
#define SQUARE_MATRIX_VALUE_HPP

#include "SquareMatrixRowValueSelector.hpp"
#include "SquareMatrixColumnValueSelector.hpp"

template <typename val_T, typename matrix_T> class SquareMatrixRowValueSelector;
template <typename val_T, typename matrix_T> class SquareMatrixColumnValueSelector;

template <typename val_T, typename matrix_T> class SquareMatrixValue
{
private:
    typedef val_T Value;
    typedef matrix_T Matrix;
    typedef class SquareMatrixRowValueSelector<Value,Matrix> RowValueSelector;
    typedef class SquareMatrixColumnValueSelector<Value,Matrix> ColumnValueSelector;

public:
    SquareMatrixValue(const RowValueSelector&);
    SquareMatrixValue(const ColumnValueSelector&);

    virtual SquareMatrixValue& operator=(const Value&) = 0;
    virtual SquareMatrixValue& operator=(const Value&) = 0;

    virtual SquareMatrixValue& perform_operation(void (*)(Value&, const Value&), const Value&) = 0;
    SquareMatrixValue& operator+=(const Value&);
    SquareMatrixValue& operator-=(const Value&);
    SquareMatrixValue& operator*=(const Value&);
    SquareMatrixValue& operator/=(const Value&);

    bool operator==(const Value&) const;
    bool operator==(const SquareMatrixValue&) const;
    bool operator!=(const Value&) const;
    bool operator!=(const SquareMatrixValue&) const;

    virtual operator Value() const = 0;

private:
    size_t m_row;
    size_t m_column;
    bool m_modifyable;
    const Matrix *m_matrix;
};

#include "SquareMatrixValue.tcc"

#endif