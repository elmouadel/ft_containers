/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:12:06 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/10 10:56:11 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_IERATOR_HPP
#define RB_TREE_IERATOR_HPP

namespace ft
{   
    template <class Tp, class Iter>
    class rb_tree_iterator
    {
        public:
            typedef Iter                                iterator_type;
            typedef Tp                                  value_type;
            typedef ptrdiff_t                           difference_type;
            typedef Tp*                                 pointer;
            typedef Tp&                                 reference;
            typedef std::bidirectional_iterator_tag     iterator_category;

        private:
            iterator_type p_i;
        
        private:
            explicit rb_tree_iterator(iterator_type _rhs) : p_i(_rhs) {}
        public:
            rb_tree_iterator() {}
            
            iterator_type base() const throw() 
            {
                return (p_i);
            }
            reference operator*() const
            {
                return (p_i->_value);
            }
            pointer operator->() const
            {
                return (&p_i->_value);
            }
            rb_tree_iterator &operator++()
            {
                p_i = _tree_next(p_i);
                return *this;
            }
            rb_tree_iterator operator++(int)
            {
                rb_tree_iterator _tmp(*this);
                ++(*this);
                return _tmp;
            }
            rb_tree_iterator &operator--()
            {
                p_i = _tree_prev(p_i);
                return *this;
            }
            rb_tree_iterator operator--(int)
            {
                rb_tree_iterator _tmp(*this);
                --(*this);
                return _tmp;
            }
            friend bool operator==(const rb_tree_iterator &lhs, const rb_tree_iterator &rhs)
            {
                return lhs.p_i == rhs.p_i;
            }
            friend bool operator!=(const rb_tree_iterator &lhs, const rb_tree_iterator &rhs)
            {
                return !(lhs == rhs);
            }
        private:
            template <class, class, class>
            friend class tree;
            template <class, class, class, class>
            friend class map;
    };

    template <class Tp, class Iter>
    class rb_tree_const_iterator
    {
        public:
            typedef Iter                                iterator_type;
            typedef Tp                                  value_type;
            typedef ptrdiff_t                           difference_type;
            typedef const Tp*                                 pointer;
            typedef const Tp&                           reference;
            typedef std::bidirectional_iterator_tag     iterator_category;
            typedef rb_tree_iterator<Tp, Iter>          non_const_iterator;

        private:
            iterator_type p_i;
        
        private:
            explicit rb_tree_const_iterator(iterator_type _rhs) : p_i(_rhs) {}
            
        public:
            rb_tree_const_iterator() {}
            rb_tree_const_iterator(const non_const_iterator &rhs) : p_i(rhs.base()) {}
            
            iterator_type base() const throw() 
            {
                return (p_i);
            }
            reference operator*() const
            {
                return (p_i->_value);
            }
            pointer operator->() const
            {
                return (&p_i->_value);
            }
            rb_tree_const_iterator &operator++()
            {
                p_i = _tree_next(p_i);
                return *this;
            }
            rb_tree_const_iterator operator++(int)
            {
                rb_tree_const_iterator _tmp(*this);
                ++(*this);
                return _tmp;
            }
            rb_tree_const_iterator &operator--()
            {
                p_i = _tree_prev(p_i);
                return *this;
            }
            rb_tree_const_iterator operator--(int)
            {
                rb_tree_const_iterator _tmp(*this);
                --(*this);
                return _tmp;
            }
            friend bool operator==(const rb_tree_const_iterator &lhs, const rb_tree_const_iterator &rhs)
            {
                return lhs.p_i == rhs.p_i;
            }
            friend bool operator!=(const rb_tree_const_iterator &lhs, const rb_tree_const_iterator &rhs)
            {
                return !(lhs == rhs);
            }
        
        private:
            template <class, class, class>
            friend class tree;
            template <class, class, class, class>
            friend class map;
            
    };
}

#endif