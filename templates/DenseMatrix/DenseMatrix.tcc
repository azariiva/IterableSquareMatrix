#include "../../headers/DenseMatrix/DenseMatrix.hpp"

template <typename T>
DenseMatrix<T>::DenseMatrix(size_t num_rows, size_t num_columns) : SquareMatrix(num_rows, num_columns)
{
    m_matrix = new Value*[SquareMatrix::m_num_rows];
    for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
        m_matrix[i] = new Value[SquareMatrix::m_num_columns];
}

template <typename T>
DenseMatrix<T>::DenseMatrix(const DenseMatrix &m) : SquareMatrix(m)
{
    m_matrix = new Value*[SquareMatrix::m_num_rows];
    for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i) {
        m_matrix[i] = new Value[SquareMatrix::m_num_columns];
        for (size_t j = 0; j < SquareMatrix::m_num_columns; ++j)
            m_matrix[i][j] = m.m_matrix[i][j];
    }
}

#include <iostream>
template <typename T>
DenseMatrix<T>::DenseMatrix(const SquareMatrixSelectorTemplate& m) :
SquareMatrix(m.matrix()->num_rows(), m.matrix()->num_columns())
{
    size_t off = m.idx();

    if (m.set() == set_mode::row) {
        m_matrix = new Value*[m.matrix()->num_rows() - off];
        for (size_t i = off; i < m.matrix()->num_rows(); ++i) {
            m_matrix[i - off] = new Value[m.matrix()->num_columns()];
            for(size_t j = 0; j < m.matrix()->num_columns(); ++j)
                m_matrix[i - off][j] = m.matrix()->get(i, j);
        }
        SquareMatrix::m_num_rows -= off;
    } else {
        m_matrix = new Value*[m.matrix()->num_columns() - off];
        for (size_t i = off; i < m.matrix()->num_columns(); ++i) {
            m_matrix[i - off] = new Value[m.matrix()->num_rows()];
            for(size_t j = 0; j < m.matrix()->num_rows(); ++j)
                m_matrix[i - off][j] = m.matrix()->get(j, i);
        }
        SquareMatrix::m_num_rows = m.matrix()->num_columns() - off;
        SquareMatrix::m_num_columns = m.matrix()->num_rows();
    }
}

template <typename T>
DenseMatrix<T>::~DenseMatrix()
{
    for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
        delete[] m_matrix[i];
    delete[] m_matrix;
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const DenseMatrix& m)
{
    if (this == &m)
        return *this;
    if (SquareMatrix::m_num_rows == m.m_num_rows) {
        if (SquareMatrix::m_num_columns != m.m_num_columns) {
            SquareMatrix::m_num_columns = m.m_num_columns;
            for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i) {
                delete[] m_matrix[i];
                m_matrix[i] = new Value[SquareMatrix::m_num_columns];
            }
        }
    } else {
        for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
            delete[] m_matrix[i];
        delete[] m_matrix;
        SquareMatrix::m_num_rows = m.m_num_rows;
        m_matrix = new Value*[SquareMatrix::m_num_rows];
        SquareMatrix::m_num_columns = m.m_num_columns;
        for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
            m_matrix[i] = new Value[SquareMatrix::m_num_columns];
    }
    for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
        for (size_t j = 0; j < SquareMatrix::m_num_columns; ++j)
            m_matrix[i][j] = m.m_matrix[i][j];
    return *this;
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::operator=(const SquareMatrixSelectorTemplate& m)
{
    if (this == m.matrix())
        throw std::runtime_error("this feature doesn't supported yet");
    
    size_t off = m.idx();

    if (m.set() == set_mode::row) {
        if (m.matrix()->num_rows() - off == SquareMatrix::m_num_rows) {
            if (m.matrix()->num_columns() != SquareMatrix::m_num_columns) {
                SquareMatrix::m_num_columns = m.matrix()->num_columns();
                for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i) {
                    delete[] m_matrix[i];
                    m_matrix[i] = new Value[SquareMatrix::m_num_columns];
                }
            }
        } else {
            for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
                delete[] m_matrix[i];
            delete[] m_matrix;
            SquareMatrix::m_num_rows = m.matrix()->num_rows() - off;
            m_matrix = new Value*[SquareMatrix::m_num_rows];
            SquareMatrix::m_num_columns = m.matrix()->num_columns();
            for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
                m_matrix[i] = new Value[SquareMatrix::m_num_columns];
        }
        for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
            for (size_t j = 0; j < SquareMatrix::m_num_columns; ++j)
                m_matrix[i][j] = m.matrix()->get(i + off, j);
    } else {
        if (m.matrix()->num_columns() - off == SquareMatrix::m_num_rows) {
            if (m.matrix()->num_rows() != SquareMatrix::m_num_columns) {
                SquareMatrix::m_num_columns = m.matrix()->num_rows();
                for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i) {
                    delete[] m_matrix[i];
                    m_matrix[i] = new Value[SquareMatrix::m_num_columns];
                }
            }
        } else {
            for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
                delete[] m_matrix[i];
            delete[] m_matrix;
            SquareMatrix::m_num_rows = m.matrix()->num_columns() - off;
            m_matrix = new Value*[SquareMatrix::m_num_rows];
            SquareMatrix::m_num_columns = m.matrix()->num_rows();
            for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
                m_matrix[i] = new Value[SquareMatrix::m_num_columns];
        }
        for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
            for (size_t j = 0; j < SquareMatrix::m_num_columns; ++j)
                m_matrix[i][j] = m.matrix()->get(j, i + off);
    }
}

template <typename T>
const typename DenseMatrix<T>::Value& DenseMatrix<T>::get(size_t row, size_t column) const
{
    if (row >= SquareMatrix::m_num_rows || column >= SquareMatrix::m_num_columns)
        throw std::out_of_range("num_rows|num_columns exceeded");
    return m_matrix[row][column];
}

template <typename T>
typename DenseMatrix<T>::Value& DenseMatrix<T>::get(size_t row, size_t column) {
    if (row >= SquareMatrix::m_num_rows || column >= SquareMatrix::m_num_columns)
        throw std::out_of_range("num_rows|num_columns exceeded");
    return m_matrix[row][column];
}

template <typename T>
DenseMatrix<T> DenseMatrix<T>::dot(const DenseMatrix& m)
{
    if (SquareMatrix::m_num_columns != m.m_num_rows)
        throw std::invalid_argument("operands could not be broadcast together");
    DenseMatrix r(SquareMatrix::m_num_rows, m.m_num_columns);

    for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
        for (size_t j = 0; j < m.m_num_columns; ++j)
            for (size_t k = 0; k < SquareMatrix::m_num_columns; ++k)
                r.get(i, j) += get(i, k) * m.get(k, j);
    return r;
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::perform_operation(void (*op)(Value&, const Value&), const SquareMatrix& m)
{
    if (SquareMatrix::m_num_rows != m.num_rows() || SquareMatrix::m_num_columns != m.num_columns())
        throw std::invalid_argument("operands could not be broadcast together");
    for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
        for (size_t j = 0; j < SquareMatrix::m_num_columns; ++j)
            op(get(i, j), m.get(i, j));
    return *this;
}

template <typename T>
DenseMatrix<T>& DenseMatrix<T>::perform_operation(void (*op)(Value&, const Value&), const Value& val)
{
    for (size_t i = 0; i < SquareMatrix::m_num_rows; ++i)
        for (size_t j = 0; j < SquareMatrix::m_num_columns; ++j)
            op(get(i, j), val);
    return *this;
}