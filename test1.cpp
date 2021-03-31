#include <iostream>

using std::cout;
using std::endl;

template <typename T> class C
{
public:
    typedef T type;

public:
    C(const type& t)
    {
        m_t = t;
    }
    operator type() const
    {
        return m_t;
    }
private:
    type m_t;
};

template <typename T>
C<T> operator+(const C<T>& c, const T& t)
{
    return C<T>(c.operator T() + t);
}

template <typename T>
C<T> operator+(const T& t, const C<T>& c)
{
    return C<T>(c.operator T() + t);
}

int main()
{
    C<int> c(3);
    C<int> d = c + 4;
    C<int>::type v = d;
    cout << v << endl;
    return 0;
}