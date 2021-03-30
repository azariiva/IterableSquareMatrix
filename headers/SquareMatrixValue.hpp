#ifndef SQUARE_MATRIX_VALUE_HPP
#define SQUARE_MATRIX_VALUE_HPP

#include "SquareMatrixRowSelector.hpp"
#include "SquareMatrix.hpp"

template <typename matrix_T> class SquareMatrixRowValueSelector;
template <typename matrix_T> class SquareMatrixColumnValueSelector;

template <typename matrix_T>
class SquareMatrixValue
{
public:
    SquareMatrixValue(const SquareMatrixRowValueSelector<matrix_T>&);
    SquareMatrixValue(const SquareMatrixColumnValueSelector<matrix_T>&);

    virtual SquareMatrixValue& operator=(const matrix_T&) = 0;
    virtual SquareMatrixValue& operator=(const SquareMatrixValue&) = 0;

    virtual SquareMatrixValue& perform_operation(void (*)(matrix_T&, const matrix_T&), const matrix_T&) = 0;
    SquareMatrixValue& operator+=(const matrix_T&);
    SquareMatrixValue& operator-=(const matrix_T&);
    SquareMatrixValue& operator*=(const matrix_T&);
    SquareMatrixValue& operator/=(const matrix_T&);

    bool operator==(const matrix_T&) const;
    bool operator==(const SquareMatrixValue&) const;
    bool operator!=(const matrix_T&) const;
    bool operator!=(const SquareMatrixValue&) const;

    virtual operator matrix_T() const = 0;

private:
    size_t m_row;
    size_t m_column;
    bool m_modifyable;
    const SquareMatrix<matrix_T> *m_matrix;
};

#endif