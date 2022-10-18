/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:24:14 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/18 15:27:04 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "./iterator_traits.hpp"

namespace ft
{
    template <class Iter>
    class vector_iterator
    {
        public:
            typedef Iter                                                           iterator_type;
            typedef typename ft::iterator_traits<iterator_type>::value_type        value_type;
            typedef typename ft::iterator_traits<iterator_type>::difference_type   difference_type;
            typedef typename ft::iterator_traits<iterator_type>::pointer           pointer;
            typedef typename ft::iterator_traits<iterator_type>::reference         reference;
            typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
        
        private:
            iterator_type p_i;
        
        private:
            vector_iterator(iterator_type rhs) : p_i(rhs) {}
            template <class Tp, class Alloc>
            friend class vector;
        public:
            vector_iterator() {}
            template <class Tp>
            vector_iterator(const vector_iterator<Tp> &rhs) : p_i(rhs.base()) {}
            
            iterator_type base() const 
            {
                return (p_i);
            }
            vector_iterator &operator=(const vector_iterator &rhs)
            {
                if (this != &rhs)
                    p_i =  rhs.p_i;
                return (*this);
            }
            reference operator*() const { return *p_i; }
            pointer operator->() const { return p_i; }
            vector_iterator &operator++()
            {
                ++p_i; 
                return (*this);
            }
            vector_iterator operator++(int)
            {
                vector_iterator tmp(*this);
                ++p_i; 
                return (tmp); 
            }
            vector_iterator &operator--()
            {
                --p_i; 
                return (*this);
            }
            vector_iterator operator--(int)
            {
                vector_iterator tmp(*this);
                --p_i; 
                return (tmp); 
            }
            vector_iterator operator+(difference_type _n) const
            {
                return (p_i + _n);
            }
            vector_iterator &operator+=(difference_type _n)
            {
                p_i += _n;
                return (*this);
            }
            vector_iterator operator-(difference_type _n) const
            {
                return (p_i - _n);
            }
            vector_iterator &operator-=(difference_type _n)
            {
                p_i -= _n;
                return (*this);
            }
            reference operator[](difference_type _n) const
            {
                return (p_i[_n]);
            }
        private:
            template <class Iter1, class Iter2>
            friend bool operator==(const vector_iterator<Iter1> &lhs, const vector_iterator<Iter2> &rhs)
            {
                return (lhs.p_i == rhs.p_i);
            }
            template <class Iter1, class Iter2>
            friend bool operator!=(const vector_iterator<Iter1> &lhs, const vector_iterator<Iter2> &rhs)
            {
                return (lhs.p_i != rhs.p_i);
            }
            template <class Iter1, class Iter2>
            friend bool operator<(const vector_iterator<Iter1> &lhs, const vector_iterator<Iter2> &rhs)
            {
                return (lhs.p_i < rhs.p_i);
            }
            template <class Iter1, class Iter2>
            friend bool operator>(const vector_iterator<Iter1> &lhs, const vector_iterator<Iter2> &rhs)
            {
                return (lhs.p_i > rhs.p_i);
            }
            template <class Iter1, class Iter2>
            friend bool operator<=(const vector_iterator<Iter1> &lhs, const vector_iterator<Iter2> &rhs)
            {
                return (lhs.p_i <= rhs.p_i);
            }
            template <class Iter1, class Iter2>
            friend bool operator>=(const vector_iterator<Iter1> &lhs, const vector_iterator<Iter2> &rhs)
            {
                return (lhs.p_i >= rhs.p_i);
            }
            template <class Iter1, class Iter2>
            friend difference_type operator-(const vector_iterator<Iter1> &lhs, const vector_iterator<Iter2> &rhs)
            {
                return (lhs.base() - rhs.base());
            }
            template <class Iter1>
            friend vector_iterator<Iter1> operator+(difference_type _n, vector_iterator<Iter1> rhs)
            {
                rhs.p_i += _n;
                return (rhs);
            }  
    };
}

#endif