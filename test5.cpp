#include "./headers/DenseMatrix/DenseMatrix.hpp"
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;

int main(void)
{
    DenseMatrix<int> u(8,9);
    DenseMatrix<int> v(9,10);
    DenseMatrix<int> m(9, 9);
    // DenseMatrix<int> mm(9, 9);

    cout << m.num_rows() << ' ' << m.num_columns() << '\n';
    for (size_t i = 0; i < m.num_rows(); i++)
        for (size_t j = 0; j < m.num_columns(); j++)
            m.set(i, j, (i + 1) * (m.num_rows() + 1) + j + 1);
    u = v = m;
    DenseMatrix<int> mm(1,1);
    mm = u + 1;
    DenseMatrix<int> mmm(2,1);
    mmm = v.transpose() + 1;
    for (size_t i = 0; i < m.num_rows(); i++)
    {
        for (size_t j = 0; j < m.num_columns(); j++)
            cout << m[i][j] << ' ';
        cout << '\n';
    }
    cout << endl;
    for (size_t i = 0; i < mm.num_rows(); i++)
    {
        for (size_t j = 0; j < mm.num_columns(); j++)
            cout << (2 + *(1 + mm + i - 1) + j - 5)[3] << ' ';
        cout << '\n';
    }
    cout << endl;
    for (size_t i = 0; i < mmm.num_rows(); i++)
    {
        for (size_t j = 0; j < mmm.num_columns(); j++)
            cout << (2 + *(1 + mmm + i - 1) + j - 5)[3] << ' ';
        cout << '\n';
    }
    cout << m.num_rows() << ' ' << m.num_columns() << '\n';
    cout << mm.num_rows() << ' ' << mm.num_columns() << '\n';
    cout << mmm.num_rows() << ' ' << mmm.num_columns() << '\n';
    return 0;
}