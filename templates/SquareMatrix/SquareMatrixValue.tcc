#include "../../headers/SquareMatrix/SquareMatrixValue.hpp"

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>::SquareMatrixValue(size_t idx, size_t pidx, set_mode set, bool modifyable, const Matrix *matrix) :
m_modifyable(modifyable), m_matrix(const_cast<Matrix *>(matrix)) {
    if (set == set_mode::row) {
        m_row = pidx;
        m_column = idx;
    } else {
        m_row = idx;
        m_column = pidx;
    }
}

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>& SquareMatrixValue<val_T,matrix_T>::operator=(const SquareMatrixValue& val)
{
    operator=(val.operator Value());
}

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>& SquareMatrixValue<val_T,matrix_T>::operator+=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l += r;} , v);
}

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>& SquareMatrixValue<val_T,matrix_T>::operator-=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l -= r;} , v);
}

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>& SquareMatrixValue<val_T,matrix_T>::operator*=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l *= r;} , v);
}

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>& SquareMatrixValue<val_T,matrix_T>::operator/=(const Value& v)
{
    return perform_operation([](Value& l, const Value& r){l /= r;} , v);
}

template <typename val_T, class matrix_T>
bool SquareMatrixValue<val_T,matrix_T>::operator==(const Value& v) const
{
    return operator Value() == v;
}

template <typename val_T, class matrix_T>
bool SquareMatrixValue<val_T,matrix_T>::operator==(const SquareMatrixValue& v) const
{
    return operator Value() == v.operator Value();
}

template <typename val_T, class matrix_T>
bool SquareMatrixValue<val_T,matrix_T>::operator!=(const Value& v) const
{
    return operator Value() != v;
}

template <typename val_T, class matrix_T>
bool SquareMatrixValue<val_T,matrix_T>::operator!=(const SquareMatrixValue& v) const
{
    return operator Value() != v.operator Value();
}

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>& SquareMatrixValue<val_T,matrix_T>::operator=(const Value& val)
{
    if (m_modifyable == false)
        throw std::logic_error("Could not modify constant value");
    else
        m_matrix->set(m_row, m_column, val);
}

template <typename val_T, class matrix_T>
SquareMatrixValue<val_T,matrix_T>::operator Value() const
{
    return m_matrix->get(m_row, m_column);
}