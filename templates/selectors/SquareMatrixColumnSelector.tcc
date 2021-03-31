#include "SquareMatrixColumnSelector.hpp"
#include <stdexcept>

template <typename val_T, typename matrix_T>
SquareMatrixColumnSelector<val_T,matrix_T>::SquareMatrixColumnSelector(
    const Matrix *matrix, bool modifyable, size_t idx) : 
    Selector(matrix, modifyable, idx) {}

template <typename val_T, typename matrix_T>
SquareMatrixColumnSelector<val_T,matrix_T>::SquareMatrixColumnSelector(
    const SquareMatrixColumnSelector& selector) :
    Selector(selector) {}

template <typename val_T, typename matrix_T>
void SquareMatrixColumnSelector<val_T,matrix_T>::check_idx()
{
    if (Selector::m_idx >= Selector::m_matrix->num_columns())
        throw std::out_of_range("out of bounds exception(num_columns exceeded)");
}