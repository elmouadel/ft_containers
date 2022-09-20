template <class _Tp>
class __attribute__((__type_visibility__("default"))) allocator
{
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef _Tp *pointer;
    typedef const _Tp *const_pointer;
    typedef _Tp &reference;
    typedef const _Tp &const_reference;
    typedef _Tp value_type;

    typedef true_type propagate_on_container_move_assignment;
    typedef true_type is_always_equal;

    template <class _Up>
    struct rebind
    {
        typedef allocator<_Up> other;
    };

    allocator() throw() {}

    template <class _Up>

    allocator(const allocator<_Up> &) throw()
    {
    }

    pointer address(reference __x) const throw()
    {
        return std::__1::addressof(__x);
    }
    const_pointer address(const_reference __x) const throw()
    {
        return std::__1::addressof(__x);
    }

    pointer allocate(size_type __n, allocator<void>::const_pointer = 0)
    {
        if (__n > max_size())
            __throw_length_error("allocator<T>::allocate(size_t n)"
                                 " 'n' exceeds maximum supported size");
        return static_cast<pointer>(std::__1::__libcpp_allocate(__n * sizeof(_Tp), _Alignof(_Tp)));
    }
    void deallocate(pointer __p, size_type __n) throw()
    {
        std::__1::__libcpp_deallocate((void *)__p, __n * sizeof(_Tp), _Alignof(_Tp));
    }
    size_type max_size() const throw()
    {
        return size_type(~0) / sizeof(_Tp);
    }

    void
    construct(pointer __p)
    {
        ::new ((void *)__p) _Tp();
    }

    template <class _A0>

    void
    construct(pointer __p, _A0 &__a0)
    {
        ::new ((void *)__p) _Tp(__a0);
    }
    template <class _A0>

    void
    construct(pointer __p, const _A0 &__a0)
    {
        ::new ((void *)__p) _Tp(__a0);
    }

    template <class _A0, class _A1>

    void
    construct(pointer __p, _A0 &__a0, _A1 &__a1)
    {
        ::new ((void *)__p) _Tp(__a0, __a1);
    }
    template <class _A0, class _A1>

    void
    construct(pointer __p, const _A0 &__a0, _A1 &__a1)
    {
        ::new ((void *)__p) _Tp(__a0, __a1);
    }
    template <class _A0, class _A1>

    void
    construct(pointer __p, _A0 &__a0, const _A1 &__a1)
    {
        ::new ((void *)__p) _Tp(__a0, __a1);
    }
    template <class _A0, class _A1>

    void
    construct(pointer __p, const _A0 &__a0, const _A1 &__a1)
    {
        ::new ((void *)__p) _Tp(__a0, __a1);
    }

    void destroy(pointer __p) { __p->~_Tp(); }
};