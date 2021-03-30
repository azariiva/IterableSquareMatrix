#ifndef SQUARE_MATRIX_COLUMN_SELECTOR
#define SQUARE_MATRIX_COLUMN_SELECTOR

#include "SquareMatrix.hpp"
#include "SquareMatrixColumnValueSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename T> class SquareMatrix;
template <typename matrix_T> class SquareMatrixColumnValueSelector;
template <typename matrix_T, typename deref_T> class SquareMatrixSelector;

template <typename matrix_T> class SquareMatrixColumnSelector : public SquareMatrixSelector<matrix_T, SquareMatrixColumnValueSelector<matrix_T>>
{
private:
    SquareMatrixColumnSelector(const SquareMatrix<matrix_T> *, bool, size_t);
    inline void check_idx();
};

#endif