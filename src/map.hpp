/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:03:19 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/21 18:37:20 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <stdexcept>
#include <algorithm>
#include "./utils/rb_tree.hpp"
#include "./utils/utility.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/allocator_traits.hpp"

namespace ft
{
    template <class _Key, class _Tp, class _Compare = std::less<_Key>, 
    class _Allocator = std::allocator<pair<const _Key, _Tp> > >
    class map
    {
        public :
            typedef _Key                                                key_type;
            typedef _Tp                                                 mapped_type;
            typedef pair<const key_type, mapped_type>                   value_type;
            typedef _Compare                                            key_compare;
            typedef _Allocator                                          allocator_type;
            typedef value_type&                                         reference;
            typedef const value_type&                                   const_reference;
            typedef typename ft::allocator_traits<allocator_type>       alloc_traits;
            typedef typename alloc_traits::size_type                    size_type;
            typedef typename alloc_traits::difference_type              difference_type;
            typedef typename alloc_traits::pointer                      pointer;
            typedef typename alloc_traits::const_pointer                const_pointer;

        _Static_assert((ft::is_same<typename allocator_type::value_type, value_type>::value), 
        "Allocator::value_type must be same type as value_type");

            class value_compare
            {
                friend class map;
                
                protected:
                    key_compare comp;
                    value_compare(key_compare c) : comp(c) {}
                public:
                    bool operator()(const value_type &_lhs, const value_type &_rhs) const
                    {
                        return comp(_lhs.first, _rhs.first);
                    }
            };
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
            explicit map(const key_compare &_comp = key_compare(), const allocator_type &_alloc = allocator_type())
                : _tree(value_compare(_comp), _alloc) {}

            template <class _InputIterator>
            map(_InputIterator _first, _InputIterator _last,
                const key_compare &_comp = key_compare(), const allocator_type &_alloc = allocator_type())
                : _tree(value_compare(_comp), _alloc)
            {
                insert(_first, _last);
            }

            map(const map &_m)
                : _tree(_m._tree)
            {
                insert(_m.begin(), _m.end());
            }

            map &operator=(const map &_m)
            {
                if (this != &_m)
                {
                    _tree.clear();
                    _tree.value_comp() = _m._tree.value_comp();
                    insert(_m.begin(), _m.end());
                }
                return *this;
            }
            ~map() 
            {
            }
/* ************************************************************************** */
                            // Observers :
/* ************************************************************************** */
            key_compare key_comp() const { return _tree.value_comp().comp; }

            value_compare value_comp() const { return value_compare(_tree.value_comp().comp); }
/* ************************************************************************** */
                            // Iterators :
/* ************************************************************************** */
            iterator begin() { return _tree.begin(); }
            iterator end() { return _tree.end(); }
            
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
            
            const_iterator begin() const { return _tree.begin(); }
            const_iterator end() const { return _tree.end(); }
            
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }

/* ************************************************************************** */
                            // Capacity :
/* ************************************************************************** */
            bool empty() const { return (_tree.size() == 0); }
            size_type size() const { return (_tree.size()); }
            size_type max_size() const { return (_tree.max_size()); }

            allocator_type get_allocator() const
            {
                return (_tree.alloc());
            }

/* ************************************************************************** */
                            // Element access :
/* ************************************************************************** */
            mapped_type &operator[](const key_type &_key)
            {
                return (this->insert(value_type(_key, mapped_type())).first->second);
            }
            mapped_type &at(const key_type &_key)
            {
                typename _base::node_ptr _pos = _tree.root();
                
                if (_tree._find_parent(_pos, value_type(_key, mapped_type())))
                    throw std::out_of_range("ft::map::at: key not found");
                return (_pos->_value.second);
            }
            const mapped_type &at(const key_type &_key) const
            {
                typename _base::node_ptr _pos = _tree.root();
                
                if (_tree._find_parent(_pos, value_type(_key, mapped_type())))
                    throw std::out_of_range("ft::map::at: key not found");
                return (_pos->_value.second);
            }

/* ************************************************************************** */
                            // Modifiers :
/* ************************************************************************** */
            void clear() { _tree.clear(); }
            void swap(map &_m)
            {
                _tree.swap(_m._tree);
            }            
            pair<iterator, bool> insert(const value_type &_val)
            {
                return (_tree._insert_unique(_val));
            }
            iterator insert(iterator _pos, const value_type& _val)
            {
                return (_tree._insert_unique(_pos.p_i,  _val));
            }
            template <class _InputIterator>
            void insert(_InputIterator _first, _InputIterator _last)
            {
                for (; _first != _last; ++_first)
                    _tree._insert_unique(*_first);
            }
            void erase (iterator _pos)
            {
                return (_tree._erase(_pos.p_i));
            }
            size_type erase (const key_type &_key)
            {
                typename _base::node_ptr _pos = _tree.root();

                if (_tree._find_parent(_pos, value_type(_key, mapped_type())))
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

                if (_tree._find_parent(_pos, value_type(_key, mapped_type())))
                    return (iterator(_tree.root()->_parent));
                return (iterator(_pos));
            }
            const_iterator find(const key_type &_key) const
            {
                typename _base::node_ptr _pos = _tree.root();
                
                if (_tree._find_parent(_pos, value_type(_key, mapped_type())))
                    return (const_iterator(_tree.end_node()));
                return (const_iterator(_pos));
            }
            size_type count(const key_type &_key) const
            {
                typename _base::node_ptr _pos = _tree.root();

                return !(_tree._find_parent(_pos, value_type(_key, mapped_type())));
            }
            iterator lower_bound(const key_type &_key)
            {
                return (iterator(_tree._lower_bound(value_type(_key, mapped_type()))));
            }
            const_iterator lower_bound(const key_type &_key) const
            {
                return (const_iterator(_tree._lower_bound(value_type(_key, mapped_type()))));
            }
            iterator upper_bound(const key_type &_key)
            {
                return (iterator(_tree._upper_bound(value_type(_key, mapped_type()))));
            }
            const_iterator upper_bound(const key_type &_key) const
            {
                return (const_iterator(_tree._upper_bound(value_type(_key, mapped_type()))));
            }
            pair<iterator, iterator> equal_range(const key_type &_key)
            {
                typedef pair<iterator, iterator> pii;
                pair<typename _base::node_ptr, typename _base::node_ptr> _ret;

                _ret = _tree._equal_range(value_type(_key, mapped_type()));
                return (pii(iterator(_ret.first), iterator(_ret.second)));
            }
            pair<const_iterator, const_iterator> equal_range(const key_type &_key) const
            {
                typedef pair<const_iterator, const_iterator> pcici;
                pair<typename _base::node_ptr, typename _base::node_ptr> _ret;

                _ret = _tree._equal_range(value_type(_key, mapped_type()));
                return (pcici(const_iterator(_ret.first), const_iterator(_ret.second)));
            }
    };
    template<typename _key, typename _Tp, typename _Compaire, typename _Alloc>
    inline bool operator==(const map<_key, _Tp, _Compaire, _Alloc> &_lhs,
                    const map<_key, _Tp, _Compaire, _Alloc> &_rhs)
    {
        return (_lhs.size() == _rhs.size() && std::equal(_lhs.begin(), _lhs.end(), _rhs.begin()));
    }
    template<typename _key, typename _Tp, typename _Compaire, typename _Alloc>
    inline bool operator<(const map<_key, _Tp, _Compaire, _Alloc> &_lhs,
                    const map<_key, _Tp, _Compaire, _Alloc> &_rhs)
    {
        return (std::lexicographical_compare(_lhs.begin(), _lhs.end(), _rhs.begin(), _rhs.end()));
    }
    template<typename _key, typename _Tp, typename _Compaire, typename _Alloc>
    inline bool operator!=(const map<_key, _Tp, _Compaire, _Alloc> &_lhs,
                    const map<_key, _Tp, _Compaire, _Alloc> &_rhs)
    {
        return !(_lhs == _rhs);
    }
    template<typename _key, typename _Tp, typename _Compaire, typename _Alloc>
    inline bool operator>(const map<_key, _Tp, _Compaire, _Alloc> &_lhs,
                    const map<_key, _Tp, _Compaire, _Alloc> &_rhs)
    {
        return (_rhs < _lhs);
    }
    template<typename _key, typename _Tp, typename _Compaire, typename _Alloc>
    inline bool operator>=(const map<_key, _Tp, _Compaire, _Alloc> &_lhs,
                    const map<_key, _Tp, _Compaire, _Alloc> &_rhs)
    {
        return !(_lhs < _rhs);
    }
    template<typename _key, typename _Tp, typename _Compaire, typename _Alloc>
    inline bool operator<=(const map<_key, _Tp, _Compaire, _Alloc> &_lhs,
                    const map<_key, _Tp, _Compaire, _Alloc> &_rhs)
    {
        return !(_rhs < _lhs);
    }
    template <class _Key, class _Tp, class _Compare, class _Alloc>
    inline  void
    swap(map<_Key, _Tp, _Compare, _Alloc> &_lhs,
         map<_Key, _Tp, _Compare, _Alloc> &_rhs) 
    {
        _lhs.swap(_rhs);
    }
}
namespace std
{
    template <class _Key, class _Tp, class _Compare, class _Alloc>
    inline void
    swap(ft::map<_Key, _Tp, _Compare, _Alloc> &_lhs,
         ft::map<_Key, _Tp, _Compare, _Alloc> &_rhs) 
    {
        ft::swap(_lhs, _rhs);
    }
}

#endif