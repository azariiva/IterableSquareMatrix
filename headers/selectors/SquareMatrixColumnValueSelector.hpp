#ifndef SQUARE_MATRIX_COLUMN_VALUE_SELECTOR
#define SQUARE_MATRIX_COLUMN_VALUE_SELECTOR

#include "SquareMatrixValue.hpp"
#include "SquareMatrixColumnSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename val_T, typename matrix_T> class SquareMatrixValue;
template <typename val_T, typename matrix_T> class SquareMatrixColumnSelector;

template <typename val_T, typename matrix_T> class SquareMatrixColumnValueSelector : public SquareMatrixSelector<matrix_T, SquareMatrixValue<val_T, matrix_T> >
{
private:
    typedef val_T Value;
    typedef matrix_T Matrix;
    typedef class SquareMatrixSelector<Matrix, SquareMatrixValue<Matrix> > Selector;
    typedef class SquareMatrixColumnSelector<Value,Matrix> ColumnSelector;

public:
    SquareMatrixColumnValueSelector(const ColumnSelector&);
    SquareMatrixColumnValueSelector(const Matrix *, bool, size_t);
    SquareMatrixColumnValueSelector(const SquareMatrixColumnValueSelector&);
    
private:
    inline void check_idx() const;

private:
    const size_t m_column;
};

#include "SquareMatrixColumnValueSelector.tcc"

#endif