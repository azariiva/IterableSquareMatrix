#include "SquareMatrixSelector.hpp"

template <typename matrix_T, typename deref_T>
deref_T SquareMatrixSelector<matrix_T,deref_T>::operator[](size_t idx) const
{
    m_idx += idx;
    check_idx();
    return deref_T(*this);
}

template <typename matrix_T, typename deref_T>
deref_T SquareMatrixSelector<matrix_T,deref_T>::operator*() const
{
    check_idx();
    return deref_T(*this);
}

template <typename matrix_T, typename deref_T>
SquareMatrixSelector<matrix_T,deref_T>::SquareMatrixSelector(const SquareMatrix<matrix_T> *matrix, bool modifyable, size_t m_idx)
{
    m_matrix = matrix;
    m_modifyable = modifyable;
    m_idx = idx;
}

template <typename matrix_T, typename deref_T>
SquareMatrixSelector<matrix_T,deref_T>&& operator+(SquareMatrixSelector<matrix_T,deref_T>&& selector, size_t offset)
{
    selector.m_idx += offset;
    return lv;
}

template <typename matrix_T, typename deref_T>
SquareMatrixSelector<matrix_T,deref_T>&& operator+(size_t offset, SquareMatrixSelector<matrix_T,deref_T>&& selector)
{
    selector.m_idx += offset;
    return rv;
}

template <typename matrix_T, typename deref_T>
SquareMatrixSelector<matrix_T,deref_T>&& operator-(SquareMatrixSelector<matrix_T,deref_T>&& selector, size_t offset)
{
    selector.m_idx -= offset;
    return lv;
}

