/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:18:29 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/14 11:27:18 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "./iterator_traits.hpp"

namespace ft
{
    template <class Iter>
    class reverse_iterator
    {
        public:
            typedef Iter                                                    iterator_type;
            typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
            typedef typename ft::iterator_traits<Iter>::pointer             pointer;
            typedef typename ft::iterator_traits<Iter>::reference           reference;
            typedef typename ft::iterator_traits<Iter>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iter>::iterator_category   iterator_category;
            
        protected:
            Iter current;
        public:
            reverse_iterator() : current(){}
            explicit reverse_iterator(Iter _val) : current(_val){}
            template <class Tp>
            reverse_iterator(const reverse_iterator<Tp>& rhs) : current(rhs.base()) {}
            template <class Tp>
            reverse_iterator& operator=(const reverse_iterator &rhs)
            {
                current = rhs.current;
                return (*this);
            }
            Iter base() const 
            {
                return (current);
            }
            reference operator*() const 
            {
                Iter _tmp = current;
                return (*--_tmp);
            }
            pointer operator->() const
            {
                Iter _tmp = current;
                return &(*--_tmp);
            }
            reverse_iterator& operator++()
            {
                --current;
                return (*this);
            }
            reverse_iterator& operator--()
            {
                ++current;
                return (*this);
            }
            reverse_iterator operator++(int)
            {
                reverse_iterator _tmp(*this);
                --current;
                return (_tmp);
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator _tmp(*this);
                ++current;
                return (_tmp);
            }
            reverse_iterator operator+(difference_type _n) const
            {
                return (reverse_iterator(current - _n));
            }
            reverse_iterator operator-(difference_type _n) const
            {
                return (reverse_iterator(current + _n));
            }
            reverse_iterator& operator+=(difference_type _n) 
            {
                current -= _n;
                return (*this);
            }
            reverse_iterator& operator-=(difference_type _n)
            {
                current += _n;
                return (*this);
            }
            reference operator[](difference_type _n) const
            {
                return (*(*this + _n));
            }
    };
    template <class _Iter1, class _Iter2>
    inline bool
    operator==(const reverse_iterator<_Iter1> &_x, const reverse_iterator<_Iter2> &_y)
    {
        return _x.base() == _y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool
    operator<(const reverse_iterator<_Iter1> &_x, const reverse_iterator<_Iter2> &_y)
    {
        return _x.base() > _y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool
    operator!=(const reverse_iterator<_Iter1> &_x, const reverse_iterator<_Iter2> &_y)
    {
        return _x.base() != _y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool
    operator>(const reverse_iterator<_Iter1> &_x, const reverse_iterator<_Iter2> &_y)
    {
        return _x.base() < _y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool
    operator>=(const reverse_iterator<_Iter1> &_x, const reverse_iterator<_Iter2> &_y)
    {
        return _x.base() <= _y.base();
    }

    template <class _Iter1, class _Iter2>
    inline bool
    operator<=(const reverse_iterator<_Iter1> &_x, const reverse_iterator<_Iter2> &_y)
    {
        return _x.base() >= _y.base();
    }
    template <class _Iter1, class _Iter2>
    inline
        typename reverse_iterator<_Iter1>::difference_type
        operator-(const reverse_iterator<_Iter1> &_x, const reverse_iterator<_Iter2> &_y)
    {
        return _y.base() - _x.base();
    }

    template <class _Iter>
    inline reverse_iterator<_Iter>
    operator+(typename reverse_iterator<_Iter>::difference_type _n, const reverse_iterator<_Iter> &_x)
    {
        return reverse_iterator<_Iter>(_x.base() - _n);
    }
}

#endif