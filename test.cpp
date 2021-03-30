#include <iostream>

class C
{
public:
    C(int v)
    {
        m_v = v;
    }

    ~C()
    {
        m_v = 0;
    }

    C(const C&) = delete;

    operator int() const
    {
        return m_v;
    }

    C& operator=(const C& c)
    {
        this->~C();
        m_v += c.m_v;
    }

private:
    int m_v;

    friend C&& operator+(C&& c, int v)
    {
        std::cout << "operator for lvalue called" << std::endl;
        c.m_v += v;
    }
    friend const C& operator+(const C& c, int v)
    {
        std::cout << "operator for rvalue called" << std::endl;
        const_cast<C *>(&c)->m_v += v;
    }
};

class D : public C
{
public:
    D(int v, int u) : C(v)
    {
        m_u = u;
    }
    operator int() const
    {
        return this->C::operator int() + m_u;
    }
private:
    int m_u;
};

int main()
{
    C c(7);
    double f = double();

    std::cout << f << std::endl;
    std::cout << (C(4) + 3) << std::endl;
    std::cout << (c + 10) << std::endl;

    D d(3, 4);
    return 0;
}