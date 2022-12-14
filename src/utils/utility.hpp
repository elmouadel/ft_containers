/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:13:22 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/22 09:28:28 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "./iterator_traits.hpp"

namespace ft
{
/* ************************************************************************** */
                                // enable_if :
/* ************************************************************************** */
    template<bool B, class T = void>
    struct enable_if {};
    
    template<class T>
    struct enable_if<true, T> 
    {
        typedef T type; 
    };

/* ************************************************************************** */
                                // is_same :
/* ************************************************************************** */
    template <class _T, class _U>
    struct is_same { static const bool value = false; };
    
    template <class _T>
    struct is_same<_T, _T> { static const bool value = true; };
    
/* ************************************************************************** */
                                // is_iterator :
/* ************************************************************************** */

                                // is_input_iterator :
/* ************************************************************************** */
    template<class, typename C = void>
    struct is_convertible_input
    {
        static const bool value = false;
    };

    template<class T>
    struct is_convertible_input<T,
    typename ft::enable_if<ft::is_same<T, std::input_iterator_tag>::value>::type>
    {
        static const bool value = true; 
    };

    template <typename T, bool = ft::_has_iterator_category<ft::iterator_traits<T> >::value>
    struct _is_input_iterator
        : public is_convertible_input<
        typename ft::iterator_traits<T>::iterator_category> {};
    
    template <typename T>
    struct _is_input_iterator<T, false>  { static const bool value = false; };

    template <typename T>
    struct is_input_iterator : _is_input_iterator<T> {};

                                // is_forward_iterator :
/* ************************************************************************** */
    template<class, typename C = void>
    struct is_convertible_forward
    {
        static const bool value = false;
    };
    
    template<class T>
    struct is_convertible_forward<T,
    typename ft::enable_if<ft::is_same<T, std::forward_iterator_tag>::value ||
        ft::is_same<T, std::bidirectional_iterator_tag>::value ||
        ft::is_same<T, std::random_access_iterator_tag>::value>::type>
        {
            static const bool value = true;
        };
    
    template <typename T, bool = ft::_has_iterator_category<ft::iterator_traits<T> >::value>
    struct _is_forward_iterator
        : public is_convertible_forward<
        typename ft::iterator_traits<T>::iterator_category> {};
    
    template <typename T>
    struct _is_forward_iterator<T, false> { static const bool value = false; };

    template <typename T>
    struct is_forward_iterator : _is_forward_iterator<T> {};

/* ************************************************************************** */
                                // is_integral :
/* ************************************************************************** */
    template <class T>
	struct is_integral { static const bool value = false; };
	
	template <>
	struct is_integral<bool> { static const bool value = true; };
	template <>
	struct is_integral<char> { static const bool value = true; };
	template <>
	struct is_integral<wchar_t> { static const bool value = true; };
	template <>
	struct is_integral<signed char> { static const bool value = true; };
	template <>
	struct is_integral<short int> { static const bool value = true; };
	template <>
	struct is_integral<int> { static const bool value = true; };
	template <>
	struct is_integral<long int> { static const bool value = true; };
	template <>
	struct is_integral<long long int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned char> { static const bool value = true; };
	template <>
	struct is_integral<unsigned short int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long int> { static const bool value = true; };
	template <>
	struct is_integral<unsigned long long int> { static const bool value = true; };

/* ************************************************************************** */
                                // equal :
/* ************************************************************************** */
    template<class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        for (; first1 != last1; ++first1, ++first2) 
            if (!(*first1 == *first2))
                return (false);
        return (true);
    }

/* ************************************************************************** */
                                // lexicographical_compare :
/* ************************************************************************** */
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        {
            if (*first1 < *first2)
                return (true);
            if (*first2 < *first1)
                return (false);
        }
        return ((first1 == last1) && (first2 != last2));
    }
    
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