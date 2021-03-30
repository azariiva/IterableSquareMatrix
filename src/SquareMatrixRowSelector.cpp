#include "SquareMatrixRowSelector.hpp"
#include <stdexcept>

template <typename matrix_T>
SquareMatrixRowSelector<matrix_T>::SquareMatrixRowSelector(
    const SquareMatrix<matrix_T> *matrix, bool modifyable,
    size_t idx) : 
    SquareMatrixSelector<matrix_T, SquareMatrixRowValueSelector>(
        matrix, modifyable, idx) {}

template <typename matrix_T>
void SquareMatrixRowSelector<matrix_T>::check_idx()
{
    if (m_idx >= m_matrix->num_rows())
        throw std::out_of_range("out of bounds exception(num_rows exceeded)");
}