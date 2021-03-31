#ifndef SQUARE_MATRIX_COLUMN_SELECTOR
#define SQUARE_MATRIX_COLUMN_SELECTOR

#include "SquareMatrixColumnValueSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename val_T, typename matrix_T> class SquareMatrixColumnValueSelector;

template <typename val_T, typename matrix_T> class SquareMatrixColumnSelector : public SquareMatrixSelector<matrix_T, SquareMatrixColumnValueSelector<val_T,matrix_T> >
{
private:
    typedef val_T Value;
    typedef matrix_T Matrix;
    typedef class SquareMatrixSelector<Matrix,SquareMatrixColumnValueSelector<Value,Matrix> > Selector;

public:
    SquareMatrixColumnSelector(const Matrix *, bool, size_t);
    SquareMatrixColumnSelector(const SquareMatrixColumnSelector&);

private:
    inline void check_idx();
};

#include "SquareMatrixColumnSelector.tcc"

#endif