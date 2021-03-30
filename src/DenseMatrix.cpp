#include "DenseMatrix.hpp"
#include <stdexcept>

template <typename T>
DenseMatrix<T>::DenseMatrix(size_t num_rows, size_t num_columns) : SquareMatrix<T>(num_rows, num_columns)
{
    m_matrix = new T*[num_rows];
    for (size_t i = 0; i < num_rows; ++i)
        m_matrix[i] = new T[num_columns];
}

template <typename T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix& m) : SquareMatrix<T>(m.m_num_rows, m.m_num_columns)
{
    m_matrix = new T*[SquareMatrix<T>::m_num_rows];
    for (size_t i = 0; i < SquareMatrix<T>::m_num_rows; ++i)
    {
        m_matrix[i] = new T[SquareMatrix<T>::m_num_columns];
        for (size_t j = 0; j < SquareMatrix<T>::m_num_columns; ++j)
            m_matrix[i][j] = m.m_matrix[i][j];
    }
}

template <typename T>
DenseMatrix<T>::~DenseMatrix()
{
    if (m_matrix != nullptr)
    {
        for (size_t i = 0; i < SquareMatrix<T>::m_num_rows; ++i)
        {
            if (m_matrix[i])
                delete[] m_matrix[i];
        }
        delete[] m_matrix;
    }
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const DenseMatrix& m)
{
    // Will it work??
    if (this == &m)
        return *this;
    this->~DenseMatrix<T>();
    m_matrix = new T*[SquareMatrix<T>::m_num_rows];
    for (size_t i = 0; i < SquareMatrix<T>::m_num_rows; ++i)
    {
        m_matrix[i] = new T[SquareMatrix<T>::m_num_columns];
        for (size_t j = 0; j < SquareMatrix<T>::m_num_columns; ++j)
            m_matrix[i][j] = m.m_matrix[i][j];
    }
    return *this;
}

template <typename T>
const T& DenseMatrix<T>::get(size_t row, size_t column) const
{
    if (row >= SquareMatrix<T>::m_num_rows || column >= SquareMatrix<T>::m_num_columns)
        throw std::out_of_range("out of bounds exception (num_rows or num_columns exceeded)");
    return m_matrix[row][column];
}


template <typename T>
void DenseMatrix<T>::set(size_t row, size_t column, const T& value) const
{
    if (row >= SquareMatrix<T>::m_num_rows || column >= SquareMatrix<T>::m_num_columns)
        throw std::out_of_range("out of bounds exception (num_rows or num_columns exceeded)");
    m_matrix[row][column] = value;
}

template <typename T>
bool DenseMatrix<T>::operator==(const DenseMatrix& m) const
{
    if (SquareMatrix<T>::m_num_rows != m.m_num_rows || SquareMatrix<T>::m_num_columns != m.m_num_columns)
        return false;
    for (size_t i = 0; i < SquareMatrix<T>::m_num_rows; ++i)
        for (size_t j = 0; j < SquareMatrix<T>::m_num_columns; ++j)
            if (m_matrix[i][j] != m.m_matrix[i][j])
                return false;
    return true;
}

template <typename T>
bool DenseMatrix<T>::operator!=(const DenseMatrix& m) const
{
    return !operator==(m);
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::perform_operation(void (*op)(T&,T), const DenseMatrix& m)
{  
    if (SquareMatrix<T>::m_num_rows != m.m_num_rows || SquareMatrix<T>::m_num_columns != m.m_num_columns)
        throw std::invalid_argument("operands could not be broadcast together");
    for (size_t i = 0; i < SquareMatrix<T>::m_num_rows; ++i)
        for (size_t j = 0; j < SquareMatrix<T>::m_num_columns; ++j)
            op(m_matrix[i][j], m.m_matrix[i][j]);
    return *this;
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::perform_operation(void (*op)(T&,T), const T& v)
{  
    for (size_t i = 0; i < SquareMatrix<T>::m_num_rows; ++i)
        for (size_t j = 0; j < SquareMatrix<T>::m_num_columns; ++j)
            op(m_matrix[i][j], v);
    return *this;
}

template class DenseMatrix<int>;