#include "./headers/DenseMatrix/DenseMatrix.hpp"
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

int main(void)
{
    DenseMatrix<int> m(9, 9);
    // DenseMatrix<int> mm(9, 9);

    cout << m.num_rows() << ' ' << m.num_columns() << '\n';
    for (size_t i = 0; i < m.num_rows(); i++)
        for (size_t j = 0; j < m.num_columns(); j++)
            m.set(i, j, (i + 1) * (m.num_rows() + 1) + j + 1);
    DenseMatrix<int> mm = m;
    for (size_t i = 0; i < m.num_rows(); i++)
    {
        for (size_t j = 0; j < m.num_columns(); j++)
            cout << m[i][j] << ' ';
        cout << '\n';
    }
    cout << endl;
    for (size_t i = 0; i < mm.num_columns(); i++)
    {
        for (size_t j = 0; j < mm.num_rows(); j++)
            cout << (2 + *(1 + mm + i - 1) + j - 5)[3] << ' ';
        cout << '\n';
    }
    return 0;
}