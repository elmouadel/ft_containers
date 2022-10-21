/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:56:10 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/19 22:11:29 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class _Tp, class _Container = vector<_Tp> >
    class stack
    {
        public:
            typedef _Container                                  container_type;
            typedef typename container_type::value_type         value_type;
            typedef typename container_type::reference          reference;
            typedef typename container_type::const_reference    const_reference;
            typedef typename container_type::size_type          size_type;
            static_assert((is_same<_Tp, value_type>::value), 
            "value_type must be same type as container_type::value_type");
            
        protected:
            container_type c;
        
        public:
            explicit stack (const container_type& _c = container_type())
                : c(_c)
            {
            }
            ~stack()
            {
            }
            stack& operator=(const stack& _rhs)
            {
                c = _rhs.c;
                return (*this);
            }

            bool empty() const
            {
                return c.empty();
            }
            size_type size() const
            {
                return c.size();
            }
            value_type& top()
            {
                return c.back();
            }
            const value_type& top() const
            {
                return c.back();
            }
            void push(const value_type& _val)
            {
                return c.push_back(_val); 
            }
            void pop()
            {
                return c.pop_back();
            }
            template <class _T, class _C>
            friend bool operator==(const stack<_T, _C>&, const stack<_T, _C>&);

            template <class _T, class _C>
            friend bool operator<(const stack<_T, _C>&, const stack<_T, _C>&);
    };
    template <class _Tp, class _Container>
    inline bool
    operator==(const stack<_Tp, _Container> &_lhs, const stack<_Tp, _Container> &_rhs)
    {
        return _lhs.c == _rhs.c;
    }
    template <class _Tp, class _Container>
    inline bool
    operator<(const stack<_Tp, _Container> &_lhs, const stack<_Tp, _Container> &_rhs)
    {
        return _lhs.c < _rhs.c;
    }
    template <class _Tp, class _Container>
    inline bool
    operator!=(const stack<_Tp, _Container> &_lhs, const stack<_Tp, _Container> &_rhs)
    {
        return !(_lhs == _rhs);
    }
    template <class _Tp, class _Container>
    inline bool
    operator>(const stack<_Tp, _Container> &_lhs, const stack<_Tp, _Container> &_rhs)
    {
        return _rhs < _lhs;
    }
    template <class _Tp, class _Container>
    inline bool
    operator>=(const stack<_Tp, _Container> &_lhs, const stack<_Tp, _Container> &_rhs)
    {
        return !(_lhs < _rhs);
    }
    template <class _Tp, class _Container>
    inline bool
    operator<=(const stack<_Tp, _Container> &_lhs, const stack<_Tp, _Container> &_rhs)
    {
        return !(_rhs < _lhs);
    }
}

#endif