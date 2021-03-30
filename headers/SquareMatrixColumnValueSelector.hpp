#ifndef SQUARE_MATRIX_COLUMN_VALUE_SELECTOR
#define SQUARE_MATRIX_COLUMN_VALUE_SELECTOR

#include "SquareMatrixValue.hpp"
#include "SquareMatrixColumnSelector.hpp"
#include "SquareMatrixSelector.hpp"
#include <cstddef>

template <typename matrix_T> class SquareMatrixValue;
template <typename matrix_T> class SquareMatrixColumnSelector;
template <typename matrix_T, typename deref_T> class SquareMatrixSelector;

template <typename matrix_T> class SquareMatrixColumnValueSelector : public SquareMatrixSelector<matrix_T, SquareMatrixValue<matrix_T>>
{
public:
    SquareMatrixColumnValueSelector(const SquareMatrixColumnSelector<matrix_T>&);

private:
    inline void check_idx() const;

private:
    const size_t m_column;
};

#endif