/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 10:20:51 by eabdelha          #+#    #+#             */
/*   Updated: 2022/09/19 07:43:42 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <type_traits>
#include "vector_iterator.hpp"

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
            typedef typename std::allocator_traits<allocator_type>  alloc_traits;
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
            
            void clear() { _destruct_at_end(_begin); }
            size_type capacity() const
            {
                return static_cast<size_type>(_end_l - _begin);
            }
            void _destruct_at_end(pointer __new_last);
            void length_error()
            {
                std::__throw_length_error("vector");
            }
            void out_of_range()
            {
                std::__throw_out_of_range("vector");
            }
    };

    
    template <class _Tp, class _Allocator>
    inline void
    _vector_base<_Tp, _Allocator>::_destruct_at_end(pointer _new_last)
    {
        pointer _soon_to_be_end = _end;
        while (_new_last != _soon_to_be_end)
            alloc_traits::destroy(_alloc, --_soon_to_be_end);
        _end = _new_last;
    }
    template <class _Tp, class _Allocator>
    inline _vector_base<_Tp, _Allocator>::_vector_base()
        : _begin(nullptr),
          _end(nullptr),
          _end_l(nullptr)
        //   _alloc(std::__default_init_tag())
    {
    }
    template <class _Tp, class _Allocator>
    inline _vector_base<_Tp, _Allocator>::_vector_base(const allocator_type &_a)
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
            clear();
            alloc_traits::deallocate(_alloc, _begin, capacity());
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
            typedef Tp                                               value_type;
            typedef value_type                                      &reference;
            typedef const value_type                                &const_reference;
            typedef Allocator                                       allocator_type;
            typedef typename std::allocator_traits<allocator_type>  alloc_traits;
            typedef typename alloc_traits::size_type                size_type;
            typedef typename alloc_traits::difference_type          difference_type;
            typedef typename alloc_traits::pointer                  pointer;
            typedef typename alloc_traits::const_pointer            const_pointer;
            typedef v_iterator<pointer>                             iterator;
            typedef v_iterator<const_pointer>                       const_iterator;

            _Static_assert((std::is_same<typename allocator_type::value_type, value_type>::value), 
            "Allocator::value_type must be same type as value_type");
            
/* ************************************************************************** */
                                // constructors :
/* ************************************************************************** */
            vector()
            {
            }
            explicit vector(size_type _n)
            {
                if (_n > 0)
                {
                    _vallocate(_n);
                    _construct_at_end();
                }
            }
            explicit vector (const allocator_type &_a = allocator_type()) : _base(_a)
            {
            }
            explicit vector (size_type _n, const_reference _val = value_type())
            {
                if (_n > 0)
                {
                    _vallocate(_n);
                    _construct_at_end(_n, _val);
                }
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
            vector (_InputIterator _first, _InputIterator _last, const allocator_type& _a = allocator_type()) :
                    _base(_a)
            {
                for (; _first != _last; ++_first)
                    __emplace_back(*_first);
            }
            vector(const vector &_v) :
                    _base(_v._base._alloc)
            {
                size_type _n = _v.size();
                if (_n > 0)
                {
                    _vallocate(_n);
                    _construct_at_end(_v._base._begin, _v._base._end);
                }
            }
            vector(const vector &_v, const allocator_type &_a) :
                    _base(_a)
            {
                size_type _n = _v.size();
                if (_n > 0)
                {
                    _vallocate(_n);
                    _construct_at_end(_v._base._begin, _v._base._end);
                }
            }
            ~vector()
            {
                // _annotate_delete();
            }
/* ************************************************************************** */
                                // assignment :(in)
/* ************************************************************************** */
            vector &operator=(const vector &_v);
            template <class _InputIterator>
            void assign(_InputIterator _first, _InputIterator _last);
            // void assign(size_type _n, const_reference _val);
/* ************************************************************************** */
                                // iterators :(in)
/* ************************************************************************** */
            allocator_type get_allocator() const throw()
            {
                return (_base._alloc);
            }
            iterator _make_iter(pointer _p) const throw()
            {
                return (iterator(_p));
            }
            // const_iterator _make_iter(const_pointer _p) const throw();
            iterator begin() throw()
            {
                return (_make_iter(_base._begin));
            }
            iterator end() throw()
            {
                return (_make_iter(_base._end));
            }
            // reverse_iterator rbegin() throw()
            // {
            //     return reverse_iterator(end());
            // }
            // reverse_iterator rend() throw()
            // {
            //     return reverse_iterator(begin());
            // }
/* ************************************************************************** */
                            // const iterators :(in)
            const_iterator begin() const throw()
            {
                return (_make_iter(_base._begin));
            }
            const_iterator end() const throw()
            {
                return (_make_iter(_base._end));
            }
            // const_reverse_iterator rbegin() const throw()
            // {
            //     return const_reverse_iterator(end());
            // }
            // const_reverse_iterator rend() const throw()
            // {
            //     return const_reverse_iterator(begin());
            // }
/* ************************************************************************** */
                            // const iterators 2 :(in)
            // const_iterator cbegin() const throw()
            // {
            //     return begin();
            // }
            // const_iterator cend() const throw()
            // {
            //     return end();
            // }
            // const_reverse_iterator crbegin() const throw()
            // {
            //     return rbegin();
            // }
            // const_reverse_iterator crend() const throw()
            // {
            //     return rend();
            // }
/* ************************************************************************** */
                            // size functions :(in)
/* ************************************************************************** */
            size_type size() const throw()
            {
                return static_cast<size_type>(_base._end - _base._begin);
            }

            size_type capacity() const throw()
            {
                return (_base.capacity());
            }

            bool empty() const throw()
            {
                return (_base._begin == _base._end);
            }
            size_type max_size() const throw()
            {
                return (std::min<size_type>(alloc_traits::max_size(_base._alloc),
                                std::numeric_limits<difference_type>::max()));
            }
            void reserve(size_type _n);
            void shrink_to_fit() throw();
/* ************************************************************************** */
                            // indexing functions :(in)
/* ************************************************************************** */
            reference operator[](size_type _n) 
            {
                return (_base._begin[_n]);
            }
            const_reference operator[](size_type _n) const
            {
                return (_base._begin[_n]);
            }
            reference at(size_type _n)
            {
                if (_n >= size())
                    _base.out_of_range();
                return (_base._begin[_n]);
            }
            const_reference at(size_type _n) const
            {
                if (_n >= size())
                    _base.out_of_range();
                return (_base._begin[_n]);
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

            value_type *data() throw()
            {
                return (_base._begin);
            }
            const value_type *data() const throw()
            {
                return (_base._begin);
            }
/* ************************************************************************** */
                            // manip functions :(in)
/* ************************************************************************** */
            void __emplace_back(const_reference _val) 
            {
                push_back(_val);
            }
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


/* ************************************************************************** */
                            // private functions :(in)
/* ************************************************************************** */      
        private:
            void _vallocate(size_type _n);
            void _construct_at_end(void);
            void _construct_at_end(const_reference _val);
            template <class _Iter>
            void _construct_at_end(_Iter _first, _Iter _last);
            // vpod _push_back_slow_path(_Up &__x);
            
            // void _construct_at_end(size_type _n);
            // void _construct_at_end(size_type _n, const_reference _v);
    };
    
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
                            // private functions :(out)
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
    template<class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_vallocate(size_type _n)
    {
        if (_n > _base._alloc.max_size())
            _base.length_error();
        _base._begin = alloc_traits::allocate(_base._alloc, _n);
        _base._end = _base._end_l = _base._begin + _n;
    }
    
    template<class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_construct_at_end(void)
    {
        pointer _pos = _base._begin;
        for (; _pos != _base._end; _pos++)
            alloc_traits::construct(_base._alloc, _pos);
    }
    
     template<class _Tp, class _Allocator>
    void vector<_Tp, _Allocator>::_construct_at_end(const_reference _val)
    {
        pointer _pos = _base._begin;
        for (; _pos != _base._end; _pos++)
            alloc_traits::construct(_base._alloc, _pos, _val);
    }
    
    template <class _Tp, class _Allocator>
    template <class _Iter>
    void vector<_Tp, _Allocator>::_construct_at_end(_Iter _first, _Iter _last)
    {
        // pointer _pos = _base._begin;
        // alloc_traits::__construct_range_forward(_base._alloc, _first, _last, _pos);
        for (; _first != _last; ++_first)
                __emplace_back(*_first);
    }
/* ************************************************************************** */
                                // assignment :(out)
/* ************************************************************************** */
    template <class _Tp, class _Allocator>
    inline vector<_Tp, _Allocator> &vector<_Tp, _Allocator>::operator=(const vector &_v)
    {
        if (this != &_v)
        {
            // _base._copy_assign_alloc(_v);
            assign(_v._begin, _v._end);
        }
        return *this;
    }
    template <class _Tp, class _Allocator>
    template <class _InputIterator>
    void vector<_Tp, _Allocator>::assign(_InputIterator _first, _InputIterator _last)
    {
        _base.clear();
        for (; _first != _last; ++_first)
            __emplace_back(*_first);
    }
}

#endif