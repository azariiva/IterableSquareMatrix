#ifndef SQUARE_MATRIX_HPP
#define SQUARE_MATRIX_HPP

#include <cstddef>

template <typename val_T, typename row_T, typename col_T, typename rowv_T> class SquareMatrix
{
public:
    typedef row_T RowSelector;
    typedef col_T ColumnSelector;
    typedef rowv_T RowValueSelector;

public:
    SquareMatrix() = delete;
    SquareMatrix(size_t, size_t);
    SquareMatrix(const SquareMatrix&);
    virtual ~SquareMatrix();
    virtual SquareMatrix& operator=(const SquareMatrix&);

    virtual const val_T& get(size_t, size_t) const = 0;
    virtual void set(size_t, size_t, const val_T&) = 0;

    size_t num_rows() const;
    size_t num_columns() const;

    RowValueSelector operator[](size_t);
    RowValueSelector operator[](size_t) const;
    RowValueSelector operator*();
    RowValueSelector operator*() const;
    ColumnSelector T();
    ColumnSelector T() const;

    /*
    ** Арифметические операции вида:
    ** SquareMatrix.op(SquareMatrix)
    */
    SquareMatrix& operator+=(const SquareMatrix&);
    SquareMatrix& operator-=(const SquareMatrix&);
    SquareMatrix& operator*=(const SquareMatrix&);
    SquareMatrix& operator/=(const SquareMatrix&);
    virtual SquareMatrix& dot(const SquareMatrix&) = 0;

     /*
    ** Арифметические операции вида:
    ** SquareMatrix.op(double)
    */
    SquareMatrix& operator*=(const val_T&);
    SquareMatrix& operator/=(const val_T&);

    virtual bool operator==(const SquareMatrix&) const;
    virtual bool operator!=(const SquareMatrix&) const;

private:
    virtual SquareMatrix& perform_operation(void (*)(val_T&,val_T), const SquareMatrix&) = 0;
    virtual SquareMatrix& perform_operation(void (*)(val_T&,val_T), const val_T&) = 0;

protected:
    size_t m_num_rows;
    size_t m_num_columns;
};

// /*
// ** Арифметические операции вида:
// ** SquareMatrix (*) SquareMatrix
// */
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> operator+(
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&,
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&);
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> operator-(
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&,
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&);
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> operator*(
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&,
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&);
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> operator/(
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&,
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&);
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> dot(
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&,
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&);

// /*
// ** Арифметичесик операции вида:
// ** SquareMatrix (*) double или  double (*) SquareMatrix
// */
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> operator*(
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&, const val_T&);
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> operator*(
//     const val_T&, const SquareMatrix<val_T,row_T,col_T,rowv_T>&);
// template <typename val_T, typename row_T, typename col_T, typename rowv_T>
// SquareMatrix<val_T,row_T,col_T,rowv_T> operator/(
//     const SquareMatrix<val_T,row_T,col_T,rowv_T>&, const val_T&);

/*
** Адресная арифметика
*/
template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowSelector
operator+(SquareMatrix<val_T,row_T,col_T,rowv_T>, size_t);
template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowSelector
operator+(const SquareMatrix<val_T,row_T,col_T,rowv_T>, size_t);
template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowSelector
operator+(size_t, SquareMatrix<val_T,row_T,col_T,rowv_T>);
template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowSelector
operator+(size_t, const SquareMatrix<val_T,row_T,col_T,rowv_T>);
template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowSelector
operator-(SquareMatrix<val_T,row_T,col_T,rowv_T>, size_t);
template <typename val_T, typename row_T, typename col_T, typename rowv_T>
typename SquareMatrix<val_T,row_T,col_T,rowv_T>::RowSelector
operator-(const SquareMatrix<val_T,row_T,col_T,rowv_T>, size_t);

#endif