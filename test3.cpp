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
    C& operator+=(const type& t)
    {
        return perform_operation([](T& c_t, const T& t){c_t += t;}, t);
    }
    C& operator-=(const type& t)
    {
        return perform_operation([](T& c_t, const T& t){c_t -= t;}, t);
    }
    virtual size_t op_ctr() = 0;
protected:
    type m_t;

private:
    virtual C& perform_operation(void (*)(type&, const type&), const type& t) = 0;
};

// template <typename T>
// C<T> operator 
class D : public C<int>
{
public:
    D(const int& t) : C(t) {m_op_ctr = 0;}
    D(const D& d) : C(d.m_t) {m_op_ctr = d.m_op_ctr;}

    inline size_t op_ctr() {return m_op_ctr;}

private:
    D& perform_operation(void (*op)(int&, const int&), const int& t)
    {
        m_op_ctr++;
        op(C::m_t, t);
        return *this;
    }

private:
    size_t m_op_ctr;
};

int main()
{
    D d(3);
    D e(d+=4);
    C<int>& c = d;

    cout << c.op_ctr() << '\n';
    cout << (d += 4) << '\n';
    cout << ((d -= 7) += 10) << '\n';
    return 0;
}
