/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:24:14 by eabdelha          #+#    #+#             */
/*   Updated: 2022/09/16 09:58:47 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
    template <class Iter>
    class v_iterator
    {
        public:
            typedef Iter                                                           iterator_type;
            typedef typename ft::iterator_traits<iterator_type>::value_type        value_type;
            typedef typename ft::iterator_traits<iterator_type>::difference_type   difference_type;
            typedef typename ft::iterator_traits<iterator_type>::pointer           pointer;
            typedef typename ft::iterator_traits<iterator_type>::reference         reference;
            // typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
        
        private:
            iterator_type p_i;
        
        public:
            v_iterator() {}
            v_iterator(const pointer &_p_i) : p_i(_p_i) {}
            v_iterator(const v_iterator &rhs) : p_i(rhs.p_i) {}

            v_iterator &operator=(const v_iterator &rhs)
            {
                if (this != &rhs)
                    p_i =  rhs.p_i;
                return (*this);
            }
            reference operator*() const { return *p_i; }
            pointer operator->() const { return p_i; }
            v_iterator &operator++()
            {
                ++p_i; 
                return (*this);
            }
            v_iterator operator++(int)
            {
                v_iterator tmp(*this);
                ++p_i; 
                return (tmp); 
            }
            v_iterator &operator--()
            {
                --p_i; 
                return (*this);
            }
            v_iterator operator--(int)
            {
                v_iterator tmp(*this);
                --p_i; 
                return (tmp); 
            }
            v_iterator operator+(difference_type _n) const
            {
                return (p_i + _n);
            }
            v_iterator &operator+=(difference_type _n)
            {
                p_i += _n;
                return (*this);
            }
            v_iterator operator-(difference_type _n) const
            {
                return (p_i - _n);
            }
            v_iterator &operator-=(difference_type _n)
            {
                p_i -= _n;
                return (*this);
            }
            reference operator[](difference_type _n) const
            {
                return (p_i[_n]);
            }
        private:
            friend bool operator==(const v_iterator &lhs, const v_iterator &rhs)
            {
                return (lhs.p_i == rhs.p_i);
            }
            friend bool operator!=(const v_iterator &lhs, const v_iterator &rhs)
            {
                return (lhs.p_i != rhs.p_i);
            }
            friend bool operator<(const v_iterator &lhs, const v_iterator &rhs)
            {
                return (lhs.p_i < rhs.p_i);
            }
            friend bool operator>(const v_iterator &lhs, const v_iterator &rhs)
            {
                return (lhs.p_i > rhs.p_i);
            }
            friend bool operator<=(const v_iterator &lhs, const v_iterator &rhs)
            {
                return (lhs.p_i <= rhs.p_i);
            }
            friend bool operator>=(const v_iterator &lhs, const v_iterator &rhs)
            {
                return (lhs.p_i >= rhs.p_i);
            }
            friend difference_type operator-(const v_iterator &lhs, const v_iterator &rhs)
            {
                return (lhs.p_i - rhs.p_i);
            }
            friend v_iterator operator+(difference_type _n, v_iterator rhs)
            {
                rhs.p_i += _n;
                return (rhs);
            }  
    };
}


#endif