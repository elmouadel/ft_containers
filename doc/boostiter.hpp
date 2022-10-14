/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boostiter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:43:38 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/14 11:33:28 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename _Tp>
struct _Rb_tree_iterator
{
    typedef _Tp value_type;
    typedef _Tp &reference;
    typedef _Tp *pointer;

    typedef bidirectional_iterator_tag ite  rator_category;
    typedef ptrdiff_t difference_type;

    typedef _Rb_tree_iterator<_Tp> _Self;
    typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
    typedef _Rb_tree_node<_Tp> *_Link_type;

    _Rb_tree_iterator()
        : _M_node() {}

    explicit _Rb_tree_iterator(_Link_type __x)
        : _M_node(__x) {}

    reference
    operator*() const
    {
        return static_cast<_Link_type>(_M_node)->_M_value_field;
    }

    pointer
    operator->() const
    {
        return std::__addressof(static_cast<_Link_type>(_M_node)->_M_value_field);
    }

    _Self &
    operator++()
    {
        _M_node = _Rb_tree_increment(_M_node);
        return *this;
    }

    _Self
    operator++(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_increment(_M_node);
        return __tmp;
    }

    _Self &
    operator--()
    {
        _M_node = _Rb_tree_decrement(_M_node);
        return *this;
    }

    _Self
    operator--(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_decrement(_M_node);
        return __tmp;
    }

    bool
    operator==(const _Self &__x) const
    {
        return _M_node == __x._M_node;
    }

    bool
    operator!=(const _Self &__x) const
    {
        return _M_node != __x._M_node;
    }

    _Base_ptr _M_node;
};

template <typename _Tp>
struct _Rb_tree_const_iterator
{
    typedef _Tp value_type;
    typedef const _Tp &reference;
    typedef const _Tp *pointer;

    typedef _Rb_tree_iterator<_Tp> iterator;

    typedef bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef _Rb_tree_const_iterator<_Tp> _Self;
    typedef _Rb_tree_node_base::_Const_Base_ptr _Base_ptr;
    typedef const _Rb_tree_node<_Tp> *_Link_type;

    _Rb_tree_const_iterator()
        : _M_node() {}

    explicit _Rb_tree_const_iterator(_Link_type __x)
        : _M_node(__x) {}

    _Rb_tree_const_iterator(const iterator &__it)
        : _M_node(__it._M_node) {}

    iterator
    _M_const_cast() const
    {
        return iterator(static_cast<typename iterator::_Link_type>(const_cast<typename iterator::_Base_ptr>(_M_node)));
    }

    reference
    operator*() const
    {
        return static_cast<_Link_type>(_M_node)->_M_value_field;
    }

    pointer
    operator->() const
    {
        return std::__addressof(static_cast<_Link_type>(_M_node)->_M_value_field);
    }

    _Self &
    operator++()
    {
        _M_node = _Rb_tree_increment(_M_node);
        return *this;
    }

    _Self
    operator++(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_increment(_M_node);
        return __tmp;
    }

    _Self &
    operator--()
    {
        _M_node = _Rb_tree_decrement(_M_node);
        return *this;
    }

    _Self
    operator--(int)
    {
        _Self __tmp = *this;
        _M_node = _Rb_tree_decrement(_M_node);
        return __tmp;
    }

    bool
    operator==(const _Self &__x) const
    {
        return _M_node == __x._M_node;
    }

    bool
    operator!=(const _Self &__x) const
    {
        return _M_node != __x._M_node;
    }

    _Base_ptr _M_node;
};



//**********************************************************************************
//**********************************************************************************
//**********************************************************************************
    // public:
    //     void print_tree(node_ptr _root, int lvl = 0) const 
    //     {
    //         if (_root == NULL)
    //         {
    //             padding('\t', lvl);
    //             // std::cout << "~";
    //         }
    //         else
    //         {
    //             print_tree(_root->_left, lvl + 1);
    //             padding('\t', lvl*2);
    //             if (_root->_color == _red_n)
    //                 std::cout << "r";
    //             std::cout << _root->_value.first /*<< ":" << _root->_value.second*/;
    //             // if (_root->_parent)
    //             //     std::cout << _root->_parent->_value.first;
    //             // else
    //             //     std::cout << "NULL";
    //             std::cout << std::endl;
    //             print_tree(_root->_right, lvl + 1);
    //         }
    //         std::cout << std::endl;
    //     }
    //     void padding(char c, int n) const
    //     {
    //         for (int i = 0; i < n; i++)
    //             std::cout << c;
    //     }
    //     void find_node_next(node_ptr root, int lvl, node_ptr *arr, size_t &indx)
    //     {
    //         if (!root)
    //         {
    //             lvl = pow(2, lvl);
    //             while (lvl-- > 0)
    //                 arr[indx++] = NULL;
    //             return ;
    //         }
    //         if (lvl == 1)
    //         {
    //             arr[indx++] = root->_left;
    //             arr[indx++] = root->_right;
    //             return;
    //         }
    //         find_node_next(root->_left, lvl-1, arr, indx);
    //         find_node_next(root->_right, lvl-1, arr, indx);
    //     }
    //     void print_tree_2(node_ptr _root)
    //     {
    //         node_ptr arr[1000000];
    //         size_t index = 1;
    //         size_t height = 2 * log2(size());
            
    //         arr[0] = _root;
    //         for (size_t j = 0 ; j < height; j++)
    //                 find_node_next(_root, j + 1, arr, index);
    //         size_t lvl = 1;
    //         int pad = height * 16;
    //         while (arr[--index] == NULL);
            
    //         for (size_t i = 0; i <= index; i++)
    //         {
    //             if (i + 1 == lvl)
    //             {                
    //                 std::cout << "\n\n\n";
    //                 lvl *= 2;
    //                 pad /= 2;
    //             }
    //             padding(' ', pad);
    //             if (arr[i])
    //             {
    //                 if (arr[i]->_color == _red_n)
    //                     std::cout << "\e[0;31m";
    //                 std::cout << '(' << arr[i]->_value.first << ')' << "\e[0m";
    //             }
    //             else
    //                 std::cout << "  ";
    //             padding(' ', pad);
    //         }
    //         std::cout << "\n\n\n";
    //         (void)_root;
    //         (void)arr;
    //     }
    
//**********************************************************************************
