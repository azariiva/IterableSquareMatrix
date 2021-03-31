#include "SquareMatrixColumnValueSelector.hpp"
#include <stdexcept>

template <typename val_T, typename matrix_T>
SquareMatrixColumnValueSelector<val_T,matrix_T>::SquareMatrixColumnValueSelector(
    const ColumnSelector &column) : Selector(column.m_matrix, column.m_modifyable, 0)
{
    m_column = column.m_idx;
}

template <typename val_T, typename matrix_T>
SquareMatrixColumnValueSelector<val_T,matrix_T>::SquareMatrixColumnValueSelector(
    const Matrix *matrix, bool modifyable, size_t column) : Selector(matrix, modifyable, 0)
{
    m_column = column;
}

template <typename val_T, typename matrix_T>
SquareMatrixColumnValueSelector<val_T,matrix_T>::SquareMatrixColumnValueSelector(
    const SquareMatrixColumnValueSelector& column) : Selector(column)
{
    m_column = column.m_column;
}

template <typename val_T, typename matrix_T>
void SquareMatrixColumnValueSelector<val_T,matrix_T>::check_idx() const
{
    if (Selector::m_idx >= Selector::m_matrix->num_rows())
        throw std::out_of_range("out of bounds exception(num_rows exceeded)");
}