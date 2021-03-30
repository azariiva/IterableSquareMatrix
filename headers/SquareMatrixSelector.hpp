#ifndef SQUARE_MATRIX_SELECTOR_HPP
#define SQUARE_MATRIX_SELECTOR_HPP

#include "SquareMatrix.hpp"
#include <cstddef>

template <typename T> class SquareMatrix;

template <typename matrix_T, typename deref_T> class SquareMatrixSelector
{
public:
    SquareMatrixSelector() = delete;
    SquareMatrixSelector(const SquareMatrixSelector&) = delete;
    SquareMatrixSelector &operator=(const SquareMatrixSelector&) = delete;
    deref_T operator[](size_t) const;
    deref_T operator*() const;

protected:
    SquareMatrixSelector(const SquareMatrix<matrix_T> *, bool, size_t);

private:
    virtual inline void check_idx() const = 0;
    friend SquareMatrixSelector&& operator+ <matrix_T,deref_T> (SquareMatrixSelector&&, size_t);
    friend SquareMatrixSelector&& operator+ <matrix_T,deref_T> (size_t, SquareMatrixSelector&&);
    friend SquareMatrixSelector&& operator- <matrix_T,deref_T> (SquareMatrixSelector&&, size_t);
    friend deref_T;
    
protected:
    const SquareMatrix<matrix_T> *m_matrix;
    const bool m_modifyable;
    size_t m_idx;
};

#endif