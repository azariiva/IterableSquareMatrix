#include "SquareMatrixRowValueSelector.hpp"
#include <stdexcept>

template <typename val_T, typename matrix_T>
SquareMatrixRowValueSelector<val_T,matrix_T>::SquareMatrixRowValueSelector(
    const RowSelector &row) : Selector(row.m_matrix, row.m_modifyable, 0)
{
    m_row = row.m_idx;
}

template <typename val_T, typename matrix_T>
SquareMatrixRowValueSelector<val_T,matrix_T>::SquareMatrixRowValueSelector(
    const Matrix *matrix, bool modifyable, size_t row) : Selector(matrix, modifyable, 0)
{
    m_row = row;
}

template <typename val_T, typename matrix_T>
SquareMatrixRowValueSelector<val_T,matrix_T>::SquareMatrixRowValueSelector(
    const SquareMatrixRowValueSelector& row) : Selector(row)
{
    m_row = row.m_row;
}

template <typename val_T, typename matrix_T>
void SquareMatrixRowValueSelector<val_T,matrix_T>::check_idx() const
{
    if (Selector::m_idx >= Selector::m_matrix->num_columns())
        throw std::out_of_range("out of bounds exception(num_columns exceeded)");
}