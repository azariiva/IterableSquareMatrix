#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include "SparseMatrixValue.hpp"
#include "../SquareMatrix/SquareMatrix.hpp"
#include "RBTree.hpp"
#include "MatrixIndex.hpp"

template <typename T> SparseMatrixValue;

template <typename T> class SparseMatrix : public SquareMatrix<T,SparseMatrixValue<T> >
{
public:
    typedef ::SquareMatrix<T,SparseMatrixValue<T> > SquareMatrix;
    typedef typename SquareMatrix::SquareMatrixSelector SquareMatrixSelector;

private:
    typedef typename SquareMatrix::SquareMatrixSelectorTemplate SquareMatrixSelectorTemplate;
    typedef typename SquareMatrix::Value Value;
    typedef typename SparseMatrixValue<T> SparseMatrixValue;

public:
    SparseMatrix(size_t, size_t);
    SparseMatrix(const SparseMatrix&);
    SparseMatrix(const SquareMatrixSelectorTemplate&);
    ~SparseMatrix();
    SparseMatrix& operator=(const SparseMatrix&);
    SparseMatrix& operator=(const SparseMatrixSelectorTemplate&);
    inline const Value& get(size_t, size_t) const;
    inline SparseMatrixValue get(size_t, size_t);
    SparseMatrix dot(const SparseMatrix&) const;

private:
    SparseMatrix& perform_operation(void (*op)(Value&, const Value&), const SquareMatrix& m);
    SparseMatrix& perform_operation(void (*op)(Value&, const Value&), const Value& val);

private:
    RBTree<MatrixIndex,T> tree;
}
#endif