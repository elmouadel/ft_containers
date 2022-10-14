

#include <__config>
#include <deque>

namespace std
{
    inline namespace __1
    {

        template <class _Tp, class _Container = deque<_Tp> >
        class stack;

        template <class _Tp, class _Container>

        bool
        operator==(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y);

        template <class _Tp, class _Container>

        bool
        operator<(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y);

        template <class _Tp, class _Container>
        class stack
        {
        public:
            typedef _Container container_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::reference reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::size_type size_type;
            _Static_assert((is_same<_Tp, value_type>::value), "");

        protected:
            container_type c;

        public:
            stack()
                : c()
            {
            }

            stack(const stack &__q) : c(__q.c) {}

            stack &operator=(const stack &__q)
            {
                c = __q.c;
                return *this;
            }
# 154 "/Library/Developer/CommandLineTools/usr/include/c++/v1/stack" 3

            explicit stack(const container_type &__c) : c(__c)
            {
            }

            template <class _Alloc>

            explicit stack(const _Alloc &__a,
                           typename enable_if<uses_allocator<container_type,
                                                             _Alloc>::value>::type * = 0)
                : c(__a)
            {
            }
            template <class _Alloc>

            stack(const container_type &__c, const _Alloc &__a,
                  typename enable_if<uses_allocator<container_type,
                                                    _Alloc>::value>::type * = 0)
                : c(__c, __a)
            {
            }
            template <class _Alloc>

            stack(const stack &__s, const _Alloc &__a,
                  typename enable_if<uses_allocator<container_type,
                                                    _Alloc>::value>::type * = 0)
                : c(__s.c, __a)
            {
            }
# 190 "/Library/Developer/CommandLineTools/usr/include/c++/v1/stack" 3

            bool empty() const
            {
                return c.empty();
            }

            size_type size() const { return c.size(); }

            reference top() { return c.back(); }

            const_reference top() const { return c.back(); }

            void push(const value_type &__v) { c.push_back(__v); }
# 216 "/Library/Developer/CommandLineTools/usr/include/c++/v1/stack" 3

            void pop()
            {
                c.pop_back();
            }

            void swap(stack &__s)

            {
                using std::__1::swap;
                swap(c, __s.c);
            }

            template <class T1, class _C1>
            friend bool
            operator==(const stack<T1, _C1> &__x, const stack<T1, _C1> &__y);

            template <class T1, class _C1>
            friend bool
            operator<(const stack<T1, _C1> &__x, const stack<T1, _C1> &__y);
        };
# 254 "/Library/Developer/CommandLineTools/usr/include/c++/v1/stack" 3
        template <class _Tp, class _Container>
        inline bool
        operator==(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y)
        {
            return __x.c == __y.c;
        }

        template <class _Tp, class _Container>
        inline bool
        operator<(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y)
        {
            return __x.c < __y.c;
        }

        template <class _Tp, class _Container>
        inline bool
        operator!=(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y)
        {
            return !(__x == __y);
        }

        template <class _Tp, class _Container>
        inline bool
        operator>(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y)
        {
            return __y < __x;
        }

        template <class _Tp, class _Container>
        inline bool
        operator>=(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y)
        {
            return !(__x < __y);
        }

        template <class _Tp, class _Container>
        inline bool
        operator<=(const stack<_Tp, _Container> &__x, const stack<_Tp, _Container> &__y)
        {
            return !(__y < __x);
        }

        template <class _Tp, class _Container>
        inline
            typename enable_if<
                __is_swappable<_Container>::value,
                void>::type
            swap(stack<_Tp, _Container> &__x, stack<_Tp, _Container> &__y)

        {
            __x.swap(__y);
        }

        template <class _Tp, class _Container, class _Alloc>
        struct uses_allocator<stack<_Tp, _Container>, _Alloc>
            : public uses_allocator<_Container, _Alloc>
        {
        };

    }
}
