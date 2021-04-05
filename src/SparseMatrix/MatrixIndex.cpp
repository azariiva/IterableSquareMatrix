#include "MatrixIndex.hpp"

MatrixIndex::MatrixIndex(size_t urow, size_t ucolumn) {
    row = urow;
    column = ucolumn;
}

MatrixIndex::MatrixIndex(const MatrixIndex& src) {
    row = src.row;
    column = src.column;
}

MatrixIndex& MatrixIndex::operator=(const MatrixIndex& rv) {
    if (&rv == this) {
        return (*this);
    }
    row = rv.row;
    column = rv.column;
    return *this;
}

bool MatrixIndex::operator==(const MatrixIndex& rv) const {
    return (&rv == this || (row == rv.row && column == rv.column));
}

bool MatrixIndex::operator!=(const MatrixIndex& rv) const {
    return (&rv != this && (row != rv.row || column != rv.column));
}

bool MatrixIndex::operator>(const MatrixIndex& rv) const {
    if (&rv == this) {
        return false;
    }
    if (row > rv.row) {
        return true;
    } else if (row < rv.row) {
        return false;
    } else if (column > rv.column) {
        return true;
    }
    return false;
}

bool MatrixIndex::operator<(const MatrixIndex& rv) const {
    if (&rv == this) {
        return false;
    }
    if (row < rv.row) {
        return true;
    } else if (row > rv.row) {
        return false;
    } else if (column < rv.column) {
        return true;
    }
    return false;
}

bool MatrixIndex::operator<=(const MatrixIndex& rv) const {
    if (&rv == this) {
        return true;
    }
    if (row <= rv.row) {
        return true;
    } else if (row > rv.row) {
        return false;
    } else if (column <= rv.column) {
        return true;
    }
    return false;
}

bool MatrixIndex::operator>=(const MatrixIndex& rv) const {
    if (&rv == this) {
        return true;
    }
    if (row >= rv.row) {
        return true;
    } else if (row < rv.row) {
        return false;
    } else if (column >= rv.column) {
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &out, const MatrixIndex&mi) {
    out << mi.row << ' ' << mi.column;
    return out;
}
