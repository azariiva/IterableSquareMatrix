// #ifndef DENSE_MATRIX_HPP
// #define DENSE_MATRIX_HPP


// #include "DenseMatrixValue.hpp"
// #include "DenseMatrixColumnValueSelector.hpp"
// #include "DenseMatrixRowSelector.hpp"
// #include "DenseMatrixColumnSelector.hpp"
// #include "SquareMatrix.hpp"
// #include <cstddef>

// template <typename T> class DenseMatrixRowValueSelector;
// template <typename T> class DenseMatrixColumnSelector;
// template <typename T> class DenseMatrixRowSelector;

// template <typename T>
// class DenseMatrix : public SquareMatrix<T, DenseMatrixRowSelector<T>, DenseMatrixColumnSelector<T>, DenseMatrixRowValueSelector<T> >
// {
// private:
//     typedef SquareMatrix<T, DenseMatrixRowSelector<T>, DenseMatrixColumnSelector<T>, DenseMatrixRowValueSelector<T> > SquareMatrix;
    
// public:
//     DenseMatrix(size_t, size_t);
//     DenseMatrix(const DenseMatrix&);
//     ~DenseMatrix();
//     DenseMatrix& operator=(const DenseMatrix&);

//     const T& get(size_t, size_t) const;
//     void set(size_t, size_t, const T&);

//     bool operator==(const DenseMatrix&) const;
//     bool operator!=(const DenseMatrix&) const;

// private:
//     DenseMatrix& perform_operation(void (*)(T&,T), const DenseMatrix&);
//     DenseMatrix& perform_operation(void (*)(T&,T), const T&);

// private:
//     T** m_matrix = nullptr;
// };

// #endif