/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:39:12 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/14 11:28:15 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "./iterator_traits.hpp"

namespace ft
{
/* ************************************************************************** */
                                // advance :
/* ************************************************************************** */
    template <class _InputIter>
    inline void _advance(_InputIter &_it, typename iterator_traits<_InputIter>::difference_type _n,
                std::input_iterator_tag)
    {
        for (; _n > 0; --_n) ++_it;
    }
    template <class _BiDirIter>
    inline void _advance(_BiDirIter &_it, typename iterator_traits<_BiDirIter>::difference_type _n,
                std::bidirectional_iterator_tag)
    {
        if (_n >= 0)
            for (; _n > 0; --_n) ++_it;
        else
            for (; _n < 0; ++_n) --_it;
    }
    template <class _RandIter>
    inline void _advance(_RandIter &_it, typename iterator_traits<_RandIter>::difference_type _n,
                std::random_access_iterator_tag)
    {
        _it += _n;
    }
    template <class _Iter>
    inline void advance(_Iter &_it, typename iterator_traits<_Iter>::difference_type _n)
    {
        _advance(_it, _n, typename iterator_traits<_Iter>::iterator_category());
    }

/* ************************************************************************** */
                                // distance :
/* ************************************************************************** */
    template <class _InputIter>
    inline typename ft::iterator_traits<_InputIter>::difference_type
    _distance(_InputIter _first, _InputIter _last, std::input_iterator_tag)
    {
        typename ft::iterator_traits<_InputIter>::difference_type _i(0);
        for (;_first != _last; ++_first)
            ++_i;
        return(_i);
    }
    template <class _RandIter>
    inline typename ft::iterator_traits<_RandIter>::difference_type
    _distance(_RandIter _first, _RandIter _last, std::random_access_iterator_tag)
    {
        typename ft::iterator_traits<_RandIter>::difference_type _i(0);
        for (;_first != _last; ++_first)
            ++_i;
        return(_i);
    }
    
    template <class _Iter>
    inline typename ft::iterator_traits<_Iter>::difference_type
    distance(_Iter _first, _Iter _last)
    {
        return (_distance(_first, _last, typename ft::iterator_traits<_Iter>::iterator_category()));
    }
/* ************************************************************************** */
                                // distance :
/* ************************************************************************** */
    template <class _Ptr>
    void move_backward(_Ptr _first, _Ptr _last, _Ptr _result)
    {
        while (_first != _last)
            *--_result = *--_last;
    }
}

#endif