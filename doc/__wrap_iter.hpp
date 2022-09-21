#include <__config>
#include <iosfwd> // for forward declarations of vector and string.
#include <__functional_base>
#include <type_traits>
#include <cstddef>
#include <initializer_list>
#include <__cxx_version>
#ifdef __APPLE__
#include <Availability.h>
#endif

#include <__debug>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD
template <class _Iter>
struct _LIBCPP_TEMPLATE_VIS iterator_traits;

// struct _LIBCPP_TEMPLATE_VIS input_iterator_tag {};
// struct _LIBCPP_TEMPLATE_VIS output_iterator_tag {};
// struct _LIBCPP_TEMPLATE_VIS forward_iterator_tag       : public input_iterator_tag {};
// struct _LIBCPP_TEMPLATE_VIS bidirectional_iterator_tag : public forward_iterator_tag {};
// struct _LIBCPP_TEMPLATE_VIS random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Iter>
class __wrap_iter_;

template <class _Iter1, class _Iter2>
bool operator==(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

template <class _Iter1, class _Iter2>
bool operator<(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

template <class _Iter1, class _Iter2>
bool operator!=(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

template <class _Iter1, class _Iter2>
bool operator>(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

template <class _Iter1, class _Iter2>
bool operator>=(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

template <class _Iter1, class _Iter2>
bool operator<=(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();
# 1364 "/Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iterator" 3
template <class _Iter1, class _Iter2>
typename __wrap_iter_<_Iter1>::difference_type
operator-(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

template <class _Iter>
__wrap_iter_<_Iter>
operator+(typename __wrap_iter_<_Iter>::difference_type, __wrap_iter_<_Iter>) throw();

template <class _Ip, class _Op>
_Op copy(_Ip, _Ip, _Op);
template <class _B1, class _B2>
_B2 copy_backward(_B1, _B1, _B2);
template <class _Ip, class _Op>
_Op move(_Ip, _Ip, _Op);
template <class _B1, class _B2>
_B2 move_backward(_B1, _B1, _B2);

template <class _Tp>
typename enable_if<
    is_trivially_copy_assignable<_Tp>::value,
    _Tp *>::type
    __unwrap_iter(__wrap_iter_<_Tp *>);
# 1404 "/Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iterator" 3
template <class _Iter>
class __wrap_iter_
{
public:
    typedef _Iter iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type value_type;
    typedef typename iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename iterator_traits<iterator_type>::pointer pointer;
    typedef typename iterator_traits<iterator_type>::reference reference;

private:
    iterator_type __i;

public:
    __wrap_iter_() throw()

    {
        std::cout << "const\n";

    }
    template <class _Up>
    __wrap_iter_(const __wrap_iter_<_Up> &__u,
                 typename enable_if<is_convertible<_Up, iterator_type>::value>::type * = 0) throw()
        : __i(__u.base())
    {
        std::cout << "copy\n";
    }
# 1458 "/Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iterator" 3
    reference operator*() const throw()
    {

        return *__i;
    }
    pointer operator->() const throw()
    {

        return (pointer)std::__1::addressof(*__i);
    }
    __wrap_iter_ &operator++() throw()
    {

        ++__i;
        return *this;
    }
    __wrap_iter_ operator++(int) throw()
    {
        __wrap_iter_ __tmp(*this);
        ++(*this);
        return __tmp;
    }

    __wrap_iter_ &operator--() throw()
    {

        --__i;
        return *this;
    }
    __wrap_iter_ operator--(int) throw()
    {
        __wrap_iter_ __tmp(*this);
        --(*this);
        return __tmp;
    }
    __wrap_iter_ operator+(difference_type __n) const throw()
    {
        __wrap_iter_ __w(*this);
        __w += __n;
        return __w;
    }
    __wrap_iter_ &operator+=(difference_type __n) throw()
    {

        __i += __n;
        return *this;
    }
    __wrap_iter_ operator-(difference_type __n) const throw()
    {
        return *this + (-__n);
    }
    __wrap_iter_ &operator-=(difference_type __n) throw()
    {
        *this += -__n;
        return *this;
    }
    reference operator[](difference_type __n) const throw()
    {

        return __i[__n];
    }

    iterator_type base() const throw() { return __i; }

private:
    __wrap_iter_(iterator_type __x) throw() : __i(__x) {}

    template <class _Up>
    friend class __wrap_iter_;
    template <class _CharT, class _Traits, class _Alloc>
    friend class basic_string;
    template <class _Tp, class _Alloc>
    friend class __attribute__((__type_visibility__("default"))) vector;
    template <class _Tp, size_t>
    friend class __attribute__((__type_visibility__("default"))) span;

    template <class _Iter1, class _Iter2>
    friend bool
    operator==(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

    template <class _Iter1, class _Iter2>
    friend bool
    operator<(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

    template <class _Iter1, class _Iter2>
    friend bool
    operator!=(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

    template <class _Iter1, class _Iter2>
    friend bool
    operator>(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

    template <class _Iter1, class _Iter2>
    friend bool
    operator>=(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

    template <class _Iter1, class _Iter2>
    friend bool
    operator<=(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();
# 1575 "/Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iterator" 3
    template <class _Iter1, class _Iter2>
    friend
        typename __wrap_iter_<_Iter1>::difference_type
        operator-(const __wrap_iter_<_Iter1> &, const __wrap_iter_<_Iter2> &) throw();

    template <class _Iter1>
    friend __wrap_iter_<_Iter1>
    operator+(typename __wrap_iter_<_Iter1>::difference_type, __wrap_iter_<_Iter1>) throw();

    template <class _Ip, class _Op>
    friend _Op copy(_Ip, _Ip, _Op);
    template <class _B1, class _B2>
    friend _B2 copy_backward(_B1, _B1, _B2);
    template <class _Ip, class _Op>
    friend _Op move(_Ip, _Ip, _Op);
    template <class _B1, class _B2>
    friend _B2 move_backward(_B1, _B1, _B2);

    template <class _Tp>
    friend
        typename enable_if<
            is_trivially_copy_assignable<_Tp>::value,
            _Tp *>::type
            __unwrap_iter(__wrap_iter_<_Tp *>);
# 1610 "/Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iterator" 3
};

template <class _Iter1, class _Iter2>
inline bool
operator==(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter2> &__y) throw()
{
    return __x.base() == __y.base();
}

template <class _Iter1, class _Iter2>
inline bool
operator<(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter2> &__y) throw()
{

    return __x.base() < __y.base();
}

template <class _Iter1, class _Iter2>
inline bool
operator!=(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter2> &__y) throw()
{
    return !(__x == __y);
}

template <class _Iter1, class _Iter2>
inline bool
operator>(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter2> &__y) throw()
{
    return __y < __x;
}

template <class _Iter1, class _Iter2>
inline bool
operator>=(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter2> &__y) throw()
{
    return !(__x < __y);
}

template <class _Iter1, class _Iter2>
inline bool
operator<=(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter2> &__y) throw()
{
    return !(__y < __x);
}

template <class _Iter1>
inline bool
operator!=(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter1> &__y) throw()
{
    return !(__x == __y);
}

template <class _Iter1>
inline bool
operator>(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter1> &__y) throw()
{
    return __y < __x;
}

template <class _Iter1>
inline bool
operator>=(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter1> &__y) throw()
{
    return !(__x < __y);
}

template <class _Iter1>
inline bool
operator<=(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter1> &__y) throw()
{
    return !(__y < __x);
}
# 1710 "/Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iterator" 3
template <class _Iter1, class _Iter2>
inline typename __wrap_iter_<_Iter1>::difference_type
operator-(const __wrap_iter_<_Iter1> &__x, const __wrap_iter_<_Iter2> &__y) throw()
{

    return __x.base() - __y.base();
}

template <class _Iter>
inline __wrap_iter_<_Iter>
operator+(typename __wrap_iter_<_Iter>::difference_type __n,
          __wrap_iter_<_Iter> __x) throw()
{
    __x += __n;
    return __x;
}

// template <class _Iter>
// struct __libcpp_is_trivial_iterator
//     : public integral_constant<bool,(is_pointer<_Iter>::value)> {};

// template <class _Iter>
// struct __libcpp_is_trivial_iterator<move_iterator<_Iter> >
//     : public integral_constant<bool,(__libcpp_is_trivial_iterator<_Iter>::value)> {};

// template <class _Iter>
// struct __libcpp_is_trivial_iterator<reverse_iterator<_Iter> >
//     : public integral_constant<bool,(__libcpp_is_trivial_iterator<_Iter>::value)> {};

// template <class _Iter>
// struct __libcpp_is_trivial_iterator<__wrap_iter_<_Iter> >
//     : public integral_constant<bool,(__libcpp_is_trivial_iterator<_Iter>::value)> {};

// template <class _Tp, size_t _Np>
// // _Tp*
// begin(_Tp (&__array)[_Np])
// {
//     return __array;
// }

// template <class _Tp, size_t _Np>
// // _Tp*
// end(_Tp (&__array)[_Np])
// {
//     return __array + _Np;
// }
// # 1891 "/Library/Developer/CommandLineTools/usr/bin/../include/c++/v1/iterator" 3
// template <class _Cp>
// // typename _Cp::iterator
// begin(_Cp& __c)
// {
//     return __c.begin();
// }

// template <class _Cp>
// // typename _Cp::const_iterator
// begin(const _Cp& __c)
// {
//     return __c.begin();
// }

// template <class _Cp>
// // typename _Cp::iterator
// end(_Cp& __c)
// {
//     return __c.end();
// }

// template <class _Cp>
// // typename _Cp::const_iterator
// end(const _Cp& __c)
// {
//     return __c.end();
// }

_LIBCPP_END_NAMESPACE_STD

_LIBCPP_POP_MACROS