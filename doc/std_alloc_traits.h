template <class _Alloc>
struct allocator_traits
{
    typedef _Alloc allocator_type;
    typedef typename allocator_type::value_type value_type;

    typedef typename __pointer_type<value_type, allocator_type>::type pointer;
    typedef typename __const_pointer<value_type, pointer, allocator_type>::type const_pointer;
    typedef typename __void_pointer<pointer, allocator_type>::type void_pointer;
    typedef typename __const_void_pointer<pointer, allocator_type>::type const_void_pointer;

    typedef typename __alloc_traits_difference_type<allocator_type, pointer>::type difference_type;
    typedef typename __size_type<allocator_type, difference_type>::type size_type;

    typedef typename __propagate_on_container_copy_assignment<allocator_type>::type
        propagate_on_container_copy_assignment;
    typedef typename __propagate_on_container_move_assignment<allocator_type>::type
        propagate_on_container_move_assignment;
    typedef typename __propagate_on_container_swap<allocator_type>::type
        propagate_on_container_swap;
    typedef typename __is_always_equal<allocator_type>::type
        is_always_equal;

    template <class _Tp>
    struct rebind_alloc
    {
        typedef typename __allocator_traits_rebind<allocator_type, _Tp>::type other;
    };
    template <class _Tp>
    struct rebind_traits
    {
        typedef allocator_traits<typename rebind_alloc<_Tp>::other> other;
    };

    static pointer allocate(allocator_type &__a, size_type __n)
    {
        return __a.allocate(__n);
    }

    static pointer allocate(allocator_type &__a, size_type __n, const_void_pointer __hint)
    {
        return __allocate(__a, __n, __hint,
                          __has_allocate_hint<allocator_type, size_type, const_void_pointer>());
    }

    static void deallocate(allocator_type &__a, pointer __p, size_type __n) throw()
    {
        __a.deallocate(__p, __n);
    }
# 1563 "/Library/Developer/CommandLineTools/usr/include/c++/v1/memory" 3
    template <class _Tp>

    static void construct(allocator_type &, _Tp *__p)
    {
        ::new ((void *)__p) _Tp();
    }
    template <class _Tp, class _A0>

    static void construct(allocator_type &__a, _Tp *__p, const _A0 &__a0)
    {
        __construct(__has_construct<allocator_type, _Tp *, const _A0 &>(),
                    __a, __p, __a0);
    }
    template <class _Tp, class _A0, class _A1>

    static void construct(allocator_type &, _Tp *__p, const _A0 &__a0,
                          const _A1 &__a1)
    {
        ::new ((void *)__p) _Tp(__a0, __a1);
    }
    template <class _Tp, class _A0, class _A1, class _A2>

    static void construct(allocator_type &, _Tp *__p, const _A0 &__a0,
                          const _A1 &__a1, const _A2 &__a2)
    {
        ::new ((void *)__p) _Tp(__a0, __a1, __a2);
    }

    template <class _Tp>

    static void destroy(allocator_type &__a, _Tp *__p)
    {
        __destroy(__has_destroy<allocator_type, _Tp *>(), __a, __p);
    }

    static size_type max_size(const allocator_type &__a) throw()
    {
        return __max_size(__has_max_size<const allocator_type>(), __a);
    }

    static allocator_type
    select_on_container_copy_construction(const allocator_type &__a)
    {
        return __select_on_container_copy_construction(
            __has_select_on_container_copy_construction<const allocator_type>(),
            __a);
    }

    template <class _Ptr>

    static void
    __construct_forward(allocator_type &__a, _Ptr __begin1, _Ptr __end1, _Ptr &__begin2)
    {
        for (; __begin1 != __end1; ++__begin1, ++__begin2)
            construct(__a, std::__1::__to_raw_pointer(__begin2), std::__1::move_if_noexcept(*__begin1));
    }

    template <class _Tp>

    static
        typename enable_if<
            (__is_default_allocator<allocator_type>::value || !__has_construct<allocator_type, _Tp *, _Tp>::value) &&
                is_trivially_move_constructible<_Tp>::value,
            void>::type
        __construct_forward(allocator_type &, _Tp *__begin1, _Tp *__end1, _Tp *&__begin2)
    {
        ptrdiff_t _Np = __end1 - __begin1;
        if (_Np > 0)
        {
            std::__1::memcpy(__begin2, __begin1, _Np * sizeof(_Tp));
            __begin2 += _Np;
        }
    }

    template <class _Iter, class _Ptr>

    static void
    __construct_range_forward(allocator_type &__a, _Iter __begin1, _Iter __end1, _Ptr &__begin2)
    {
        for (; __begin1 != __end1; ++__begin1, (void)++__begin2)
            construct(__a, std::__1::__to_raw_pointer(__begin2), *__begin1);
    }

    template <class _SourceTp, class _DestTp,
              class _RawSourceTp = typename remove_const<_SourceTp>::type,
              class _RawDestTp = typename remove_const<_DestTp>::type>

    static
        typename enable_if<
            is_trivially_move_constructible<_DestTp>::value &&
                is_same<_RawSourceTp, _RawDestTp>::value &&
                (__is_default_allocator<allocator_type>::value ||
                 !__has_construct<allocator_type, _DestTp *, _SourceTp &>::value),
            void>::type
        __construct_range_forward(allocator_type &, _SourceTp *__begin1, _SourceTp *__end1, _DestTp *&__begin2)
    {
        ptrdiff_t _Np = __end1 - __begin1;
        if (_Np > 0)
        {
            std::__1::memcpy(const_cast<_RawDestTp *>(__begin2), __begin1, _Np * sizeof(_DestTp));
            __begin2 += _Np;
        }
    }

    template <class _Ptr>

    static void
    __construct_backward(allocator_type &__a, _Ptr __begin1, _Ptr __end1, _Ptr &__end2)
    {
        while (__end1 != __begin1)
        {
            construct(__a, std::__1::__to_raw_pointer(__end2 - 1), std::__1::move_if_noexcept(*--__end1));
            --__end2;
        }
    }

    template <class _Tp>

    static
        typename enable_if<
            (__is_default_allocator<allocator_type>::value || !__has_construct<allocator_type, _Tp *, _Tp>::value) &&
                is_trivially_move_constructible<_Tp>::value,
            void>::type
        __construct_backward(allocator_type &, _Tp *__begin1, _Tp *__end1, _Tp *&__end2)
    {
        ptrdiff_t _Np = __end1 - __begin1;
        __end2 -= _Np;
        if (_Np > 0)
            std::__1::memcpy(__end2, __begin1, _Np * sizeof(_Tp));
    }

private:
    static pointer __allocate(allocator_type &__a, size_type __n,
                              const_void_pointer __hint, true_type)
    {
        return __a.allocate(__n, __hint);
    }

    static pointer __allocate(allocator_type &__a, size_type __n,
                              const_void_pointer, false_type)
    {
        return __a.allocate(__n);
    }
# 1725 "/Library/Developer/CommandLineTools/usr/include/c++/v1/memory" 3
    template <class _Tp, class _A0>

    static void __construct(true_type, allocator_type &__a, _Tp *__p,
                            const _A0 &__a0)
    {
        __a.construct(__p, __a0);
    }
    template <class _Tp, class _A0>

    static void __construct(false_type, allocator_type &, _Tp *__p,
                            const _A0 &__a0)
    {
        ::new ((void *)__p) _Tp(__a0);
    }

    template <class _Tp>

    static void __destroy(true_type, allocator_type &__a, _Tp *__p)
    {
        __a.destroy(__p);
    }
    template <class _Tp>

    static void __destroy(false_type, allocator_type &, _Tp *__p)
    {
        __p->~_Tp();
    }

    static size_type __max_size(true_type, const allocator_type &__a) throw()
    {
        return __a.max_size();
    }

    static size_type __max_size(false_type, const allocator_type &) throw()
    {
        return numeric_limits<size_type>::max() / sizeof(value_type);
    }

    static allocator_type
    __select_on_container_copy_construction(true_type, const allocator_type &__a)
    {
        return __a.select_on_container_copy_construction();
    }

    static allocator_type
    __select_on_container_copy_construction(false_type, const allocator_type &__a)
    {
        return __a;
    }
};

template <class _Traits, class _Tp>
struct __rebind_alloc_helper
{

    typedef typename _Traits::template rebind_alloc<_Tp>::other type;
};
