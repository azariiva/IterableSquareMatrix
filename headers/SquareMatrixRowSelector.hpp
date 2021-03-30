#ifndef SQUARE_MATRIX_ROW_SELECTOR_HPP
#define SQUARE_MATRIX_ROW_SELECTOR_HPP

#include "SquareMatrixRowValueSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename matrix_T> class SquareMatrixRowValueSelector;

template <typename matrix_T> class SquareMatrixRowSelector : public SquareMatrixSelector<matrix_T, SquareMatrixRowValueSelector<matrix_T>>
{
private:
    SquareMatrixRowSelector(const SquareMatrix<matrix_T> *, bool, size_t);
    inline void check_idx();
};

#endif