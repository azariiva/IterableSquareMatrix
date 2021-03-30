#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include "SquareMatrixValue.hpp"
#include "SquareMatrixRowSelector.hpp"
#include "SquareMatrixColumnSelector.hpp"
#include <cstddef>

template <typename T> class SquareMatrixValue;

template <typename T> class SquareMatrix
{
public:
    SquareMatrix() = delete;
    SquareMatrix(size_t, size_t);
    SquareMatrix(const SquareMatrix&);
    virtual ~SquareMatrix();
    virtual SquareMatrix& operator=(const SquareMatrix&);

    virtual const T& get(size_t, size_t) const = 0;
    virtual void set(size_t, size_t, const T&) = 0;

    size_t num_rows() const;
    size_t num_columns() const;

    SquareMatrix& operator+=(const SquareMatrix&);
    SquareMatrix& operator-=(const SquareMatrix&);
    SquareMatrix& operator*=(const SquareMatrix&);
    SquareMatrix& operator/=(const SquareMatrix&);

    SquareMatrix& operator*=(const T&);
    SquareMatrix& operator/=(const T&);

    virtual bool operator==(const SquareMatrix&) const;
    virtual bool operator!=(const SquareMatrix&) const;

private:
    virtual SquareMatrix& perform_operation(void (*)(T&,T), const SquareMatrix&) = 0;
    virtual SquareMatrix& perform_operation(void (*)(T&,T), const T&) = 0;

protected:
    size_t m_num_rows;
    size_t m_num_columns;
};

#endif