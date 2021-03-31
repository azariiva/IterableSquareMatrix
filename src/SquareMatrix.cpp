#include "SquareMatrix.hpp"

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>::SquareMatrix(
    size_t num_rows, size_t num_columns)
{
    m_num_rows = num_rows;
    m_num_columns = num_columns;
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>::SquareMatrix(const SquareMatrix& m)
{
    m_num_rows = m.m_num_rows;
    m_num_columns = m.m_num_columns;
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>::~SquareMatrix() {}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>&
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator=(const SquareMatrix& m)
{
    m_num_rows = m.m_num_rows;
    m_num_columns = m.num_columns;
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
size_t SquareMatrix<val_T,row_T,col_T,rowv_T>::num_rows() const
{
    return m_num_rows;
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
size_t SquareMatrix<val_T,row_T,col_T,rowv_T>::num_columns() const
{
    return m_num_columns;
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowValueSelector
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator[](size_t row)
{
    if (row >= m_num_rows)
        throw std::out_of_range("out of bounds exception(num_rows exceeded)");
    return RowValueSelector(this, true, row);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowValueSelector
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator[](size_t row) const
{
    if (row >= m_num_rows)
        throw std::out_of_range("out of bounds exception(num_rows exceeded)");
    return RowValueSelector(this, false, row);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowValueSelector
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator*()
{
    return operator[](0);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowValueSelector
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator*() const
{
    return operator[](0);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::ColumnSelector
SquareMatrix<val_T,row_T,col_T,rowv_T>::T()
{
    return ColumnSelector(this, true, 0);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::ColumnSelector
SquareMatrix<val_T,row_T,col_T,rowv_T>::T() const
{
    return ColumnSelector(this, false, 0);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>&
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator+=(const SquareMatrix& m)
{
    return perform_operation([](val_T& l,val_T r){l += r;}, m);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>&
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator-=(const SquareMatrix& m)
{
    return perform_operation([](val_T& l,val_T r){l -= r;}, m);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>&
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator*=(const SquareMatrix& m)
{
    return perform_operation([](val_T& l,val_T r){l *= r;}, m);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>&
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator/=(const SquareMatrix& m)
{
    return perform_operation([](val_T& l,val_T r){l /= r;}, m);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>&
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator*=(const val_T& v)
{
    return perform_operation([](val_T& l,val_T r){l *= r;}, v);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
SquareMatrix<val_T,row_T,col_T,rowv_T>&
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator/=(const val_T& v)
{
    return perform_operation([](val_T& l,val_T r){l /= r;}, v);
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
bool
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator==(
    const SquareMatrix& m) const
{
    return m_num_rows == m.m_num_rows && m_num_columns == m.m_num_columns;
}

template <typename val_T, typename row_T, typename col_T, typename rowv_T>
bool
SquareMatrix<val_T,row_T,col_T,rowv_T>::operator!=(
    const SquareMatrix& m) const
{
    return m_num_rows != m.m_num_rows || m_num_columns != m.m_num_columns;
}
