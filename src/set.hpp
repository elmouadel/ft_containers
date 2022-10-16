/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:17:30 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/16 09:42:52 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include <set>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include "./utils/rb_tree.hpp"
#include "./utils/utility.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/allocator_traits.hpp"

namespace ft
{
    template <class _Key, class _Compare = std::less<_Key>, 
    class _Allocator = std::allocator<_Key> >
    class set
    {
        public :
            typedef _Key                                                key_type;
            typedef key_type                                            value_type;
            typedef _Compare                                            key_compare;
            typedef key_compare                                            value_compare;
            typedef _Allocator                                          allocator_type;
            typedef value_type                                          &reference;
            typedef const value_type                                    &const_reference;
            typedef typename ft::allocator_traits<allocator_type>       alloc_traits;
            typedef typename alloc_traits::size_type                    size_type;
            typedef typename alloc_traits::difference_type              difference_type;
            typedef typename alloc_traits::pointer                      pointer;
            typedef typename alloc_traits::const_pointer                const_pointer;

        _Static_assert((ft::is_same<typename allocator_type::value_type, value_type>::value), 
        "Allocator::value_type must be same type as value_type");

        private:
            typedef ft::tree<value_type, value_compare, allocator_type> _base;
            _base _tree;
            
        public:
            typedef typename _base::iterator                iterator;
            typedef typename _base::const_iterator          const_iterator;
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
            
/* ************************************************************************** */
                            // Costructors :
/* ************************************************************************** */
            explicit set(const key_compare &_comp = key_compare(), const allocator_type &_alloc = allocator_type())
                : _tree(value_compare(_comp), _alloc) {}

            template <class _InputIterator>
            set(_InputIterator _first, _InputIterator _last,
                const key_compare &_comp = key_compare(), const allocator_type &_alloc = allocator_type())
                : _tree(value_compare(_comp), _alloc)
            {
                insert(_first, _last);
                (void)_first;
                (void)_last;
            }

            set(const set &_m)
                : _tree(_m._tree)
            {
                insert(_m.begin(), _m.end());
            }

            set &operator=(const set &_m)
            {
                if (this != &_m)
                {
                    _tree.clear();
                    _tree.value_comp() = _m._tree.value_comp();
                    insert(_m.begin(), _m.end());
                }
                return *this;
            }
            ~set() 
            {
            }
/* ************************************************************************** */
                            // Observers :
/* ************************************************************************** */
            key_compare key_comp() const { return _tree.value_comp(); }

            value_compare value_comp() const { return _tree.value_comp(); }
/* ************************************************************************** */
                            // Iterators :
/* ************************************************************************** */
            iterator begin() throw() { return _tree.begin(); }
            iterator end() throw() { return _tree.end(); }
            
            reverse_iterator rbegin() throw()
            {
                return reverse_iterator(end());
            }
            reverse_iterator rend() throw()
            {
                return reverse_iterator(begin());
            }
            
            const_iterator begin() const throw() { return _tree.begin(); }
            const_iterator end() const throw() { return _tree.end(); }
            
            const_reverse_iterator rbegin() const throw()
            {
                return const_reverse_iterator(end());
            }
            const_reverse_iterator rend() const throw()
            {
                return const_reverse_iterator(begin());
            }

/* ************************************************************************** */
                            // Capacity :
/* ************************************************************************** */
            bool empty() const throw() { return (_tree.size() == 0); }
            size_type size() const throw() { return (_tree.size()); }
            size_type max_size() const throw() { return (_tree.max_size()); }

            allocator_type get_allocator() const
            {
                return (_tree.alloc());
            }

/* ************************************************************************** */
                            // Modifiers :
/* ************************************************************************** */
            void clear() throw() { _tree.clear(); }
            void swap(set &_m)
            {
                _tree.swap(_m._tree);
            }            
            pair<iterator, bool> insert(const value_type &_val)
            {
                return (_tree._insert_unique(_val));
            }
            iterator insert(const_iterator _pos, const value_type& _val)
            {
                return (_tree._insert_unique(_pos.p_i,  _val));
            }
            template <class _InputIterator>
            void insert(_InputIterator _first, _InputIterator _last)
            {
                for (const_iterator _it = end(); _first != _last; ++_first)
                {
                    //check exp _it = end()
                    _tree._insert_unique(_it.p_i, *_first);
                }
            }
            void erase (iterator _pos)
            {
                return (_tree._erase(_pos.p_i));
            }
            size_type erase (const key_type &_key)
            {
                typename _base::node_ptr _pos = _tree.root();

                if (_tree._find_parent(_pos, value_type(_key)))
                    return (0);
                _tree._erase(_pos);
                return (1);
            }
            void erase(iterator _first, iterator _last)
            {
                iterator _hol_i;
                
                while (_first != _last)
                {
                    _hol_i = _first++;
                    _tree._erase(_hol_i.p_i);
                }
            }

/* ************************************************************************** */
                            // Lookup :
/* ************************************************************************** */
            iterator find(const key_type &_key) 
            {
                typename _base::node_ptr _pos = _tree.root();

                if (_tree._find_parent(_pos, value_type(_key)))
                    return (iterator(_tree.root()->_parent));
                return (iterator(_pos));
            }
            const_iterator find(const key_type &_key) const
            {
                typename _base::node_ptr _pos = _tree.root();
                
                if (_tree._find_parent(_pos, value_type(_key)))
                    return (const_iterator(_tree.end_node()));
                return (const_iterator(_pos));
            }
            size_type count(const key_type &_key)
            {
                typename _base::node_ptr _pos = _tree.root();

                return !(_tree._find_parent(_pos, value_type(_key)));
            }
            iterator lower_bound(const key_type &_key)
            {
                return (iterator(_tree._lower_bound(value_type(_key))));
            }
            const_iterator lower_bound(const key_type &_key) const
            {
                return (const_iterator(_tree._lower_bound(value_type(_key))));
            }
            iterator upper_bound(const key_type &_key)
            {
                return (iterator(_tree._upper_bound(value_type(_key))));
            }
            const_iterator upper_bound(const key_type &_key) const
            {
                return (const_iterator(_tree._upper_bound(value_type(_key))));
            }
            pair<iterator, iterator> equal_range(const key_type &_key)
            {
                typedef pair<iterator, iterator> pii;
                pair<typename _base::node_ptr, typename _base::node_ptr> _ret;

                _ret = _tree._equal_range(value_type(_key));
                return (pii(iterator(_ret.first), iterator(_ret.second)));
            }
            pair<const_iterator, const_iterator> equal_range(const key_type &_key) const
            {
                typedef pair<const_iterator, const_iterator> pcici;
                pair<typename _base::node_ptr, typename _base::node_ptr> _ret;

                _ret = _tree._equal_range(value_type(_key));
                return (pcici(const_iterator(_ret.first), const_iterator(_ret.second)));
            }
    };
    template<typename _key, typename _Compaire, typename _Alloc>
    bool operator==(const set<_key, _Compaire, _Alloc> &_lhs,
                    const set<_key, _Compaire, _Alloc> &_rhs)
    {
        return (_lhs.size() == _rhs.size() && std::equal(_lhs.begin(), _lhs.end(), _rhs.begin()));
    }
    template<typename _key, typename _Compaire, typename _Alloc>
    bool operator<(const set<_key, _Compaire, _Alloc> &_lhs,
                    const set<_key, _Compaire, _Alloc> &_rhs)
    {
        return (std::lexicographical_compare(_lhs.begin(), _lhs.end(), _rhs.begin(), _rhs.end()));
    }
    template<typename _key, typename _Compaire, typename _Alloc>
    bool operator!=(const set<_key, _Compaire, _Alloc> &_lhs,
                    const set<_key, _Compaire, _Alloc> &_rhs)
    {
        return !(_lhs == _rhs);
    }
    template<typename _key, typename _Compaire, typename _Alloc>
    bool operator>(const set<_key, _Compaire, _Alloc> &_lhs,
                    const set<_key, _Compaire, _Alloc> &_rhs)
    {
        return (_rhs < _lhs);
    }
    template<typename _key, typename _Compaire, typename _Alloc>
    bool operator>=(const set<_key, _Compaire, _Alloc> &_lhs,
                    const set<_key, _Compaire, _Alloc> &_rhs)
    {
        return !(_lhs < _rhs);
    }
    template<typename _key, typename _Compaire, typename _Alloc>
    bool operator<=(const set<_key, _Compaire, _Alloc> &_lhs,
                    const set<_key, _Compaire, _Alloc> &_rhs)
    {
        return !(_rhs < _lhs);
    }
    template <class _Key, class _Compare, class _Alloc>
    inline void
    swap(set<_Key, _Compare, _Alloc> &_lhs,
         set<_Key, _Compare, _Alloc> &_rhs) 
    {
        _lhs.swap(_rhs);
    }
}

#endif