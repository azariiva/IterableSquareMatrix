#ifndef SQUARE_MATRIX_ROW_VALUE_SELECTOR
#define SQUARE_MATRIX_ROW_VALUE_SELECTOR

#include "SquareMatrixValue.hpp"
#include "SquareMatrixRowSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename matrix_T> class SquareMatrixValue;
template <typename matrix_T> class SquareMatrixRowSelector;

template <typename matrix_T> class SquareMatrixRowValueSelector : public SquareMatrixSelector<matrix_T, SquareMatrixValue<matrix_T>>
{
public:
    SquareMatrixRowValueSelector(const SquareMatrixRowSelector<matrix_T>&);

private:
    inline void check_idx() const;

private:
    const size_t m_row;
};

#endif