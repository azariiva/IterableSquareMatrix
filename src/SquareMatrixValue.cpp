#include "SquareMatrixValue.hpp"

template <typename matrix_T>
SquareMatrixValue<matrix_T>::SquareMatrixValue(const SquareMatrixRowValueSelector<matrix_T>& selector)
{
    m_row = selector.m_row;
    m_column = selector.m_idx;
    m_modifyable = selector.m_modifyable;
    m_matrix = selector.m_matrix;
}

template <typename matrix_T>
SquareMatrixValue<matrix_T>::SquareMatrixValue(const SquareMatrixColumnValueSelector<matrix_T>& selector)
{
    m_column = selector.m_column;
    m_row = selector.m_idx;
    m_modifyable = selector.m_modifyable;
    m_matrix = selector.m_matrix;
}

template <typename matrix_T>
SquareMatrixValue<matrix_T>& SquareMatrixValue<matrix_T>::operator+=(const matrix_T& v)
{
    return perform_operation([](matrix_T& l, const matrix_T& r){l += r;} , v);
}

template <typename matrix_T>
SquareMatrixValue<matrix_T>& SquareMatrixValue<matrix_T>::operator-=(const matrix_T& v)
{
    return perform_operation([](matrix_T& l, const matrix_T& r){l -= r;} , v);
}

template <typename matrix_T>
SquareMatrixValue<matrix_T>& SquareMatrixValue<matrix_T>::operator*=(const matrix_T& v)
{
    return perform_operation([](matrix_T& l, const matrix_T& r){l *= r;} , v);
}

template <typename matrix_T>
SquareMatrixValue<matrix_T>& SquareMatrixValue<matrix_T>::operator/=(const matrix_T& v)
{
    return perform_operation([](matrix_T& l, const matrix_T& r){l /= r;} , v);
}

template <typename matrix_T>
bool SquareMatrixValue<matrix_T>::operator==(const matrix_T& v) const
{
    return operator matrix_T() == v;
}

template <typename matrix_T>
bool SquareMatrixValue<matrix_T>::operator==(const SquareMatrixValue& v) const
{
    return operator matrix_T() == v.operator matrix_T();
}

template <typename matrix_T>
bool SquareMatrixValue<matrix_T>::operator!=(const matrix_T& v) const
{
    return operator matrix_T() != v;
}

template <typename matrix_T>
bool SquareMatrixValue<matrix_T>::operator!=(const SquareMatrixValue& v) const
{
    return operator matrix_T() != v.operator matrix_T();
}