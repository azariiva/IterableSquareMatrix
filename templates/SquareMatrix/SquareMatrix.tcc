#include "../../headers/SquareMatrix/SquareMatrix.hpp"
#include <stdexcept>

template <typename T, typename value_T>
SquareMatrix<T,value_T>::SquareMatrix(size_t num_rows, size_t num_columns) :
m_num_rows(num_rows), m_num_columns(num_columns) {
    if (m_num_rows == 0 || m_num_columns == 0)
        throw std::logic_error("matrix couldn't be 0xN or Nx0");
}

template <typename T, typename value_T>
SquareMatrix<T,value_T>::SquareMatrix(const SquareMatrix& m) :
m_num_rows(m.m_num_rows), m_num_columns(m.m_num_columns) {}

template <typename T, typename value_T>
SquareMatrix<T,value_T>::~SquareMatrix() {}

template <typename T, typename value_T>
SquareMatrix<T,value_T>& SquareMatrix<T,value_T>::operator=(const SquareMatrix& m)
{
    if (this == &m)
        return *this;
    m_num_rows = m.m_num_rows;
    m_num_columns = m.m_num_columns;
    return *this;
}

template <typename T, typename value_T>
void SquareMatrix<T,value_T>::set(size_t row, size_t column, const Value& val)
{
    get(row, column) = val;
}

template <typename T, typename value_T>
size_t SquareMatrix<T,value_T>::num_rows() const
{
    return m_num_rows;
}

template <typename T, typename value_T>
size_t SquareMatrix<T,value_T>::num_columns() const
{
    return m_num_columns;
}

template <typename T, typename value_T>
typename SquareMatrix<T,value_T>::SquareMatrixValueSelector
SquareMatrix<T,value_T>::operator[](size_t row)
{
    if (row >= m_num_rows)
        throw std::out_of_range("out of bounds exception(num_rows exceeded)");
    return SquareMatrixValueSelector(this, true, row);
}

template <typename T, typename value_T>
typename SquareMatrix<T,value_T>::SquareMatrixValueSelector
SquareMatrix<T,value_T>::operator[](size_t row) const
{
    if (row >= m_num_rows)
        throw std::out_of_range("out of bounds exception(num_rows exceeded)");
    return SquareMatrixValueSelector(this, false, row);
}

template <typename T, typename value_T>
typename SquareMatrix<T,value_T>::SquareMatrixValueSelector
SquareMatrix<T,value_T>::operator*()
{
    return SquareMatrixValueSelector(this, true, 0);
}

template <typename T, typename value_T>
typename SquareMatrix<T,value_T>::SquareMatrixValueSelector
SquareMatrix<T,value_T>::operator*() const
{
    return SquareMatrixValueSelector(this, false, 0);
}

template <typename T, typename value_T>
typename SquareMatrix<T,value_T>::SquareMatrixSelector
SquareMatrix<T,value_T>::transpose()
{
    return SquareMatrixSelector(this, true, 0, set_mode::column);
}

template <typename T, typename value_T>
typename SquareMatrix<T,value_T>::SquareMatrixSelector
SquareMatrix<T,value_T>::transpose() const
{
    return SquareMatrixSelector(this, false, 0, set_mode::column);
}

template <typename T, typename value_T>
SquareMatrix<T,value_T>& SquareMatrix<T,value_T>::operator+=(const SquareMatrix& m)
{
    return perform_operation([](Value& l,Value r){l += r;}, m);
}

template <typename T, typename value_T>
SquareMatrix<T,value_T>& SquareMatrix<T,value_T>::operator-=(const SquareMatrix& m)
{
    return perform_operation([](Value& l,Value r){l -= r;}, m);
}

template <typename T, typename value_T>
SquareMatrix<T,value_T>& SquareMatrix<T,value_T>::operator*=(const SquareMatrix& m)
{
    return perform_operation([](Value& l,Value r){l *= r;}, m);
}

template <typename T, typename value_T>
SquareMatrix<T,value_T>& SquareMatrix<T,value_T>::operator/=(const SquareMatrix& m)
{
    return perform_operation([](Value& l,Value r){l /= r;}, m);
}

template <typename T, typename value_T>
SquareMatrix<T,value_T>& SquareMatrix<T,value_T>::operator*=(const Value& v)
{
    return perform_operation([](Value& l,Value r){l *= r;}, v);
}

template <typename T, typename value_T>
SquareMatrix<T,value_T>& SquareMatrix<T,value_T>::operator/=(const Value& v)
{
    return perform_operation([](Value& l,Value r){l /= r;}, v);
}

template <typename T, typename value_T>
bool SquareMatrix<T,value_T>::operator==(const SquareMatrix& m) const
{
    if (this == &m)
        return true;
    return m_num_rows == m.m_num_rows && m_num_columns == m.m_num_columns;
}

template <typename T, typename value_T>
bool
SquareMatrix<T,value_T>::operator!=(const SquareMatrix& m) const
{
    if (this == &m)
        return false;
    return m_num_rows != m.m_num_rows || m_num_columns != m.m_num_columns;
}

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(SquareMatrix<T, value_T>& matrix, size_t idx)
{
    return typename SquareMatrix<T, value_T>::SquareMatrixSelector(&matrix, true, idx);
}

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(const SquareMatrix<T, value_T>& matrix, size_t idx)
{
    return typename SquareMatrix<T, value_T>::SquareMatrixSelector(&matrix, false, idx);
}

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(size_t idx, SquareMatrix<T, value_T>& matrix)
{
    return typename SquareMatrix<T, value_T>::SquareMatrixSelector(&matrix, true, idx);
}

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator+(size_t idx, const SquareMatrix<T, value_T>& matrix)
{
    return typename SquareMatrix<T, value_T>::SquareMatrixSelector(&matrix, false, idx);
}

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator-(SquareMatrix<T, value_T>& matrix, size_t idx)
{
    return typename SquareMatrix<T, value_T>::SquareMatrixSelector(&matrix, true, -idx);
}

template <typename T, typename value_T>
typename SquareMatrix<T, value_T>::SquareMatrixSelector
operator-(const SquareMatrix<T, value_T>& matrix, size_t idx)
{
    return typename SquareMatrix<T, value_T>::SquareMatrixSelector(&matrix, false, -idx);
}