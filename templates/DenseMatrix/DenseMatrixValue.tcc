#include "../../headers/DenseMatrix/DenseMatrixValue.hpp"

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue(
    const typename SquareMatrixValueSelector::SquareMatrixSelectorTemplate& s) :
    SquareMatrixValue(s.idx(), s.pidx(), s.set(), s.modifyable(), s.matrix()) {}