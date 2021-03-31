#include "SquareMatrixValue.hpp"

template <typename val_T, typename Value>
SquareMatrixValue<val_T,Value>::SquareMatrixValue(const RowValueSelector& selector)
{
    m_row = selector.m_row;
    m_column = selector.m_idx;
    m_modifyable = selector.m_modifyable;
    m_matrix = selector.m_matrix;
}

template <typename val_T, typename Value>
SquareMatrixValue<val_T,Value>::SquareMatrixValue(const ColumnValueSelector& selector)
{
    m_column = selector.m_column;
    m_row = selector.m_idx;
    m_modifyable = selector.m_modifyable;
    m_matrix = selector.m_matrix;
}

template <typename val_T, typename Value>
SquareMatrixValue<val_T,Value>& SquareMatrixValue<val_T,Value>::operator+=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l += r;} , v);
}

template <typename val_T, typename Value>
SquareMatrixValue<val_T,Value>& SquareMatrixValue<val_T,Value>::operator-=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l -= r;} , v);
}

template <typename val_T, typename Value>
SquareMatrixValue<val_T,Value>& SquareMatrixValue<val_T,Value>::operator*=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l *= r;} , v);
}

template <typename val_T, typename Value>
SquareMatrixValue<val_T,Value>& SquareMatrixValue<val_T,Value>::operator/=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l /= r;} , v);
}

template <typename val_T, typename Value>
bool SquareMatrixValue<val_T,Value>::operator==(const Value& v) const
{
    return operator Value() == v;
}

template <typename val_T, typename Value>
bool SquareMatrixValue<val_T,Value>::operator==(const SquareMatrixValue& v) const
{
    return operator Value() == v.operator Value();
}

template <typename val_T, typename Value>
bool SquareMatrixValue<val_T,Value>::operator!=(const Value& v) const
{
    return operator Value() != v;
}

template <typename val_T, typename Value>
bool SquareMatrixValue<val_T,Value>::operator!=(const SquareMatrixValue& v) const
{
    return operator Value() != v.operator Value();
}