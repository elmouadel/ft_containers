/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:55:40 by eabdelha          #+#    #+#             */
/*   Updated: 2022/09/28 13:01:53 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
    template <class>
    struct void_t { typedef void type; };
    
    template <class _Tp>
    struct _has_iterator_typedefs
    {
    private:
        struct _two {char _lx; char _lxx;};
        template <class _Up> static _two _test(...);
        template <class _Up> static char _test(typename void_t<typename _Up::iterator_category>::type* = 0,
                                                typename void_t<typename _Up::difference_type>::type* = 0,
                                                typename void_t<typename _Up::value_type>::type* = 0,
                                                typename void_t<typename _Up::reference>::type* = 0,
                                                typename void_t<typename _Up::pointer>::type* = 0
                                                );
    public:
        static const bool value = sizeof(_test<_Tp>(0,0,0,0,0)) == 1;
    };


    template <class _Tp>
    struct _has_iterator_category
    {
    private:
        struct _two {char _lx; char _lxx;};
        template <class _Up> static _two _test(...);
        template <class _Up> static char _test(typename _Up::iterator_category* = 0);
    public:
        static const bool value = sizeof(_test<_Tp>(0)) == 1;
    };


    template <class _Iter, bool> struct _iterator_traits {};
    
    template <class _Iter>
    struct _iterator_traits<_Iter, true>
    {
        typedef typename _Iter::difference_type   difference_type;
        typedef typename _Iter::value_type        value_type;
        typedef typename _Iter::pointer           pointer;
        typedef typename _Iter::reference         reference;
        typedef typename _Iter::iterator_category iterator_category;
    };

    template <class _Iter>
    struct iterator_traits
        : _iterator_traits<_Iter, _has_iterator_typedefs<_Iter>::value> {};

    template<class Tp>
    struct  iterator_traits<Tp*>
    {
        typedef ptrdiff_t difference_type;
        typedef Tp value_type;
        typedef Tp* pointer;
        typedef Tp& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
}

#endif