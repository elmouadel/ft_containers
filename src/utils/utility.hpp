/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:13:22 by eabdelha          #+#    #+#             */
/*   Updated: 2022/09/28 15:07:46 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS_HPP
#define VECTOR_UTILS_HPP

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
    struct is_same : std::false_type {};
    
    template <class _T>
    struct is_same<_T, _T> : std::true_type {};
    
/* ************************************************************************** */
                                // is_iterator :
/* ************************************************************************** */
    template<class T, class U, typename C = void>
    struct is_convertible_input : std::false_type {};

    template<class T, class U>
    struct is_convertible_input<T, U, 
    typename ft::enable_if<ft::is_same<T, std::input_iterator_tag>::value>::type> : std::true_type {};

    template<class T, class U, typename C = void>
    struct is_convertible_forward : std::false_type {};

    template<class T, class U>
    struct is_convertible_forward<T, U, 
    typename ft::enable_if<ft::is_same<T, std::forward_iterator_tag>::value ||
        ft::is_same<T, std::bidirectional_iterator_tag>::value ||
        ft::is_same<T, std::random_access_iterator_tag>::value>::type> : std::true_type {};
    
    template <typename T, bool = ft::_has_iterator_category<ft::iterator_traits<T> >::value>
    struct _is_input_iterator
        : public is_convertible_input<
        typename ft::iterator_traits<T>::iterator_category, std::input_iterator_tag> {};
    
    template <typename T, bool = ft::_has_iterator_category<ft::iterator_traits<T> >::value>
    struct _is_forward_iterator
        : public is_convertible_forward<
        typename ft::iterator_traits<T>::iterator_category, std::forward_iterator_tag> {};
    
    template <typename T>
    struct _is_input_iterator<T, false> : std::false_type {};

    template <typename T>
    struct _is_forward_iterator<T, false> : std::false_type {};


    template <typename T>
    struct is_input_iterator : _is_input_iterator<T> {};

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
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return (true);
            if (*first2 < *first1)
                return (false);
        }
        return ((first1 == last1) && (first2 != last2));
    }

}

#endif