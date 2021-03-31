#ifndef SQUARE_MATRIX_SELECTOR_HPP
#define SQUARE_MATRIX_SELECTOR_HPP

#include "SquareMatrix.hpp"
#include <cstddef>

template <typename T> class SquareMatrix;
template <typename matrix_T, typename deref_T> class SquareMatrixSelector;

template <typename matrix_T, typename deref_T>
SquareMatrixSelector<matrix_T,deref_T> && operator+(SquareMatrixSelector<matrix_T,deref_T>&&, size_t);

template <typename matrix_T, typename deref_T>
SquareMatrixSelector<matrix_T,deref_T> && operator+(size_t, SquareMatrixSelector<matrix_T,deref_T>&&);

template <typename matrix_T, typename deref_T>
SquareMatrixSelector<matrix_T,deref_T> && operator-(SquareMatrixSelector<matrix_T,deref_T>&&, size_t);

template <typename matrix_T, typename deref_T> class SquareMatrixSelector
{
public:
    SquareMatrixSelector() = delete;
    SquareMatrixSelector &operator=(const SquareMatrixSelector&) = delete;
    deref_T operator[](size_t) const;
    deref_T operator*() const;

protected:
    SquareMatrixSelector(const matrix_T *, bool, size_t);
    SquareMatrixSelector(const SquareMatrixSelector&);

private:
    virtual inline void check_idx() const = 0;
    friend SquareMatrixSelector&& operator+ <matrix_T,deref_T> (SquareMatrixSelector&&, size_t);
    friend SquareMatrixSelector&& operator+ <matrix_T,deref_T> (size_t, SquareMatrixSelector&&);
    friend SquareMatrixSelector&& operator- <matrix_T,deref_T> (SquareMatrixSelector&&, size_t);
    friend deref_T;
    
protected:
    const matrix_T *m_matrix;
    const bool m_modifyable;
    size_t m_idx;
};

#include "SquareMatrixSelector.tcc"

#endif