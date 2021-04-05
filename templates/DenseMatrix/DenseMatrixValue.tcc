#include "../../headers/DenseMatrix/DenseMatrixValue.hpp"
#include <cmath>

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue(
    const typename SquareMatrixValueSelector::SquareMatrixSelectorTemplate& s) :
    SquareMatrixValue(s.idx(), s.pidx(), s.set(), s.modifyable(), s.matrix()) {}

template <typename T>
DenseMatrixValue<T>::DenseMatrixValue(
    size_t row, size_t column, bool modifyable, const DenseMatrix *m) :
    SquareMatrixValue(column, row, set_mode::row, modifyable, m) {}

template <typename T>
DenseMatrixValue<T>::operator Value() const
{
    return SquareMatrixValue::m_matrix->get(SquareMatrixValue::m_row, SquareMatrixValue::m_column);
}

template <typename T>
typename DenseMatrixValue<T>::SquareMatrixValue& 
DenseMatrixValue<T>::perform_operation(
    void (*op)(Value&, const Value&), const Value& val)
{
    Value m_val;

    if (SquareMatrixValue::m_modifyable == false)
        throw std::logic_error("Could not modify constant value");
    m_val = static_cast<DenseMatrix *>(SquareMatrixValue::m_matrix)->m_matrix[SquareMatrixValue::m_row][SquareMatrixValue::m_column];
    op(m_val, val);
    if (abs(m_val - Value()) <= SquareMatrixValue::m_matrix->get_precision())
        m_val = 0;
    return *this;
}

template <typename T>
typename DenseMatrixValue<T>::SquareMatrixValue& DenseMatrixValue<T>::operator=(const Value& val)
{
    if (SquareMatrixValue::m_modifyable == false)
        throw std::logic_error("Could not modify constant value");
    if (abs(val - Value()) > SquareMatrixValue::m_matrix->get_precision())
        SquareMatrixValue::m_matrix->set(SquareMatrixValue::m_row, SquareMatrixValue::m_column, val);
    return *this;
}