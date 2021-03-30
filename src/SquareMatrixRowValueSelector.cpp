#include "SquareMatrixRowValueSelector.hpp"
#include <stdexcept>

template <typename matrix_T>
SquareMatrixRowValueSelector<matrix_T>::SquareMatrixRowValueSelector(
    const SquareMatrixRowSelector<matrix_T> &row_selector) : SquareMatrixSelector<matrix_T, SquareMatrixValue>(
        row_selector.m_matrix, row_selector.m_modifyable, 0)
{
    m_row = row_selector.m_idx;
}

template <typename matrix_T>
void SquareMatrixRowValueSelector<matrix_T>::check_idx() const
{
    if (m_idx >= m_matrix->num_columns())
        throw std::out_of_range("out of bounds exception(num_columns exceeded)");
}