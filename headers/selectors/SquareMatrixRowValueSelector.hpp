#ifndef SQUARE_MATRIX_ROW_VALUE_SELECTOR
#define SQUARE_MATRIX_ROW_VALUE_SELECTOR

#include "SquareMatrixValue.hpp"
#include "SquareMatrixRowSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename val_T, typename matrix_T> class SquareMatrixValue;
template <typename val_T, typename matrix_T> class SquareMatrixRowSelector;

template <typename val_T, typename matrix_T> class SquareMatrixRowValueSelector : public SquareMatrixSelector<matrix_T, SquareMatrixValue<matrix_T> >
{
private:
    typedef val_T Value;
    typedef matrix_T Matrix;
    typedef class SquareMatrixSelector<Matrix, SquareMatrixValue<Value,Matrix> > Selector;
    typedef class SquareMatrixRowSelector<Matrix> RowSelector;

public:
    SquareMatrixRowValueSelector(const RowSelector&);
    SquareMatrixRowValueSelector(const Matrix *, bool, size_t);
    SquareMatrixRowValueSelector(const SquareMatrixRowValueSelector&);
    
private:
    inline void check_idx() const;

private:
    const size_t m_row;
};

#include "SquareMatrixRowValueSelector.tcc"

#endif