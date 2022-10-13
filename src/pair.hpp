/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:07:03 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/13 23:51:52 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

#include <algorithm>

namespace ft
{
/* ************************************************************************** */
                                // pair :
/* ************************************************************************** */
    template <class _T1, class _T2>
    struct pair
    {
        typedef _T1 first_type;
        typedef _T2 second_type;
        
        first_type first;
        second_type second;

        pair() : first(), second() {}
        pair(first_type const &_t1, second_type const &_t2) : first(_t1), second(_t2) {}

        template <class _U1, class _U2>
        pair(const pair<_U1, _U2>& _rhs) : first(_rhs.first), second(_rhs.second) {}
        
        pair& operator=(const pair& _rhs)
        {
            first = _rhs.first;
            second = _rhs.second;
            return (*this);
        }
        void swap(pair& _rhs)
        {
            std::swap(first,  _rhs.first);
            std::swap(second, _rhs.second);
        }
    };
    template <class _T1, class _T2>
    inline bool operator==(const pair<_T1, _T2>& _lhs, const pair<_T1, _T2>& _rhs)
    {
        return (_lhs.first == _rhs.first && _lhs.second == _rhs.second);
    }
    template <class _T1, class _T2>
    inline bool operator!=(const pair<_T1, _T2>& _lhs, const pair<_T1, _T2>& _rhs)
    {
        return !(_lhs == _rhs);
    }
    template <class _T1, class _T2>
    inline bool operator<(const pair<_T1, _T2>& _lhs, const pair<_T1, _T2>& _rhs)
    {
        return ((_lhs.first < _rhs.first) || (!(_rhs.first < _lhs.first) && _lhs.second < _rhs.second));
    }
    template <class _T1, class _T2>
    inline bool operator<=(const pair<_T1, _T2>& _lhs, const pair<_T1, _T2>& _rhs)
    {
        return !(_rhs < _lhs);
    }
    template <class _T1, class _T2>
    inline bool operator>(const pair<_T1, _T2>& _lhs, const pair<_T1, _T2>& _rhs)
    {
        return (_rhs < _lhs);
    }
    template <class _T1, class _T2>
    inline bool operator>=(const pair<_T1, _T2>& _lhs, const pair<_T1, _T2>& _rhs)
    {
        return !(_lhs < _rhs);
    }
    template <class _T1, class _T2>
    inline pair<_T1,_T2> make_pair(_T1 _lhs, _T2 _rhs)
    {
        return pair<_T1, _T2>(_lhs, _rhs);
    }
}

#endif