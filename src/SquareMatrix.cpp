#include "SquareMatrix.hpp"

template <typename T>
SquareMatrix<T>::SquareMatrix(size_t num_rows, size_t num_columns)
{
    m_num_rows = num_rows;
    m_num_columns = num_columns;
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix& m)
{
    m_num_rows = m.m_num_rows;
    m_num_columns = m.m_num_columns;
}

template <typename T>
SquareMatrix<T>::~SquareMatrix() {}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix& m)
{
    m_num_rows = m.m_num_rows;
    m_num_columns = m.num_columns;
}

template <typename T>
size_t SquareMatrix<T>::num_rows() const
{
    return m_num_rows;
}

template <typename T>
size_t SquareMatrix<T>::num_columns() const
{
    return m_num_columns;
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator+=(const SquareMatrix& m)
{
    return perform_operation([](T& l,T r){l += r;}, m);
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator-=(const SquareMatrix& m)
{
    return perform_operation([](T& l,T r){l -= r;}, m);
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator*=(const SquareMatrix& m)
{
    return perform_operation([](T& l,T r){l *= r;}, m);
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator/=(const SquareMatrix& m)
{
    return perform_operation([](T& l,T r){l /= r;}, m);
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator*=(const T& v)
{
    return perform_operation([](T& l,T r){l *= r;}, v);
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator/=(const T& v)
{
    return perform_operation([](T& l,T r){l /= r;}, v);
}

template <typename T>
bool SquareMatrix<T>::operator==(const SquareMatrix& m) const
{
    return m_num_rows == m.m_num_rows && m_num_columns == m.m_num_columns;
}

template <typename T>
bool SquareMatrix<T>::operator!=(const SquareMatrix& m) const
{
    return m_num_rows != m.m_num_rows || m_num_columns != m.m_num_columns;
}
