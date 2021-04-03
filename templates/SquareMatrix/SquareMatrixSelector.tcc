#include "../../headers/SquareMatrix/SquareMatrixSelector.hpp"
#include <stdexcept>

/*
 *  SquareMatrixSelectorTemplate конструкторы
*/
template <class matrix_T, class deref_T>
SquareMatrixSelectorTemplate<matrix_T,deref_T>::SquareMatrixSelectorTemplate(
    const matrix_T *matrix, bool modifyable, size_t idx, set_mode set) :
m_matrix(matrix), m_modifyable(modifyable), m_idx(idx), m_set(set) {}

template <class matrix_T, class deref_T>
SquareMatrixSelectorTemplate<matrix_T,deref_T>::SquareMatrixSelectorTemplate(
    const SquareMatrixSelectorTemplate& s) :
m_matrix(s.m_matrix), m_modifyable(s.m_modifyable), m_idx(s.m_idx), 
m_set(s.m_set) {}


template <class matrix_T, class deref_T>
const typename SquareMatrixSelectorTemplate<matrix_T,deref_T>::Matrix *
SquareMatrixSelectorTemplate<matrix_T,deref_T>::matrix() const
{
    return m_matrix;
}

/*
 *  SquareMatrixSelectorTemplate getters
*/
template <class matrix_T, class deref_T>
bool SquareMatrixSelectorTemplate<matrix_T,deref_T>::modifyable() const
{
    return m_modifyable;
}

template <class matrix_T, class deref_T>
size_t SquareMatrixSelectorTemplate<matrix_T,deref_T>::idx() const
{
    return m_idx;
}

template <class matrix_T, class deref_T>
set_mode SquareMatrixSelectorTemplate<matrix_T,deref_T>::set() const
{
    return m_set;
}

template <class matrix_T, class deref_T>
size_t SquareMatrixSelectorTemplate<matrix_T,deref_T>::pidx() const
{
    throw std::logic_error("pidx doesn't exist");
}

/*
 *  SquareMatrixSelectorTemplate разыменование
*/
template <class matrix_T, class deref_T>
deref_T SquareMatrixSelectorTemplate<matrix_T,deref_T>::operator[](size_t idx) const
{
    const_cast<SquareMatrixSelectorTemplate *>(this)->m_idx += idx;
    check_idx();
    return deref_T(*this);
}

template <class matrix_T, class deref_T>
deref_T SquareMatrixSelectorTemplate<matrix_T,deref_T>::operator*() const
{
    check_idx();
    return deref_T(*this);
}

/*
 *  SquareMatrixSelectorTemplate адресная арифметика
*/
template <class matrix_T, class deref_T>
const SquareMatrixSelectorTemplate<matrix_T,deref_T>& operator+(const SquareMatrixSelectorTemplate<matrix_T,deref_T>& s, size_t off)
{
    const_cast<SquareMatrixSelectorTemplate<matrix_T,deref_T> &>(s).m_idx += off;
    return s;
}

template <class matrix_T, class deref_T>
const SquareMatrixSelectorTemplate<matrix_T,deref_T>& operator+(size_t off, const SquareMatrixSelectorTemplate<matrix_T,deref_T>& s)
{
    const_cast<SquareMatrixSelectorTemplate<matrix_T,deref_T> &>(s).m_idx += off;
    return s;
}

template <class matrix_T, class deref_T>
const SquareMatrixSelectorTemplate<matrix_T,deref_T>& operator-(const SquareMatrixSelectorTemplate<matrix_T,deref_T>& s, size_t off)
{
    const_cast<SquareMatrixSelectorTemplate<matrix_T,deref_T> &>(s).m_idx -= off;
    return s;
}

/*
 *  SquareMatrixSelector конструкторы
*/
template <typename value_T, class matrix_T>
SquareMatrixSelector<value_T,matrix_T>::SquareMatrixSelector(const SquareMatrixSelector& s) :
SquareMatrixSelectorTemplate(s) {}

template <typename value_T, class matrix_T>
SquareMatrixSelector<value_T,matrix_T>::SquareMatrixSelector(const Matrix *matrix, bool modifyable, size_t idx, set_mode set) :
SquareMatrixSelectorTemplate(matrix, modifyable, idx, set) {}

/*
 *  SquareMatrixSelector::check_idx()
*/
template <typename value_T, class matrix_T>
void SquareMatrixSelector<value_T,matrix_T>::check_idx() const
{
    if (SquareMatrixSelectorTemplate::m_set == set_mode::row && \
        SquareMatrixSelectorTemplate::m_idx >= SquareMatrixSelectorTemplate::m_matrix->num_rows())
        throw std::out_of_range("num_rows exceeded");
    if (SquareMatrixSelectorTemplate::m_set == set_mode::column && \
        SquareMatrixSelectorTemplate::m_idx >= SquareMatrixSelectorTemplate::m_matrix->num_columns())
        throw std::out_of_range("num_columns exceeded");
}

/*
 *  SquareMatrixSelectorValue конструкторы
*/
template <typename value_T, class matrix_T>
SquareMatrixValueSelector<value_T, matrix_T>::SquareMatrixValueSelector(const typename SquareMatrixSelector::SquareMatrixSelectorTemplate& s) :
SquareMatrixSelectorTemplate(s.m_matrix, s.m_modifyable, 0, s.m_set), m_pidx(s.m_idx) {}

template <typename value_T, class matrix_T>
SquareMatrixValueSelector<value_T, matrix_T>::SquareMatrixValueSelector(const SquareMatrixValueSelector& s) :
SquareMatrixSelectorTemplate(s), m_pidx(s.m_pidx) {};

/*
 *  set == row if SquareMatrixValueSelector will iterate through columns
*/
template <typename value_T, class matrix_T>
SquareMatrixValueSelector<value_T, matrix_T>::SquareMatrixValueSelector(const Matrix *matrix, bool modifyable, size_t idx, set_mode set) :
SquareMatrixSelectorTemplate(matrix, modifyable, 0, set), m_pidx(idx) {};

/*
 *  SquareMatrixValueSelector::check_idx()
*/
template <typename value_T, class matrix_T>
void SquareMatrixValueSelector<value_T, matrix_T>::check_idx() const
{
    if (SquareMatrixSelectorTemplate::m_set == set_mode::row && \
        SquareMatrixSelectorTemplate::m_idx >= SquareMatrixSelectorTemplate::m_matrix->num_columns())
        throw std::out_of_range("num_columns exceeded");
    if (SquareMatrixSelectorTemplate::m_set == set_mode::column && \
        SquareMatrixSelectorTemplate::m_idx >= SquareMatrixSelectorTemplate::m_matrix->num_rows())
        throw std::out_of_range("num_rows exceeded");
}

template <typename value_T, class matrix_T>
size_t SquareMatrixValueSelector<value_T, matrix_T>::pidx() const
{
    return m_pidx;
}