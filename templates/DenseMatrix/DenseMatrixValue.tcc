#include "../../headers/DenseMatrix/DenseMatrixValue.hpp"
#include <stdexcept>

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue(
    const typename SquareMatrixValueSelector::SquareMatrixSelectorTemplate& s) :
    SquareMatrixValue(s.idx(), s.pidx(), s.set(), s.modifyable(), s.matrix()) {}

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue(
    size_t row, size_t column, bool modifyable, const DenseMatrix *m) :
    SquareMatrixValue(column, row, set_mode::row, modifyable, m) {}

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue& DenseMatrixValue<T>::perform_operation(
    void(*op)(Value&, const Value&), const Value& val)
{
    Value &m_val;

    if (!SquareMatrixValue::m_modifyable)
        throw std::logic_error("Could not modify constant value");
    m_val = SquareMatrixValue::matrix()->m_matrix[m_row][m_column];
    op(m_val, val);
    if ((m_val - T()) <= SquareMatrixValue::matrix()->get_precision())
        m_val = 0;
}