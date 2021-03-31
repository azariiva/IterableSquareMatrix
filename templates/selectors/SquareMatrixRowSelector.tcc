#include "SquareMatrixRowSelector.hpp"
#include <stdexcept>

template <typename val_T, typename matrix_T>
SquareMatrixRowSelector<val_T,matrix_T>::SquareMatrixRowSelector(
    const Matrix *matrix, bool modifyable, size_t idx) : 
    Selector(matrix, modifyable, idx) {}

template <typename val_T, typename matrix_T>
SquareMatrixRowSelector<val_T,matrix_T>::SquareMatrixRowSelector(
    const SquareMatrixRowSelector& selector) : 
    Selector(selector) {}

template <typename val_T, typename matrix_T>
void SquareMatrixRowSelector<val_T,matrix_T>::check_idx()
{
    if (Selector::m_idx >= Selector::m_matrix->num_rows())
        throw std::out_of_range("out of bounds exception(num_rows exceeded)");
}