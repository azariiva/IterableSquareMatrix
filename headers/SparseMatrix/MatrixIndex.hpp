#ifndef MATRIX_INDEX_HPP
#define MATRIX_INDEX_HPP

#include <ostream>
#include <cstddef>

class MatrixIndex {
    size_t  row;
    size_t  column;

    public:
    MatrixIndex(size_t = 0, size_t = 0);
    MatrixIndex(const MatrixIndex&);
    MatrixIndex& operator=(const MatrixIndex&);
    bool operator==(const MatrixIndex&) const;
    bool operator!=(const MatrixIndex&) const;
    bool operator>(const MatrixIndex&) const;
    bool operator<(const MatrixIndex&) const;
    bool operator>=(const MatrixIndex&) const;
    bool operator<=(const MatrixIndex&) const;
    friend std::ostream &operator<<(std::ostream&, const MatrixIndex&);
};

#endif