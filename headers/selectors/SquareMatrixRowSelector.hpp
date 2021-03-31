#ifndef SQUARE_MATRIX_ROW_SELECTOR_HPP
#define SQUARE_MATRIX_ROW_SELECTOR_HPP

#include "SquareMatrixRowValueSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename val_T, typename matrix_T> class SquareMatrixRowValueSelector;

template <typename val_T, typename matrix_T> class SquareMatrixRowSelector : public SquareMatrixSelector<matrix_T, SquareMatrixRowValueSelector<val_T,matrix_T> >
{
private:
    typedef val_T Value;
    typedef matrix_T Matrix;
    typedef class SquareMatrixSelector<Matrix, SquareMatrixRowValueSelector<Value,Matrix> > Selector;

public:
    SquareMatrixRowSelector(const Matrix *, bool, size_t);
    SquareMatrixRowSelector(const SquareMatrixRowSelector&);
    
private:
    inline void check_idx();
};

#include "SquareMatrixRowSelector.tcc"

#endif