#include "../../headers/DenseMatrix/DenseMatrixValue.hpp"

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue(
    const typename SquareMatrixValueSelector::SquareMatrixSelectorTemplate& s) :
    SquareMatrixValue(s.idx(), s.pidx(), s.set(), s.modifyable(), s.matrix()) {}

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue(
    size_t row, size_t column, bool modifyable, const DenseMatrix *m) :
    SquareMatrixValue(column, row, set_mode::row, modifyable, m) {}