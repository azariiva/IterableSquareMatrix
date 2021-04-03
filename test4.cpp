#include "SquareMatrixValue.hpp"
#include "SquareMatrixSelector.hpp"
#include "SquareMatrix.hpp"
#include <stdexcept>
#include <iostream>

class DenseMatrix;
class DenseMatrixSelector;
class DenseMatrixValueSelector;
class DenseMatrixValue;

class DenseMatrix : public SquareMatrix<int,DenseMatrixValue>
{
public:
    typedef SquareMatrix<int,DenseMatrixValue> SquareMatrix;
    typedef SquareMatrix::SquareMatrixSelector SquareMatrixSelector;

private:
    typedef SquareMatrix::Value Value;

public:
    DenseMatrix(size_t num_rows, size_t num_columns) : SquareMatrix(num_rows, num_columns)
    {
        m_matrix = new Value*[m_num_rows];
        for (size_t i = 0; i < m_num_rows; ++i)
            m_matrix[i] = new Value[m_num_columns];
    }

    DenseMatrix(DenseMatrix &m) : SquareMatrix(m)
    {
        m_matrix = new Value*[m_num_rows];
        for (size_t i = 0; i < m_num_rows; ++i) {
            m_matrix[i] = new Value[m_num_columns];
            for (size_t j = 0; j < m_num_columns; ++j)
                m_matrix[i][j] = m.m_matrix[i][j];
        }
    }

    ~DenseMatrix()
    {
        for (size_t i = 0; i < m_num_rows; ++i)
            delete[] m_matrix[i];
        delete[] m_matrix;
    }

    DenseMatrix& operator=(const DenseMatrix& m)
    {
        if (this == &m)
            return *this;
        if (m_num_rows == m.m_num_rows) {
            if (m_num_columns != m.m_num_columns) {
                for (size_t i = 0; i < m_num_rows; ++i) {
                    delete[] m_matrix[i];
                    m_matrix[i] = new Value[m.m_num_columns];
                }
            }
        } else {
            for (size_t i = 0; i < m_num_rows; ++i)
                delete[] m_matrix[i];
            delete[] m_matrix;
            m_matrix = new Value*[m.m_num_rows];
            for (size_t i = 0; i < m.m_num_rows; ++i)
                m_matrix[i] = new Value[m.m_num_columns];
        }
        m_num_rows = m.m_num_rows;
        m_num_columns = m.m_num_columns;
        for (size_t i = 0; i < m_num_rows; ++i)
            for (size_t j = 0; j < m_num_columns; ++j)
                m_matrix[i][j] = m.m_matrix[i][j];
        return *this;
    }

    inline const Value& get(size_t row, size_t column) const
    {
        if (row >= m_num_rows || column >= m_num_columns)
            throw std::out_of_range("num_rows|num_columns exceeded");
        return m_matrix[row][column];
    }

    inline Value& get(size_t row, size_t column) {
        if (row >= m_num_rows || column >= m_num_columns)
            throw std::out_of_range("num_rows|num_columns exceeded");
        return m_matrix[row][column];
    }

    DenseMatrix dot(const DenseMatrix& m)
    {
        if (m_num_columns != m.m_num_rows)
            throw std::invalid_argument("operands could not be broadcast together");
        DenseMatrix r(m_num_rows, m.m_num_columns);

        for (size_t i = 0; i < m_num_rows; ++i)
            for (size_t j = 0; j < m.m_num_columns; ++j)
                for (size_t k = 0; k < m_num_columns; ++k)
                    r.get(i, j) += get(i, k) * m.get(k, j);
        return r;
    }

private:
    DenseMatrix& perform_operation(void (*op)(Value&, const Value&), const SquareMatrix& m)
    {
        if (m_num_rows != m.num_rows() || m_num_columns != m.num_columns())
            throw std::invalid_argument("operands could not be broadcast together");
        for (size_t i = 0; i < m_num_rows; ++i)
            for (size_t j = 0; j < m_num_columns; ++j)
                op(get(i, j), m.get(i, j));
        return *this;
    }

    DenseMatrix& perform_operation(void (*op)(Value&, const Value&), const Value& val)
    {
        for (size_t i = 0; i < m_num_rows; ++i)
            for (size_t j = 0; j < m_num_columns; ++j)
                op(get(i, j), val);
        return *this;
    }

private:
    int **m_matrix;
};

DenseMatrix::SquareMatrix::SquareMatrixSelector operator+(DenseMatrix::SquareMatrix& m, size_t idx)
{
    return DenseMatrix::SquareMatrix::SquareMatrixSelector(&m, true, idx);
}

DenseMatrix::SquareMatrix::SquareMatrixSelector operator-(DenseMatrix::SquareMatrix& m, size_t idx)
{
    return DenseMatrix::SquareMatrix::SquareMatrixSelector(&m, true, -idx);
}

DenseMatrix::SquareMatrix::SquareMatrixSelector operator+(const DenseMatrix::SquareMatrix& m, size_t idx)
{
    return DenseMatrix::SquareMatrix::SquareMatrixSelector(&m, false, idx);
}

DenseMatrix::SquareMatrix::SquareMatrixSelector operator-(const DenseMatrix::SquareMatrix& m, size_t idx)
{
    return DenseMatrix::SquareMatrix::SquareMatrixSelector(&m, false, -idx);
}

DenseMatrix::SquareMatrix::SquareMatrixSelector operator+(size_t idx, DenseMatrix::SquareMatrix& m)
{
    return DenseMatrix::SquareMatrix::SquareMatrixSelector(&m, true, idx);
}

DenseMatrix::SquareMatrix::SquareMatrixSelector operator+(size_t idx, const DenseMatrix::SquareMatrix& m)
{
    return DenseMatrix::SquareMatrix::SquareMatrixSelector(&m, false, idx);
}

class DenseMatrixValue : SquareMatrixValue<int,::DenseMatrix::SquareMatrix>
{
private:
    typedef ::DenseMatrix::SquareMatrix::SquareMatrixValueSelector SquareMatrixValueSelector;
    typedef SquareMatrixValue<int,DenseMatrix::SquareMatrix> SquareMatrixValue;
    typedef SquareMatrixValue::Value Value;
    typedef SquareMatrixValue::Matrix Matrix;

public:
    DenseMatrixValue(const SquareMatrixValueSelector::SquareMatrixSelectorTemplate& s) :
    SquareMatrixValue(s.idx(), s.pidx(), s.set(), s.modifyable(), s.matrix()) {}

    DenseMatrixValue& operator=(const Value& val)
    {
        if (m_modifyable)
            m_matrix->set(m_row, m_column, val);
        else
            throw std::logic_error("Can't modify constant value");
    }

    operator Value() const
    {
        return m_matrix->get(m_row, m_column);
    }

private:
    DenseMatrixValue& perform_operation(void(*op)(Value&, const Value&), const Value& val)
    {
        if (SquareMatrixValue::m_modifyable)
            op(m_matrix->get(m_row, m_column), val);
        else
            throw std::logic_error("Can't modify constant value");
    }
};

using std::cout;
using std::endl;

int main(void)
{
    DenseMatrix m(9, 9);
    
    cout << m.num_rows() << ' ' << m.num_columns() << '\n';
    for (size_t i = 0; i < m.num_rows(); i++)
        for (size_t j = 0; j < m.num_columns(); j++)
            m.set(i, j, (i + 1) * (m.num_rows() + 1) + j + 1);

    for (size_t i = 0; i < m.num_rows(); i++)
    {
        for (size_t j = 0; j < m.num_columns(); j++)
            cout << m[i][j] << ' ';
        cout << '\n';
    }
    cout << endl;
    for (size_t i = 0; i < m.num_columns(); i++)
    {
        for (size_t j = 0; j < m.num_rows(); j++)
            cout << (2 + *(1 + m.transpose() + i - 1) + j - 5)[3] << ' ';
        cout << '\n';
    }
    return 0;
}