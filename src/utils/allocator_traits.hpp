/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:56:36 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/21 18:30:34 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_TRAITS_HPP
#define ALLOCATOR_TRAITS_HPP

namespace ft
{
    template<class _Alloc>
    struct allocator_traits
    {
        typedef _Alloc                                      allocator_type;
        typedef typename allocator_type::value_type         value_type;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        
        static pointer allocate(allocator_type &_alloc, size_type _n)
        {
            return _alloc.allocate(_n);
        }
        static void deallocate(allocator_type &_alloc, pointer _p, size_type _n)
        {
            _alloc.deallocate(_p, _n);
        }
        template <class _Tp, class _Up>
        static void construct(allocator_type &_alloc, _Tp *_p, _Up &_val)
        {
            _alloc.construct(_p, _val);
        }
        template <class _Tp>
        static void destroy(allocator_type &_alloc, _Tp *_p)
        {
            _alloc.destroy(_p);
        }
        template <class _Ptr>
        static void
        construct_forward(allocator_type &_alloc, _Ptr _begin1, _Ptr _end1, _Ptr &_begin2)
        {
            for (; _begin1 != _end1; ++_begin1, ++_begin2)
                construct(_alloc, _begin2, *_begin1);
        }
        template <class _Ptr>
        static void
        construct_backward(allocator_type &_alloc, _Ptr _begin1, _Ptr _end1, _Ptr &_end2)
        {
            while (_end1 != _begin1)
            {
                construct(_alloc, (_end2 - 1), *--_end1);
                --_end2;
            }
        }
        template <class _Iter, class _Ptr>
        static void
        construct_range_forward(allocator_type &_alloc, _Iter _begin1, _Iter _end1, _Ptr &_begin2)
        {
            for (; _begin1 != _end1; ++_begin1, ++_begin2)
                construct(_alloc, _begin2, *_begin1);
        }
        static size_type max_size(const allocator_type &_alloc)
        {
            return _alloc.max_size();
        }
    };    
}

#endif
