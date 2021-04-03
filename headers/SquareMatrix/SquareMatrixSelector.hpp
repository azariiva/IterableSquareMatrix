#ifndef SQUARE_MATRIX_SELECTOR_HPP
#define SQUARE_MATRIX_SELECTOR_HPP

#include <cstddef>

enum class set_mode
{
    row,
    column
};

template <class matrix_T, class deref_T> class SquareMatrixSelectorTemplate;

template <class matrix_T, class deref_T>
const SquareMatrixSelectorTemplate<matrix_T,deref_T> & operator+(const SquareMatrixSelectorTemplate<matrix_T,deref_T>&, size_t);

template <class matrix_T, class deref_T>
const SquareMatrixSelectorTemplate<matrix_T,deref_T> & operator+(size_t, const SquareMatrixSelectorTemplate<matrix_T,deref_T>&);

template <class matrix_T, class deref_T>
const SquareMatrixSelectorTemplate<matrix_T,deref_T> & operator-(const SquareMatrixSelectorTemplate<matrix_T,deref_T>&, size_t);

template <class matrix_T, class deref_T> class SquareMatrixSelectorTemplate
{
protected:
    typedef matrix_T Matrix;
    typedef deref_T Deref;

public:
    SquareMatrixSelectorTemplate() = delete;
    SquareMatrixSelectorTemplate &operator=(const SquareMatrixSelectorTemplate&) = delete;
    deref_T operator[](size_t) const;
    deref_T operator*() const;
    inline const Matrix *matrix() const;
    inline bool modifyable() const;
    inline size_t idx() const;
    inline set_mode set() const;
    inline virtual size_t pidx() const;

protected:
    SquareMatrixSelectorTemplate(const Matrix *, bool, size_t, set_mode = set_mode::row);
    SquareMatrixSelectorTemplate(const SquareMatrixSelectorTemplate&);

private:
    virtual void check_idx() const = 0;
    friend const SquareMatrixSelectorTemplate& operator+ <matrix_T,deref_T> (const SquareMatrixSelectorTemplate&, size_t);
    friend const SquareMatrixSelectorTemplate& operator+ <matrix_T,deref_T> (size_t, const SquareMatrixSelectorTemplate&);
    friend const SquareMatrixSelectorTemplate& operator- <matrix_T,deref_T> (const SquareMatrixSelectorTemplate&, size_t);
    friend deref_T;

protected:
    const matrix_T *m_matrix;
    const bool m_modifyable;
    const set_mode m_set;
    size_t m_idx;
};

template <typename value_T, class matrix_T> class SquareMatrixValueSelector;

template <typename value_T, class matrix_T> class SquareMatrixSelector : public SquareMatrixSelectorTemplate<matrix_T,SquareMatrixValueSelector<value_T,matrix_T> >
{
public:
    typedef ::SquareMatrixSelectorTemplate<matrix_T, SquareMatrixValueSelector<value_T, matrix_T> > SquareMatrixSelectorTemplate;

private:
    typedef typename SquareMatrixSelectorTemplate::Matrix Matrix;

public:
    SquareMatrixSelector(const SquareMatrixSelector&);
    SquareMatrixSelector(const Matrix *, bool, size_t, set_mode = set_mode::row);

private:
    inline void check_idx() const;
};

template <typename value_T, class matrix_T> class SquareMatrixValueSelector : public SquareMatrixSelectorTemplate<matrix_T,value_T>
{
public:
    typedef ::SquareMatrixSelectorTemplate<matrix_T,value_T> SquareMatrixSelectorTemplate;

private:
    typedef ::SquareMatrixSelector<value_T,matrix_T> SquareMatrixSelector;
    typedef typename SquareMatrixSelectorTemplate::Matrix Matrix;

public:
    SquareMatrixValueSelector(const typename SquareMatrixSelector::SquareMatrixSelectorTemplate&);
    SquareMatrixValueSelector(const SquareMatrixValueSelector&);
    SquareMatrixValueSelector(const Matrix *, bool, size_t, set_mode = set_mode::row);
    inline size_t pidx() const;

private:
    inline void check_idx() const;

private:
    const size_t m_pidx;
};

#include "../../templates/SquareMatrix/SquareMatrixSelector.tcc"

#endif