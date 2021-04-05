#ifndef SQUARE_MATRIX_VALUE_HPP
#define SQUARE_MATRIX_VALUE_HPP

#include "./SquareMatrixSelector.hpp"
#include <cstddef>

template <typename val_T, class matrix_T> class SquareMatrixValue
{
public:
    typedef val_T Value;
    typedef matrix_T Matrix;

public:
    SquareMatrixValue(size_t, size_t, set_mode, bool, const Matrix *);
    virtual SquareMatrixValue& operator=(const Value&);
    SquareMatrixValue& operator=(const SquareMatrixValue&);

    SquareMatrixValue& operator+=(const Value&);
    SquareMatrixValue& operator-=(const Value&);
    SquareMatrixValue& operator*=(const Value&);
    SquareMatrixValue& operator/=(const Value&);

    bool operator==(const Value&) const;
    bool operator==(const SquareMatrixValue&) const;
    bool operator!=(const Value&) const;
    bool operator!=(const SquareMatrixValue&) const;

    virtual operator Value() const;

private:
    virtual SquareMatrixValue& perform_operation(void (*)(Value&, const Value&), const Value&) = 0;

protected:
    size_t m_row;
    size_t m_column;
    const bool m_modifyable;
    Matrix *const m_matrix;
};


#include "../../templates/SquareMatrix/SquareMatrixValue.tcc"

#endif