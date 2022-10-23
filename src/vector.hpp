/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:20:51 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/22 09:09:18 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include "./utils/utility.hpp"
#include "./utils/algorithm.hpp"
#include "./utils/vector_iterator.hpp"
#include "./utils/iterator_traits.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/allocator_traits.hpp"

namespace ft
{
/* ************************************************************************** */
/* ************************************************************************** */
                            // vector_base class :
/* ************************************************************************** */
/* ************************************************************************** */
    template< class _Tp, class _Allocator>
    class _vector_base
    {
        protected:
            typedef _Tp                                             value_type;
            typedef _Allocator                                      allocator_type;
            typedef typename ft::allocator_traits<allocator_type>   alloc_traits;
            typedef typename alloc_traits::size_type                size_type;
            typedef typename alloc_traits::difference_type          difference_type;
            typedef typename alloc_traits::pointer                  pointer;
            typedef typename alloc_traits::const_pointer            const_pointer;

        public:
            pointer         _begin;   
            pointer         _end;
            pointer         _end_l;
            allocator_type  _alloc;
            
            _vector_base();
            _vector_base(const allocator_type &_a);
            ~_vector_base();
            
            void _clear() { _destruct_at_end(_begin); }
            size_type _capacity() const
            {
                return static_cast<size_type>(_end_l - _begin);
            }
            void _destruct_at_end(pointer _new_last);
            void _length_error() const
            {
                throw std::length_error("vector");
            }
            void _out_of_range() const
            {
                throw std::out_of_range("vector");
            }
    };
    
    template <class _Tp, class _Allocator>
    void _vector_base<_Tp, _Allocator>::_destruct_at_end(pointer _new_last)
    {
        while (_new_last != _end)
            alloc_traits::destroy(_alloc, --_end);
    }
    template <class _Tp, class _Allocator>
    _vector_base<_Tp, _Allocator>::_vector_base()
        : _begin(nullptr),
          _end(nullptr),
          _end_l(nullptr)
    {
    }
    template <class _Tp, class _Allocator>
    _vector_base<_Tp, _Allocator>::_vector_base(const allocator_type &_a)
        : _begin(nullptr),
          _end(nullptr),
          _end_l(nullptr),
          _alloc(_a)
    {
    }
    template <class _Tp, class _Allocator>
    _vector_base<_Tp, _Allocator>::~_vector_base()
    {
        if (_begin != nullptr)
        {
            _clear();
            alloc_traits::deallocate(_alloc, _begin, _capacity());
        }
    }

/* ************************************************************************** */
/* ************************************************************************** */
                                // vector class :
/* ************************************************************************** */
/* ************************************************************************** */
    template< class Tp, 
    class Allocator = std::allocator<Tp> >
    class vector
    {
        _vector_base<Tp, Allocator> _base;
        
        public:
            typedef Tp                                              value_type;
            typedef value_type&                                     reference;
            typedef const value_type&                               const_reference;
            typedef Allocator                                       allocator_type;
            typedef typename ft::allocator_traits<allocator_type>   alloc_traits;
            typedef typename alloc_traits::size_type                size_type;
            typedef typename alloc_traits::difference_type          difference_type;
            typedef typename alloc_traits::pointer                  pointer;
            typedef typename alloc_traits::const_pointer            const_pointer;
            typedef vector_iterator<pointer>                        iterator;
            typedef vector_iterator<const_pointer>                  const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

            _Static_assert((ft::is_same<typename allocator_type::value_type, value_type>::value), 
            "Allocator::value_type must be same type as value_type");
            
/* ************************************************************************** */
                                // constructors :
/* ************************************************************************** */
        
            explicit vector (const allocator_type &_a = allocator_type()) : _base(_a)
            {
            }
            explicit vector (size_type _n, const_reference _val = value_type(), 
                            const allocator_type &_a = allocator_type()) : _base(_a)
            {
                if (_n > 0)
                {
                    _vallocate(_n);
                    _construct_at_end(_n, _val);
                }
            }
            template <class _InputIterator>
            vector (_InputIterator _first, _InputIterator _last, const allocator_type& _a = allocator_type(),
                typename ft::enable_if<ft::is_input_iterator<_InputIterator>::value>::type* = 0) :
                    _base(_a)
            {
                for (; _first != _last; ++_first)
                    push_back(*_first);
            }
            template <class _ForwardIterator>
            vector (_ForwardIterator _first, _ForwardIterator _last, const allocator_type& _a = allocator_type(),
                typename ft::enable_if<ft::is_forward_iterator<_ForwardIterator>::value>::type* = 0) :
                    _base(_a)
            {
                size_type _n = static_cast<size_type>(ft::distance(_first, _last));
                if (_n > 0)
                {
                    _vallocate(_n);
                    alloc_traits::construct_range_forward(_base._alloc, _first, _last, _base._end);
                }
            }
            vector(const vector &_v) :
                    _base(_v._base._alloc)
            {
                size_type _n = _v.size();
                if (_n > 0)
                {
                    _vallocate(_n);
                    alloc_traits::construct_range_forward(_base._alloc, _v._base._begin, _v._base._end, _base._end);
                }
            }
            ~vector()
            {
            }
            
/* ************************************************************************** */
                                // assignment :(in)
/* ************************************************************************** */
            vector &operator=(const vector &_v);
            void assign(size_type _n, const_reference _val);
            
            template <class _InputIterator>
                typename ft::enable_if<ft::is_input_iterator<_InputIterator>::value, void>::type
            assign(_InputIterator _first, _InputIterator _last);

            template <class _ForwardIterator>    
                typename ft::enable_if<ft::is_forward_iterator<_ForwardIterator>::value, void>::type
            assign(_ForwardIterator _first, _ForwardIterator _last);
           
/* ************************************************************************** */
            allocator_type get_allocator() const
            {
                return (_base._alloc);
            }

/* ************************************************************************** */
                                // iterators :(in)
/* ************************************************************************** */
        private:
            iterator _make_iter(pointer _p) 
            {
                return (iterator(_p));
            }
            const_iterator _make_iter(const_pointer _p) const
            {
                return (const_iterator(_p));
            }
        public:
            iterator begin()
            {
                return (_make_iter(_base._begin));
            }
            iterator end()
            {
                return (_make_iter(_base._end));
            }
            reverse_iterator rbegin()
            {
                return reverse_iterator(end());
            }
            reverse_iterator rend()
            {
                return reverse_iterator(begin());
            }
/* ************************************************************************** */
                            // const iterators :(in)
            const_iterator begin() const
            {
                return (_make_iter(_base._begin));
            }
            const_iterator end() const
            {
                return (_make_iter(_base._end));
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(end());
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }

/* ************************************************************************** */
                            // Capacity functions :(in)
/* ************************************************************************** */
            size_type size() const
            {
                return static_cast<size_type>(_base._end - _base._begin);
            }

            size_type capacity() const
            {
                return (_base._capacity());
            }

            bool empty() const
            {
                return (_base._begin == _base._end);
            }
            size_type max_size() const
            {
                return (std::min<size_type>(alloc_traits::max_size(_base._alloc),
                                std::numeric_limits<difference_type>::max()));
            }
            void reserve(size_type _n)
            {
                if (_n > max_size())
                    _base._length_error();
                if (_n > capacity())
                {
                    tmp_buffer<value_type, allocator_type &> _v(_n, size(), _base._alloc);
                    _construct_and_swap_buffers(_v);
                }
            }
            
/* ************************************************************************** */
                            // accessing functions :(in)
/* ************************************************************************** */
            reference operator[](size_type _in) 
            {
                return (_base._begin[_in]);
            }
            const_reference operator[](size_type _in) const
            {
                return (_base._begin[_in]);
            }
            reference at(size_type _in)
            {
                if (_in >= size())
                    _base._out_of_range();
                return (_base._begin[_in]);
            }
            const_reference at(size_type _in) const
            {
                if (_in >= size())
                    _base._out_of_range();
                return (_base._begin[_in]);
            }
            
/* ************************************************************************** */
                        // get top functions :(in)
/* ************************************************************************** */
            reference front()
            {
                return (*_base._begin);
            }
            const_reference front() const
            {
                return (*_base._begin);
            }
            reference back()
            {
                return (*(_base._end - 1));
            }
            const_reference back() const
            {
                return (*(_base._end - 1));
            }

            value_type *data()
            {
                return (_base._begin);
            }
            const value_type *data() const
            {
                return (_base._begin);
            }
            
/* ************************************************************************** */
                            // Modifiers functions :(in)
/* ************************************************************************** */
            void push_back(const_reference _val)
            {
                if (_base._end != _base._end_l)
                {
                    alloc_traits::construct(_base._alloc,_base._end, _val);
                    ++_base._end;
                }
                else
                    _push_back_slow_path(_val);
            }
            void pop_back()
            {
                _base._destruct_at_end(_base._end - 1);
            }
            iterator insert(const_iterator _pos, const_reference _val);
            iterator insert(const_iterator _pos, size_type _n, const_reference _val);
            
            template <class _InputIter>
            typename ft::enable_if<
                    ft::is_input_iterator<_InputIter>::value, 
                    typename vector<Tp, Allocator>::iterator>::type 
            insert(const_iterator _pos, _InputIter _first, _InputIter _last);
            
            template <class _ForwardIter>
            typename ft::enable_if<
                    ft::is_forward_iterator<_ForwardIter>::value, 
                    typename vector<Tp, Allocator>::iterator>::type 
            insert(const_iterator _pos, _ForwardIter _first, _ForwardIter _last);

            iterator erase(iterator _pos);
            iterator erase(iterator _first, iterator _last);
            void clear() {_base._clear(); }
            void resize(size_type _size, const_reference _val = value_type());
            void swap(vector &_v)
            {
                std::swap(_base._begin, _v._base._begin);
                std::swap(_base._end, _v._base._end);
                std::swap(_base._end_l, _v._base._end_l);
            }
            
/* ************************************************************************** */
                            // private struct :(in)
/* ************************************************************************** */
        private:
            template< class _Tp, class _Allocator>
            struct tmp_buffer
            {
                _vector_base<Tp, Allocator> _tmp;
                
                tmp_buffer(size_type _cap, size_type _start, allocator_type& _alloc)
                    : _tmp(_alloc)
                {
                    pointer _first;
                    _first = _cap != 0 ? alloc_traits::allocate(_alloc, _cap) : nullptr;
                    _tmp._begin = _tmp._end = _first + _start;
                    _tmp._end_l = _first + _cap;
                }
                ~tmp_buffer()
                {
                }
            };
            
/* ************************************************************************** */
                            // private functions :(in)
/* ************************************************************************** */      
        private:
            void _vallocate(size_type _n);
            void _construct_at_end(size_type _n, const_reference _val);
            void _push_back_slow_path(const_reference _val);
            size_type _new_capacity(size_type _new_size) const;
            void _construct_and_swap_buffers(tmp_buffer<value_type, allocator_type&> &_v);
            pointer _construct_and_swap_buffers(tmp_buffer<value_type, allocator_type&> &_v, pointer _p);
            void _move_range(pointer _from_s, pointer _from_e, pointer _new_s);
        
    };

/* ************************************************************************** */
/* ************************************************************************** */
                            // functions def(out)
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
                            // private functions :(out)
/* ************************************************************************** */
    template<class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_vallocate(size_type _n)
    {
        if (_n > max_size())
            _base._length_error();
        _base._begin = _base._end = alloc_traits::allocate(_base._alloc, _n);
        _base._end_l = _base._begin + _n;
    }

    template<class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_construct_at_end(size_type _n, const_reference _val)
    {
        for (; _n; --_n, ++_base._end)
            alloc_traits::construct(_base._alloc, _base._end, _val);
    }

    template<class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_push_back_slow_path(const_reference _val)
    {
        tmp_buffer<value_type, allocator_type&> _v(_new_capacity(size() + 1), size(), _base._alloc);
        
        alloc_traits::construct(_base._alloc, _v._tmp._end, _val);
        ++_v._tmp._end;
        _construct_and_swap_buffers(_v);
    }
    template <class _Tp, class _Allocator>
    typename vector<_Tp, _Allocator>::size_type
    vector<_Tp, _Allocator>::_new_capacity(size_type _new_size) const
    {
        const size_type _ms = max_size();
        if (_new_size > _ms)
            _base._length_error();
        const size_type _cap = capacity();
        if (_cap >= _ms / 2)
            return (_ms);
        return (std::max<size_type>(2 * _cap, _new_size));
    }
    template <class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_construct_and_swap_buffers(tmp_buffer<value_type, allocator_type&> &_v)
    {
        alloc_traits::construct_backward(_base._alloc, _base._begin, _base._end, _v._tmp._begin);
        std::swap(_base._begin, _v._tmp._begin);
        std::swap(_base._end, _v._tmp._end);
        std::swap(_base._end_l, _v._tmp._end_l);
    }
    template <class _Tp, class _Allocator>
    typename vector<_Tp, _Allocator>::pointer
    vector<_Tp, _Allocator>::_construct_and_swap_buffers(tmp_buffer<value_type, allocator_type&> &_v, pointer _p)
    {
        pointer _r = _v._tmp._begin;
        alloc_traits::construct_backward(_base._alloc, _base._begin, _p, _v._tmp._begin);
        alloc_traits::construct_forward(_base._alloc, _p, _base._end, _v._tmp._end);
        std::swap(_base._begin, _v._tmp._begin);
        std::swap(_base._end, _v._tmp._end);
        std::swap(_base._end_l, _v._tmp._end_l);
        return (_r);
    }
    template <class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_move_range(pointer _from_s, pointer _from_e, pointer _new_s)
    {
        pointer _end_hol = _base._end;
        difference_type _n = _end_hol - _new_s;
        
        for (pointer _i = _from_s + _n; _i < _from_e; ++_i, ++_base._end)
            alloc_traits::construct(_base._alloc, _base._end, *_i);
        ft::move_backward(_from_s, _from_s + _n, _end_hol);
    }
    
/* ************************************************************************** */
                                // assignment :(out)
/* ************************************************************************** */
    template <class _Tp, class _Allocator>
    vector<_Tp, _Allocator> &vector<_Tp, _Allocator>::operator=(const vector &_v)
    {
        if (this != &_v)
            assign(_v._base._begin, _v._base._end);
        return (*this);
    }
    template <class _Tp, class _Allocator>
    template <class _InputIterator>
        typename ft::enable_if<ft::is_input_iterator<_InputIterator>::value, void>::type
    vector<_Tp, _Allocator>::assign(_InputIterator _first, _InputIterator _last)
    {
        _base._clear();
        for (; _first != _last; ++_first)
            push_back(*_first);
    }
    template <class _Tp, class _Allocator>
    template <class _ForwardIterator>
        typename ft::enable_if<ft::is_forward_iterator<_ForwardIterator>::value, void>::type
    vector<_Tp, _Allocator>::assign(_ForwardIterator _first, _ForwardIterator _last)
    {
         size_type _new_size = static_cast<size_type>(ft::distance(_first, _last));
         if (_new_size <= capacity())
         {
             _ForwardIterator _hol_p = _last;
             if (_new_size > size())
            {
                _hol_p = _first;
                ft::advance(_hol_p, size());
            }
            pointer _inter = std::copy(_first, _hol_p, _base._begin);
            if (_hol_p != _last)
                alloc_traits::construct_range_forward(_base._alloc, _hol_p, _last, _base._end);
            else
                _base._destruct_at_end(_inter);
         }
         else
         {
            _base._clear();
            if (_base._begin)
                alloc_traits::deallocate(_base._alloc, _base._begin, capacity());
            _base._begin = _base._end = _base._end_l = nullptr;
            _vallocate(_new_capacity(_new_size));
            alloc_traits::construct_range_forward(_base._alloc, _first, _last, _base._end);
        }
    }
    template <class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::assign(size_type _n, const_reference _val)
    {
        if (_n <= capacity())
        {
            std::fill_n(_base._begin, std::min(_n, size()), _val);
            if (_n > size())
                _construct_at_end(_n - size(), _val);
            else
                _base._destruct_at_end(_base._begin + _n);
        }
        else
        {
            _base._clear();
            if (_base._begin)
                alloc_traits::deallocate(_base._alloc, _base._begin, capacity());
            _base._begin = _base._end = _base._end_l = nullptr;
            _vallocate(_new_capacity(_n));
            _construct_at_end(_n, _val);
        }
    }
/* ************************************************************************** */
                            // Modifiers functions :(in)
/* ************************************************************************** */
    template <class _Tp, class _Allocator>
    typename vector<_Tp, _Allocator>::iterator
    vector<_Tp, _Allocator>::insert(const_iterator _pos, const_reference _val)
    {
        pointer _p = _base._begin + (_pos - begin());
        if (_base._end != _base._end_l)
        {
            if (_p == _base._end)
            {
                alloc_traits::construct(_base._alloc,_base._end, _val);
                ++_base._end;
            }
            else
            {
                _move_range(_p, _base._end, _p + 1);
                const_pointer _val_add = &_val;
                if (_p <= _val_add && _val_add < _base._end)
                    ++_val_add;
                *_p = *_val_add;
            }
        }
        else
        {
            tmp_buffer<value_type, allocator_type&> _v(_new_capacity(this->size() + 1), _p - _base._begin, _base._alloc);
            
            alloc_traits::construct(_v._tmp._alloc, _v._tmp._end, _val);
            ++_v._tmp._end;
            _p = _construct_and_swap_buffers(_v, _p);
        }
        return (_make_iter(_p));
    }
    template <class _Tp, class _Allocator>
    typename vector<_Tp, _Allocator>::iterator
    vector<_Tp, _Allocator>::insert(const_iterator _pos, size_type _n, const_reference _val)
    {
        pointer _p = _base._begin + (_pos - begin());
        if (_n == 0)
            return (_make_iter(_p));
        if (_n <= static_cast<size_type>(_base._end_l - _base._end))
        {
            size_type _n_hol = _n;
            pointer _end_hol = _base._end;
            if (static_cast<size_type>(_base._end - _p) < _n)
            {
                _n = _base._end - _p;
                _construct_at_end(_n_hol - _n, _val);
            }
            if (_n > 0)
            {
                _move_range(_p, _end_hol, _p + _n_hol);
                const_pointer _val_add = &_val;
                if (_p <= _val_add && _val_add < _base._end)
                    _val_add += _n_hol;
                std::fill_n(_p, _n, *_val_add);
            }
        }
        else
        {
            tmp_buffer<value_type, allocator_type&> _v(_new_capacity(this->size() + _n), _p - _base._begin, _base._alloc);
            
            for (; _n; --_n, ++_v._tmp._end)
                alloc_traits::construct(_v._tmp._alloc, _v._tmp._end, _val);
            _p = _construct_and_swap_buffers(_v, _p);
        }
        return (_make_iter(_p));
    }
    template <class _Tp, class _Allocator>
    template <class _InputIter>
    typename ft::enable_if<
                ft::is_input_iterator<_InputIter>::value, 
                typename vector<_Tp, _Allocator>::iterator
            >::type vector<_Tp, _Allocator>::insert(const_iterator _pos, _InputIter _first, _InputIter _last)
    {
        vector  _v;
        for (;_first != _last; ++_first)
            _v.push_back(*_first);
        return (insert(_pos, _v.begin(), _v.end()));
    }
    template <class _Tp, class _Allocator>
    template <class _ForwardIter>
            typename ft::enable_if<
                ft::is_forward_iterator<_ForwardIter>::value, 
                typename vector<_Tp, _Allocator>::iterator
            >::type vector<_Tp, _Allocator>::insert(const_iterator _pos, _ForwardIter _first, _ForwardIter _last)
    {
        pointer         _p = _base._begin + (_pos - begin());
        difference_type _n = ft::distance(_first, _last);
        if (_n <= 0)
            return (_make_iter(_p));
        if (_n <= _base._end_l - _base._end)
        {
            _ForwardIter    _iter_hol = _last;
            pointer         _end_hol = _base._end;
            size_type       _n_hol = _n;
            
            if (_n > _base._end - _p)
            {
                _n = _base._end - _p;
                _iter_hol = _first;
                ft::advance(_iter_hol, _n);
                alloc_traits::construct_range_forward(_base._alloc, _iter_hol, _last, _base._end);
            }
            if (_n > 0)
            {
                _move_range(_p, _end_hol, _p + _n_hol);
                std::copy(_first, _iter_hol, _p);
            }
        }
        else
        {
            tmp_buffer<value_type, allocator_type&> _v(_new_capacity(this->size() + _n), _p - _base._begin, _base._alloc);
            alloc_traits::construct_range_forward(_base._alloc, _first, _last, _v._tmp._end);  
            _p = _construct_and_swap_buffers(_v, _p);
        }
        return (_make_iter(_p));
    }
    template <class _Tp, class _Allocator>
    typename vector<_Tp, _Allocator>::iterator
    vector<_Tp, _Allocator>::erase(iterator _pos)
    {
        pointer _p = _base._begin + (_pos - begin());
        iterator _ret = _make_iter(_p);
        // if (_p >= _base._end)
        //     return (_ret);
        std::memmove(_p, _p + 1, (_base._end - _p - 1) * sizeof(*_p));
        alloc_traits::destroy(_base._alloc, --_base._end);
        return (_ret);
    }
    template <class _Tp, class _Allocator>
    typename vector<_Tp, _Allocator>::iterator
    vector<_Tp, _Allocator>::erase(iterator _first, iterator _last)
    {
        pointer _p_last = _base._begin + (_last - begin());
        pointer _p_first = _base._begin + (_first - begin());
        iterator _ret = _make_iter(_p_first);
        
        std::memmove(_p_first, _p_last, (_base._end - _p_last) * sizeof(*_p_first));
        _p_first += _base._end - _p_last;
        _base._destruct_at_end(_p_first);
        return (_ret);
    }
    template <class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::resize(size_type _size, const_reference _val)
    {
        size_type _hol_size = size();
        size_type _n = _size - _hol_size;
        if (_size < _hol_size)
            _base._destruct_at_end(_base._begin + _size);
        else if (_size > _hol_size)
        {
            if (_size <= capacity())
                _construct_at_end(_n, _val);
            else
            {
                tmp_buffer<value_type, allocator_type&> _v(_new_capacity(_hol_size + _n), _hol_size, _base._alloc);
                _construct_and_swap_buffers(_v);
                _construct_at_end(_n, _val);
            }    
        }
    }

/* ************************************************************************** */
                        // Non-member functions :(out)
/* ************************************************************************** */
    
    template <class _Tp, class _Allocator>
    inline bool
    operator==(const vector<_Tp, _Allocator> &_lhs, const vector<_Tp, _Allocator> &_rhs)
    {
        return _lhs.size() == _rhs.size() && ft::equal(_lhs.begin(), _lhs.end(), _rhs.begin());
    }
    template <class _Tp, class _Allocator>
    inline bool
    operator!=(const vector<_Tp, _Allocator> &_lhs, const vector<_Tp, _Allocator> &_rhs)
    {
        return !(_lhs == _rhs);
    }
    template <class _Tp, class _Allocator>
    inline bool
    operator<(const vector<_Tp, _Allocator> &_lhs, const vector<_Tp, _Allocator> &_rhs)
    {
        return ft::lexicographical_compare(_lhs.begin(), _lhs.end(), _rhs.begin(), _rhs.end());
    }
    template <class _Tp, class _Allocator>
    inline bool
    operator>(const vector<_Tp, _Allocator> &_lhs, const vector<_Tp, _Allocator> &_rhs)
    {
        return _rhs < _lhs;
    }

    template <class _Tp, class _Allocator>
    inline bool
    operator>=(const vector<_Tp, _Allocator> &_lhs, const vector<_Tp, _Allocator> &_rhs)
    {
        return !(_lhs < _rhs);
    }
    template <class _Tp, class _Allocator>
    inline bool
    operator<=(const vector<_Tp, _Allocator> &_lhs, const vector<_Tp, _Allocator> &_rhs)
    {
        return !(_rhs < _lhs);
    }
    template <class _Tp, class _Allocator>
    inline void
    swap(ft::vector<_Tp, _Allocator> &_lhs, ft::vector<_Tp, _Allocator> &_rhs)
    {
        _lhs.swap(_rhs);
    }
    
}
namespace std
{
    template <class _Tp, class _Allocator>
    inline void
    swap(ft::vector<_Tp, _Allocator> &_lhs, ft::vector<_Tp, _Allocator> &_rhs)
    {
       ft::swap(_lhs, _rhs);
    }
}

#endif