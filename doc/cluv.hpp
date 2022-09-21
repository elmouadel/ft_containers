#include <__config>
#include <iosfwd> // for forward declaration of vector
#include <__bit_reference>
#include <type_traits>
#include <climits>
#include <limits>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <__cxx_version>
#include <__split_buffer>
#include <__functional_base>

#include <__debug>

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_PUSH_MACROS
#include <__undef_macros>
_LIBCPP_BEGIN_NAMESPACE_STD

template <bool>
class __vector_base_common
{
protected:
    __attribute__ ((__visibility__("hidden"))) __attribute__ ((internal_linkage)) __vector_base_common() {}
    __attribute__ ((noreturn)) void __throw_length_error() const;
    __attribute__ ((noreturn)) void __throw_out_of_range() const;
};

template <bool __b>
void
__vector_base_common<__b>::__throw_length_error() const
{
    std::__1::__throw_length_error("vector");
}

template <bool __b>
void
__vector_base_common<__b>::__throw_out_of_range() const
{
    std::__1::__throw_out_of_range("vector");
}

extern template class __attribute__ ((__visibility__("default"))) __vector_base_common<true>;

        template <class _Tp, class _Allocator>
        class __vector_base
            : protected __vector_base_common<true>
        {
        public:
            typedef _Allocator allocator_type;
            typedef allocator_traits<allocator_type> __alloc_traits;
            typedef typename __alloc_traits::size_type size_type;

        protected:
            typedef _Tp value_type;
            typedef value_type &reference;
            typedef const value_type &const_reference;
            typedef typename __alloc_traits::difference_type difference_type;
            typedef typename __alloc_traits::pointer pointer;
            typedef typename __alloc_traits::const_pointer const_pointer;
            typedef pointer iterator;
            typedef const_pointer const_iterator;

            pointer __begin_;
            pointer __end_;
            __compressed_pair<pointer, allocator_type> __end_cap_;

            allocator_type &__alloc() throw()
            {
                return __end_cap_.second();
            }

            const allocator_type &__alloc() const throw()
            {
                return __end_cap_.second();
            }

            pointer &__end_cap() throw()
            {
                return __end_cap_.first();
            }

            const pointer &__end_cap() const throw()
            {
                return __end_cap_.first();
            }

            __vector_base();
            __vector_base(const allocator_type &__a);

            ~__vector_base();

            void clear() throw() { __destruct_at_end(__begin_); }

            size_type capacity() const throw()
            {
                return static_cast<size_type>(__end_cap() - __begin_);
            }

            void __destruct_at_end(pointer __new_last) throw();

            void __copy_assign_alloc(const __vector_base &__c)
            {
                __copy_assign_alloc(__c, integral_constant<bool,
                                                           __alloc_traits::propagate_on_container_copy_assignment::value>());
            }

            void __move_assign_alloc(__vector_base &__c)

            {
                __move_assign_alloc(__c, integral_constant<bool,
                                                           __alloc_traits::propagate_on_container_move_assignment::value>());
            }

        private:
            void __copy_assign_alloc(const __vector_base &__c, true_type)
            {
                if (__alloc() != __c.__alloc())
                {
                    clear();
                    __alloc_traits::deallocate(__alloc(), __begin_, capacity());
                    __begin_ = __end_ = __end_cap() = std::__1::__get_nullptr_t();
                }
                __alloc() = __c.__alloc();
            }

            void __copy_assign_alloc(const __vector_base &, false_type)
            {
            }

            void __move_assign_alloc(__vector_base &__c, true_type)

            {
                __alloc() = std::__1::move(__c.__alloc());
            }

            void __move_assign_alloc(__vector_base &, false_type) throw()
            {
            }
        };

        template <class _Tp, class _Allocator>
        inline void
        __vector_base<_Tp, _Allocator>::__destruct_at_end(pointer __new_last) throw()
        {
            pointer __soon_to_be_end = __end_;
            while (__new_last != __soon_to_be_end)
                __alloc_traits::destroy(__alloc(), std::__1::__to_raw_pointer(--__soon_to_be_end));
            __end_ = __new_last;
        }

        template <class _Tp, class _Allocator>
        inline __vector_base<_Tp, _Allocator>::__vector_base()

            : __begin_(std::__1::__get_nullptr_t()),
              __end_(std::__1::__get_nullptr_t()),
              __end_cap_(std::__1::__get_nullptr_t())
        {
        }

        template <class _Tp, class _Allocator>
        inline __vector_base<_Tp, _Allocator>::__vector_base(const allocator_type &__a)
            : __begin_(std::__1::__get_nullptr_t()),
              __end_(std::__1::__get_nullptr_t()),
              __end_cap_(std::__1::__get_nullptr_t(), __a)
        {
        }
# 459 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        __vector_base<_Tp, _Allocator>::~__vector_base()
        {
            if (__begin_ != std::__1::__get_nullptr_t())
            {
                clear();
                __alloc_traits::deallocate(__alloc(), __begin_, capacity());
            }
        }

        template <class _Tp, class _Allocator>
        class __attribute__((__type_visibility__("default"))) vector
            : private __vector_base<_Tp, _Allocator>
        {
        private:
            typedef __vector_base<_Tp, _Allocator> __base;
            typedef allocator<_Tp> __default_allocator_type;

        public:
            typedef vector __self;
            typedef _Tp value_type;
            typedef _Allocator allocator_type;
            typedef typename __base::__alloc_traits __alloc_traits;
            typedef typename __base::reference reference;
            typedef typename __base::const_reference const_reference;
            typedef typename __base::size_type size_type;
            typedef typename __base::difference_type difference_type;
            typedef typename __base::pointer pointer;
            typedef typename __base::const_pointer const_pointer;
            typedef __wrap_iter<pointer> iterator;
            typedef __wrap_iter<const_pointer> const_iterator;
            typedef std::__1::reverse_iterator<iterator> reverse_iterator;
            typedef std::__1::reverse_iterator<const_iterator> const_reverse_iterator;

            _Static_assert((is_same<typename allocator_type::value_type, value_type>::value), "Allocator::value_type must be same type as value_type");

            vector()
            {
            }
            explicit vector(const allocator_type &__a)

                : __base(__a)
            {
            }
            explicit vector(size_type __n);

            vector(size_type __n, const value_type &__x);
            vector(size_type __n, const value_type &__x, const allocator_type &__a);
            template <class _InputIterator>
            vector(_InputIterator __first,
                   typename enable_if<__is_input_iterator<_InputIterator>::value &&
                                          !__is_forward_iterator<_InputIterator>::value &&
                                          is_constructible<
                                              value_type,
                                              typename iterator_traits<_InputIterator>::reference>::value,
                                      _InputIterator>::type __last);
            template <class _InputIterator>
            vector(_InputIterator __first, _InputIterator __last, const allocator_type &__a,
                   typename enable_if<__is_input_iterator<_InputIterator>::value &&
                                      !__is_forward_iterator<_InputIterator>::value &&
                                      is_constructible<
                                          value_type,
                                          typename iterator_traits<_InputIterator>::reference>::value>::type * = 0);
            template <class _ForwardIterator>
            vector(_ForwardIterator __first,
                   typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                          is_constructible<
                                              value_type,
                                              typename iterator_traits<_ForwardIterator>::reference>::value,
                                      _ForwardIterator>::type __last);
            template <class _ForwardIterator>
            vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type &__a,
                   typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                      is_constructible<
                                          value_type,
                                          typename iterator_traits<_ForwardIterator>::reference>::value>::type * = 0);

            ~vector()
            {
                __annotate_delete();
            }

            vector(const vector &__x);
            vector(const vector &__x, const allocator_type &__a);

            vector &operator=(const vector &__x);
# 590 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
            template <class _InputIterator>
            typename enable_if<
                __is_input_iterator<_InputIterator>::value &&
                    !__is_forward_iterator<_InputIterator>::value &&
                    is_constructible<
                        value_type,
                        typename iterator_traits<_InputIterator>::reference>::value,
                void>::type
            assign(_InputIterator __first, _InputIterator __last);
            template <class _ForwardIterator>
            typename enable_if<
                __is_forward_iterator<_ForwardIterator>::value &&
                    is_constructible<
                        value_type,
                        typename iterator_traits<_ForwardIterator>::reference>::value,
                void>::type
            assign(_ForwardIterator __first, _ForwardIterator __last);

            void assign(size_type __n, const_reference __u);

            allocator_type get_allocator() const throw()
            {
                return this->__alloc();
            }

            iterator begin() throw();
            const_iterator begin() const throw();
            iterator end() throw();
            const_iterator end() const throw();

            reverse_iterator rbegin() throw()
            {
                return reverse_iterator(end());
            }

            const_reverse_iterator rbegin() const throw()
            {
                return const_reverse_iterator(end());
            }

            reverse_iterator rend() throw()
            {
                return reverse_iterator(begin());
            }

            const_reverse_iterator rend() const throw()
            {
                return const_reverse_iterator(begin());
            }

            const_iterator cbegin() const throw()
            {
                return begin();
            }

            const_iterator cend() const throw()
            {
                return end();
            }

            const_reverse_iterator crbegin() const throw()
            {
                return rbegin();
            }

            const_reverse_iterator crend() const throw()
            {
                return rend();
            }

            size_type size() const throw()
            {
                return static_cast<size_type>(this->__end_ - this->__begin_);
            }

            size_type capacity() const throw()
            {
                return __base::capacity();
            }

            bool empty() const throw()
            {
                return this->__begin_ == this->__end_;
            }
            size_type max_size() const throw();
            void reserve(size_type __n);
            void shrink_to_fit() throw();

            reference operator[](size_type __n);
            const_reference operator[](size_type __n) const;
            reference at(size_type __n);
            const_reference at(size_type __n) const;

            reference front()
            {
                ((void)0);
                return *this->__begin_;
            }
            const_reference front() const
            {
                ((void)0);
                return *this->__begin_;
            }
            reference back()
            {
                ((void)0);
                return *(this->__end_ - 1);
            }
            const_reference back() const
            {
                ((void)0);
                return *(this->__end_ - 1);
            }

            value_type *data() throw()
            {
                return std::__1::__to_raw_pointer(this->__begin_);
            }

            const value_type *data() const throw()
            {
                return std::__1::__to_raw_pointer(this->__begin_);
            }

            void __emplace_back(const value_type &__x) { push_back(__x); }
# 712 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
            void push_back(const_reference __x);
# 726 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3

            void pop_back();

            iterator insert(const_iterator __position, const_reference __x);

            iterator insert(const_iterator __position, size_type __n, const_reference __x);
            template <class _InputIterator>
            typename enable_if<
                __is_input_iterator<_InputIterator>::value &&
                    !__is_forward_iterator<_InputIterator>::value &&
                    is_constructible<
                        value_type,
                        typename iterator_traits<_InputIterator>::reference>::value,
                iterator>::type
            insert(const_iterator __position, _InputIterator __first, _InputIterator __last);
            template <class _ForwardIterator>
            typename enable_if<
                __is_forward_iterator<_ForwardIterator>::value &&
                    is_constructible<
                        value_type,
                        typename iterator_traits<_ForwardIterator>::reference>::value,
                iterator>::type
            insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last);

            iterator erase(const_iterator __position);
            iterator erase(const_iterator __first, const_iterator __last);

            void clear() throw()
            {
                size_type __old_size = size();
                __base::clear();
                __annotate_shrink(__old_size);
                __invalidate_all_iterators();
            }

            void resize(size_type __sz);
            void resize(size_type __sz, const_reference __x);

            void swap(vector &)

                ;

            bool __invariants() const;
# 800 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        private:
            void __invalidate_all_iterators();
            void __invalidate_iterators_past(pointer __new_last);
            void __vallocate(size_type __n);
            void __vdeallocate() throw();
            size_type __recommend(size_type __new_size) const;
            void __construct_at_end(size_type __n);

            void __construct_at_end(size_type __n, const_reference __x);
            template <class _ForwardIterator>
            typename enable_if<
                __is_forward_iterator<_ForwardIterator>::value,
                void>::type
            __construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n);
            void __append(size_type __n);
            void __append(size_type __n, const_reference __x);

            iterator __make_iter(pointer __p) throw();

            const_iterator __make_iter(const_pointer __p) const throw();
            void __swap_out_circular_buffer(__split_buffer<value_type, allocator_type &> &__v);
            pointer __swap_out_circular_buffer(__split_buffer<value_type, allocator_type &> &__v, pointer __p);
            void __move_range(pointer __from_s, pointer __from_e, pointer __to);
            void __move_assign(vector &__c, true_type);
            void __move_assign(vector &__c, false_type);

            void __destruct_at_end(pointer __new_last) throw()
            {
                __invalidate_iterators_past(__new_last);
                size_type __old_size = size();
                __base::__destruct_at_end(__new_last);
                __annotate_shrink(__old_size);
            }

            template <class _Up>
            void __push_back_slow_path(_Up &__x);
# 861 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3

            void __annotate_contiguous_container(const void *, const void *, const void *,
                                                 const void *) const
            {
            }

            void __annotate_new(size_type __current_size) const
            {
                __annotate_contiguous_container(data(), data() + capacity(),
                                                data() + capacity(), data() + __current_size);
            }

            void __annotate_delete() const
            {
                __annotate_contiguous_container(data(), data() + capacity(),
                                                data() + size(), data() + capacity());
            }

            void __annotate_increase(size_type __n) const
            {
                __annotate_contiguous_container(data(), data() + capacity(),
                                                data() + size(), data() + size() + __n);
            }

            void __annotate_shrink(size_type __old_size) const
            {
                __annotate_contiguous_container(data(), data() + capacity(),
                                                data() + __old_size, data() + size());
            }
# 908 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
            struct __RAII_IncreaseAnnotator
            {

                __RAII_IncreaseAnnotator(const vector &, size_type = 1) {}
                void __done() {}
            };
        };
# 933 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type &> &__v)
        {
            __annotate_delete();
            __alloc_traits::__construct_backward(this->__alloc(), this->__begin_, this->__end_, __v.__begin_);
            std::__1::swap(this->__begin_, __v.__begin_);
            std::__1::swap(this->__end_, __v.__end_);
            std::__1::swap(this->__end_cap(), __v.__end_cap());
            __v.__first_ = __v.__begin_;
            __annotate_new(size());
            __invalidate_all_iterators();
        }

        template <class _Tp, class _Allocator>
        typename vector<_Tp, _Allocator>::pointer
        vector<_Tp, _Allocator>::__swap_out_circular_buffer(__split_buffer<value_type, allocator_type &> &__v, pointer __p)
        {
            __annotate_delete();
            pointer __r = __v.__begin_;
            __alloc_traits::__construct_backward(this->__alloc(), this->__begin_, __p, __v.__begin_);
            __alloc_traits::__construct_forward(this->__alloc(), __p, this->__end_, __v.__end_);
            std::__1::swap(this->__begin_, __v.__begin_);
            std::__1::swap(this->__end_, __v.__end_);
            std::__1::swap(this->__end_cap(), __v.__end_cap());
            __v.__first_ = __v.__begin_;
            __annotate_new(size());
            __invalidate_all_iterators();
            return __r;
        }
# 971 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::__vallocate(size_type __n)
        {
            if (__n > max_size())
                this->__throw_length_error();
            this->__begin_ = this->__end_ = __alloc_traits::allocate(this->__alloc(), __n);
            this->__end_cap() = this->__begin_ + __n;
            __annotate_new(0);
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::__vdeallocate() throw()
        {
            if (this->__begin_ != std::__1::__get_nullptr_t())
            {
                clear();
                __alloc_traits::deallocate(this->__alloc(), this->__begin_, capacity());
                this->__begin_ = this->__end_ = this->__end_cap() = std::__1::__get_nullptr_t();
            }
        }

        template <class _Tp, class _Allocator>
        typename vector<_Tp, _Allocator>::size_type
        vector<_Tp, _Allocator>::max_size() const throw()
        {
            return std::__1::min<size_type>(__alloc_traits::max_size(this->__alloc()),
                                            numeric_limits<difference_type>::max());
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::size_type
            vector<_Tp, _Allocator>::__recommend(size_type __new_size) const
        {
            const size_type __ms = max_size();
            if (__new_size > __ms)
                this->__throw_length_error();
            const size_type __cap = capacity();
            if (__cap >= __ms / 2)
                return __ms;
            return std::__1::max<size_type>(2 * __cap, __new_size);
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::__construct_at_end(size_type __n)
        {
            allocator_type &__a = this->__alloc();
            do
            {
                __RAII_IncreaseAnnotator __annotator(*this);
                __alloc_traits::construct(__a, std::__1::__to_raw_pointer(this->__end_));
                ++this->__end_;
                --__n;
                __annotator.__done();
            } while (__n > 0);
        }

        template <class _Tp, class _Allocator>
        inline void
        vector<_Tp, _Allocator>::__construct_at_end(size_type __n, const_reference __x)
        {
            allocator_type &__a = this->__alloc();
            do
            {
                __RAII_IncreaseAnnotator __annotator(*this);
                __alloc_traits::construct(__a, std::__1::__to_raw_pointer(this->__end_), __x);
                ++this->__end_;
                --__n;
                __annotator.__done();
            } while (__n > 0);
        }

        template <class _Tp, class _Allocator>
        template <class _ForwardIterator>
        typename enable_if<
            __is_forward_iterator<_ForwardIterator>::value,
            void>::type
        vector<_Tp, _Allocator>::__construct_at_end(_ForwardIterator __first, _ForwardIterator __last, size_type __n)
        {
            allocator_type &__a = this->__alloc();
            __RAII_IncreaseAnnotator __annotator(*this, __n);
            __alloc_traits::__construct_range_forward(__a, __first, __last, this->__end_);
            __annotator.__done();
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::__append(size_type __n)
        {
            if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
                this->__construct_at_end(__n);
            else
            {
                allocator_type &__a = this->__alloc();
                __split_buffer<value_type, allocator_type &> __v(__recommend(size() + __n), size(), __a);
                __v.__construct_at_end(__n);
                __swap_out_circular_buffer(__v);
            }
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::__append(size_type __n, const_reference __x)
        {
            if (static_cast<size_type>(this->__end_cap() - this->__end_) >= __n)
                this->__construct_at_end(__n, __x);
            else
            {
                allocator_type &__a = this->__alloc();
                __split_buffer<value_type, allocator_type &> __v(__recommend(size() + __n), size(), __a);
                __v.__construct_at_end(__n, __x);
                __swap_out_circular_buffer(__v);
            }
        }

        template <class _Tp, class _Allocator>
        vector<_Tp, _Allocator>::vector(size_type __n)
        {

            if (__n > 0)
            {
                __vallocate(__n);
                __construct_at_end(__n);
            }
        }
# 1141 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        vector<_Tp, _Allocator>::vector(size_type __n, const value_type &__x)
        {

            if (__n > 0)
            {
                __vallocate(__n);
                __construct_at_end(__n, __x);
            }
        }

        template <class _Tp, class _Allocator>
        vector<_Tp, _Allocator>::vector(size_type __n, const value_type &__x, const allocator_type &__a)
            : __base(__a)
        {

            if (__n > 0)
            {
                __vallocate(__n);
                __construct_at_end(__n, __x);
            }
        }

        template <class _Tp, class _Allocator>
        template <class _InputIterator>
        vector<_Tp, _Allocator>::vector(_InputIterator __first,
                                        typename enable_if<__is_input_iterator<_InputIterator>::value &&
                                                               !__is_forward_iterator<_InputIterator>::value &&
                                                               is_constructible<
                                                                   value_type,
                                                                   typename iterator_traits<_InputIterator>::reference>::value,
                                                           _InputIterator>::type __last)
        {

            for (; __first != __last; ++__first)
                __emplace_back(*__first);
        }

        template <class _Tp, class _Allocator>
        template <class _InputIterator>
        vector<_Tp, _Allocator>::vector(_InputIterator __first, _InputIterator __last, const allocator_type &__a,
                                        typename enable_if<__is_input_iterator<_InputIterator>::value &&
                                                           !__is_forward_iterator<_InputIterator>::value &&
                                                           is_constructible<
                                                               value_type,
                                                               typename iterator_traits<_InputIterator>::reference>::value>::type *)
            : __base(__a)
        {

            for (; __first != __last; ++__first)
                __emplace_back(*__first);
        }

        template <class _Tp, class _Allocator>
        template <class _ForwardIterator>
        vector<_Tp, _Allocator>::vector(_ForwardIterator __first,
                                        typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                                               is_constructible<
                                                                   value_type,
                                                                   typename iterator_traits<_ForwardIterator>::reference>::value,
                                                           _ForwardIterator>::type __last)
        {

            size_type __n = static_cast<size_type>(std::__1::distance(__first, __last));
            if (__n > 0)
            {
                __vallocate(__n);
                __construct_at_end(__first, __last, __n);
            }
        }

        template <class _Tp, class _Allocator>
        template <class _ForwardIterator>
        vector<_Tp, _Allocator>::vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type &__a,
                                        typename enable_if<__is_forward_iterator<_ForwardIterator>::value &&
                                                           is_constructible<
                                                               value_type,
                                                               typename iterator_traits<_ForwardIterator>::reference>::value>::type *)
            : __base(__a)
        {

            size_type __n = static_cast<size_type>(std::__1::distance(__first, __last));
            if (__n > 0)
            {
                __vallocate(__n);
                __construct_at_end(__first, __last, __n);
            }
        }

        template <class _Tp, class _Allocator>
        vector<_Tp, _Allocator>::vector(const vector &__x)
            : __base(__alloc_traits::select_on_container_copy_construction(__x.__alloc()))
        {

            size_type __n = __x.size();
            if (__n > 0)
            {
                __vallocate(__n);
                __construct_at_end(__x.__begin_, __x.__end_, __n);
            }
        }

        template <class _Tp, class _Allocator>
        vector<_Tp, _Allocator>::vector(const vector &__x, const allocator_type &__a)
            : __base(__a)
        {

            size_type __n = __x.size();
            if (__n > 0)
            {
                __vallocate(__n);
                __construct_at_end(__x.__begin_, __x.__end_, __n);
            }
        }
# 1391 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        inline vector<_Tp, _Allocator> &
        vector<_Tp, _Allocator>::operator=(const vector &__x)
        {
            if (this != &__x)
            {
                __base::__copy_assign_alloc(__x);
                assign(__x.__begin_, __x.__end_);
            }
            return *this;
        }

        template <class _Tp, class _Allocator>
        template <class _InputIterator>
        typename enable_if<
            __is_input_iterator<_InputIterator>::value &&
                !__is_forward_iterator<_InputIterator>::value &&
                is_constructible<
                    _Tp,
                    typename iterator_traits<_InputIterator>::reference>::value,
            void>::type
        vector<_Tp, _Allocator>::assign(_InputIterator __first, _InputIterator __last)
        {
            clear();
            for (; __first != __last; ++__first)
                __emplace_back(*__first);
        }

        template <class _Tp, class _Allocator>
        template <class _ForwardIterator>
        typename enable_if<
            __is_forward_iterator<_ForwardIterator>::value &&
                is_constructible<
                    _Tp,
                    typename iterator_traits<_ForwardIterator>::reference>::value,
            void>::type
        vector<_Tp, _Allocator>::assign(_ForwardIterator __first, _ForwardIterator __last)
        {
            size_type __new_size = static_cast<size_type>(std::__1::distance(__first, __last));
            if (__new_size <= capacity())
            {
                _ForwardIterator __mid = __last;
                bool __growing = false;
                if (__new_size > size())
                {
                    __growing = true;
                    __mid = __first;
                    std::__1::advance(__mid, size());
                }
                pointer __m = std::__1::copy(__first, __mid, this->__begin_);
                if (__growing)
                    __construct_at_end(__mid, __last, __new_size - size());
                else
                    this->__destruct_at_end(__m);
            }
            else
            {
                __vdeallocate();
                __vallocate(__recommend(__new_size));
                __construct_at_end(__first, __last, __new_size);
            }
            __invalidate_all_iterators();
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::assign(size_type __n, const_reference __u)
        {
            if (__n <= capacity())
            {
                size_type __s = size();
                std::__1::fill_n(this->__begin_, std::__1::min(__n, __s), __u);
                if (__n > __s)
                    __construct_at_end(__n - __s, __u);
                else
                    this->__destruct_at_end(this->__begin_ + __n);
            }
            else
            {
                __vdeallocate();
                __vallocate(__recommend(static_cast<size_type>(__n)));
                __construct_at_end(__n, __u);
            }
            __invalidate_all_iterators();
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::iterator
            vector<_Tp, _Allocator>::__make_iter(pointer __p) throw()
        {
            return iterator(__p);
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::const_iterator
            vector<_Tp, _Allocator>::__make_iter(const_pointer __p) const throw()
        {
            return const_iterator(__p);
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::iterator
            vector<_Tp, _Allocator>::begin() throw()
        {
            return __make_iter(this->__begin_);
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::const_iterator
            vector<_Tp, _Allocator>::begin() const throw()
        {
            return __make_iter(this->__begin_);
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::iterator
            vector<_Tp, _Allocator>::end() throw()
        {
            return __make_iter(this->__end_);
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::const_iterator
            vector<_Tp, _Allocator>::end() const throw()
        {
            return __make_iter(this->__end_);
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::reference
            vector<_Tp, _Allocator>::operator[](size_type __n)
        {
            ((void)0);
            return this->__begin_[__n];
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::const_reference
            vector<_Tp, _Allocator>::operator[](size_type __n) const
        {
            ((void)0);
            return this->__begin_[__n];
        }

        template <class _Tp, class _Allocator>
        typename vector<_Tp, _Allocator>::reference
        vector<_Tp, _Allocator>::at(size_type __n)
        {
            if (__n >= size())
                this->__throw_out_of_range();
            return this->__begin_[__n];
        }

        template <class _Tp, class _Allocator>
        typename vector<_Tp, _Allocator>::const_reference
        vector<_Tp, _Allocator>::at(size_type __n) const
        {
            if (__n >= size())
                this->__throw_out_of_range();
            return this->__begin_[__n];
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::reserve(size_type __n)
        {
            if (__n > capacity())
            {
                allocator_type &__a = this->__alloc();
                __split_buffer<value_type, allocator_type &> __v(__n, size(), __a);
                __swap_out_circular_buffer(__v);
            }
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::shrink_to_fit() throw()
        {
            if (capacity() > size())
            {

                try
                {

                    allocator_type &__a = this->__alloc();
                    __split_buffer<value_type, allocator_type &> __v(size(), size(), __a);
                    __swap_out_circular_buffer(__v);
                }
                catch (...)
                {
                }
            }
        }

        template <class _Tp, class _Allocator>
        template <class _Up>
        void
        vector<_Tp, _Allocator>::__push_back_slow_path(_Up &__x)

        {
            allocator_type &__a = this->__alloc();
            __split_buffer<value_type, allocator_type &> __v(__recommend(size() + 1), size(), __a);

            __alloc_traits::construct(__a, std::__1::__to_raw_pointer(__v.__end_), std::__1::forward<_Up>(__x));
            __v.__end_++;
            __swap_out_circular_buffer(__v);
        }

        template <class _Tp, class _Allocator>
        inline void
        vector<_Tp, _Allocator>::push_back(const_reference __x)
        {
            if (this->__end_ != this->__end_cap())
            {
                __RAII_IncreaseAnnotator __annotator(*this);
                __alloc_traits::construct(this->__alloc(),
                                          std::__1::__to_raw_pointer(this->__end_), __x);
                __annotator.__done();
                ++this->__end_;
            }
            else
                __push_back_slow_path(__x);
        }
# 1703 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        inline void
        vector<_Tp, _Allocator>::pop_back()
        {
            ((void)0);
            this->__destruct_at_end(this->__end_ - 1);
        }

        template <class _Tp, class _Allocator>
        inline
            typename vector<_Tp, _Allocator>::iterator
            vector<_Tp, _Allocator>::erase(const_iterator __position)
        {

            ((void)0);

            difference_type __ps = __position - cbegin();
            pointer __p = this->__begin_ + __ps;
            this->__destruct_at_end(std::__1::move(__p + 1, this->__end_, __p));
            this->__invalidate_iterators_past(__p - 1);
            iterator __r = __make_iter(__p);
            return __r;
        }

        template <class _Tp, class _Allocator>
        typename vector<_Tp, _Allocator>::iterator
        vector<_Tp, _Allocator>::erase(const_iterator __first, const_iterator __last)
        {
# 1744 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
            ((void)0);
            pointer __p = this->__begin_ + (__first - begin());
            if (__first != __last)
            {
                this->__destruct_at_end(std::__1::move(__p + (__last - __first), this->__end_, __p));
                this->__invalidate_iterators_past(__p - 1);
            }
            iterator __r = __make_iter(__p);
            return __r;
        }
        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::__move_range(pointer __from_s, pointer __from_e, pointer __to)
        {
            pointer __old_last = this->__end_;
            difference_type __n = __old_last - __to;
            for (pointer __i = __from_s + __n; __i < __from_e; ++__i, ++this->__end_)
            {
                __alloc_traits::construct(this->__alloc(),
                                          std::__1::__to_raw_pointer(this->__end_),
                                          std::__1::move(*__i));
            }
            std::__1::move_backward(__from_s, __from_s + __n, __old_last);
        }

        template <class _Tp, class _Allocator>
        typename vector<_Tp, _Allocator>::iterator
        vector<_Tp, _Allocator>::insert(const_iterator __position, const_reference __x)
        {

            pointer __p = this->__begin_ + (__position - begin());
            if (this->__end_ < this->__end_cap())
            {
                __RAII_IncreaseAnnotator __annotator(*this);
                if (__p == this->__end_)
                {
                    __alloc_traits::construct(this->__alloc(),
                                              std::__1::__to_raw_pointer(this->__end_), __x);
                    ++this->__end_;
                }
                else
                {
                    __move_range(__p, this->__end_, __p + 1);
                    const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
                    if (__p <= __xr && __xr < this->__end_)
                        ++__xr;
                    *__p = *__xr;
                }
                __annotator.__done();
            }
            else
            {
                allocator_type &__a = this->__alloc();
                __split_buffer<value_type, allocator_type &> __v(__recommend(size() + 1), __p - this->__begin_, __a);
                __v.push_back(__x);
                __p = __swap_out_circular_buffer(__v, __p);
            }
            return __make_iter(__p);
        }
# 1886 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        typename vector<_Tp, _Allocator>::iterator
        vector<_Tp, _Allocator>::insert(const_iterator __position, size_type __n, const_reference __x)
        {

            pointer __p = this->__begin_ + (__position - begin());
            if (__n > 0)
            {
                if (__n <= static_cast<size_type>(this->__end_cap() - this->__end_))
                {
                    size_type __old_n = __n;
                    pointer __old_last = this->__end_;
                    if (__n > static_cast<size_type>(this->__end_ - __p))
                    {
                        size_type __cx = __n - (this->__end_ - __p);
                        __construct_at_end(__cx, __x);
                        __n -= __cx;
                    }
                    if (__n > 0)
                    {
                        __RAII_IncreaseAnnotator __annotator(*this, __n);
                        __move_range(__p, __old_last, __p + __old_n);
                        __annotator.__done();
                        const_pointer __xr = pointer_traits<const_pointer>::pointer_to(__x);
                        if (__p <= __xr && __xr < this->__end_)
                            __xr += __old_n;
                        std::__1::fill_n(__p, __n, *__xr);
                    }
                }
                else
                {
                    allocator_type &__a = this->__alloc();
                    __split_buffer<value_type, allocator_type &> __v(__recommend(size() + __n), __p - this->__begin_, __a);
                    __v.__construct_at_end(__n, __x);
                    __p = __swap_out_circular_buffer(__v, __p);
                }
            }
            return __make_iter(__p);
        }

        template <class _Tp, class _Allocator>
        template <class _InputIterator>
        typename enable_if<
            __is_input_iterator<_InputIterator>::value &&
                !__is_forward_iterator<_InputIterator>::value &&
                is_constructible<
                    _Tp,
                    typename iterator_traits<_InputIterator>::reference>::value,
            typename vector<_Tp, _Allocator>::iterator>::type
        vector<_Tp, _Allocator>::insert(const_iterator __position, _InputIterator __first, _InputIterator __last)
        {

            difference_type __off = __position - begin();
            pointer __p = this->__begin_ + __off;
            allocator_type &__a = this->__alloc();
            pointer __old_last = this->__end_;
            for (; this->__end_ != this->__end_cap() && __first != __last; ++__first)
            {
                __RAII_IncreaseAnnotator __annotator(*this);
                __alloc_traits::construct(__a, std::__1::__to_raw_pointer(this->__end_),
                                          *__first);
                ++this->__end_;
                __annotator.__done();
            }
            __split_buffer<value_type, allocator_type &> __v(__a);
            if (__first != __last)
            {

                try
                {

                    __v.__construct_at_end(__first, __last);
                    difference_type __old_size = __old_last - this->__begin_;
                    difference_type __old_p = __p - this->__begin_;
                    reserve(__recommend(size() + __v.size()));
                    __p = this->__begin_ + __old_p;
                    __old_last = this->__begin_ + __old_size;
                }
                catch (...)
                {
                    erase(__make_iter(__old_last), end());
                    throw;
                }
            }
            __p = std::__1::rotate(__p, __old_last, this->__end_);
            insert(__make_iter(__p), make_move_iterator(__v.begin()),
                   make_move_iterator(__v.end()));
            return begin() + __off;
        }

        template <class _Tp, class _Allocator>
        template <class _ForwardIterator>
        typename enable_if<
            __is_forward_iterator<_ForwardIterator>::value &&
                is_constructible<
                    _Tp,
                    typename iterator_traits<_ForwardIterator>::reference>::value,
            typename vector<_Tp, _Allocator>::iterator>::type
        vector<_Tp, _Allocator>::insert(const_iterator __position, _ForwardIterator __first, _ForwardIterator __last)
        {

            pointer __p = this->__begin_ + (__position - begin());
            difference_type __n = std::__1::distance(__first, __last);
            if (__n > 0)
            {
                if (__n <= this->__end_cap() - this->__end_)
                {
                    size_type __old_n = __n;
                    pointer __old_last = this->__end_;
                    _ForwardIterator __m = __last;
                    difference_type __dx = this->__end_ - __p;
                    if (__n > __dx)
                    {
                        __m = __first;
                        difference_type __diff = this->__end_ - __p;
                        std::__1::advance(__m, __diff);
                        __construct_at_end(__m, __last, __n - __diff);
                        __n = __dx;
                    }
                    if (__n > 0)
                    {
                        __RAII_IncreaseAnnotator __annotator(*this, __n);
                        __move_range(__p, __old_last, __p + __old_n);
                        __annotator.__done();
                        std::__1::copy(__first, __m, __p);
                    }
                }
                else
                {
                    allocator_type &__a = this->__alloc();
                    __split_buffer<value_type, allocator_type &> __v(__recommend(size() + __n), __p - this->__begin_, __a);
                    __v.__construct_at_end(__first, __last);
                    __p = __swap_out_circular_buffer(__v, __p);
                }
            }
            return __make_iter(__p);
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::resize(size_type __sz)
        {
            size_type __cs = size();
            if (__cs < __sz)
                this->__append(__sz - __cs);
            else if (__cs > __sz)
                this->__destruct_at_end(this->__begin_ + __sz);
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::resize(size_type __sz, const_reference __x)
        {
            size_type __cs = size();
            if (__cs < __sz)
                this->__append(__sz - __cs, __x);
            else if (__cs > __sz)
                this->__destruct_at_end(this->__begin_ + __sz);
        }

        template <class _Tp, class _Allocator>
        void
        vector<_Tp, _Allocator>::swap(vector &__x)

        {
            ((void)0);

            std::__1::swap(this->__begin_, __x.__begin_);
            std::__1::swap(this->__end_, __x.__end_);
            std::__1::swap(this->__end_cap(), __x.__end_cap());
            __swap_allocator(this->__alloc(), __x.__alloc(),
                             integral_constant<bool, __alloc_traits::propagate_on_container_swap::value>());
        }

        template <class _Tp, class _Allocator>
        bool
        vector<_Tp, _Allocator>::__invariants() const
        {
            if (this->__begin_ == std::__1::__get_nullptr_t())
            {
                if (this->__end_ != std::__1::__get_nullptr_t() || this->__end_cap() != std::__1::__get_nullptr_t())
                    return false;
            }
            else
            {
                if (this->__begin_ > this->__end_)
                    return false;
                if (this->__begin_ == this->__end_cap())
                    return false;
                if (this->__end_ > this->__end_cap())
                    return false;
            }
            return true;
        }
# 2143 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
        template <class _Tp, class _Allocator>
        inline void
        vector<_Tp, _Allocator>::__invalidate_all_iterators()
        {
        }

        template <class _Tp, class _Allocator>
        inline void
        vector<_Tp, _Allocator>::__invalidate_iterators_past(pointer __new_last)
        {
# 2171 "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../include/c++/v1/vector" 3
            ((void)__new_last);
        }

        template <class _Tp, class _Allocator>
        inline bool
        operator==(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
        {
            const typename vector<_Tp, _Allocator>::size_type __sz = __x.size();
            return __sz == __y.size() && std::__1::equal(__x.begin(), __x.end(), __y.begin());
        }

        template <class _Tp, class _Allocator>
        inline bool
        operator!=(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
        {
            return !(__x == __y);
        }

        template <class _Tp, class _Allocator>
        inline bool
        operator<(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
        {
            return std::__1::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
        }

        template <class _Tp, class _Allocator>
        inline bool
        operator>(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
        {
            return __y < __x;
        }

        template <class _Tp, class _Allocator>
        inline bool
        operator>=(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
        {
            return !(__x < __y);
        }

        template <class _Tp, class _Allocator>
        inline bool
        operator<=(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
        {
            return !(__y < __x);
        }

        template <class _Tp, class _Allocator>
        inline void
        swap(vector<_Tp, _Allocator> &__x, vector<_Tp, _Allocator> &__y)

        {
            __x.swap(__y);
        }



_LIBCPP_END_NAMESPACE_STD

_LIBCPP_POP_MACROS

