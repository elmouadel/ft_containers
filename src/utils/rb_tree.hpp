/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:56:06 by eabdelha          #+#    #+#             */
/*   Updated: 2022/10/22 08:50:35 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <memory>
#include <stdexcept>
#include <algorithm>
#include "./rb_tree.hpp"
#include "./utility.hpp"
#include "./reverse_iterator.hpp"
#include "./allocator_traits.hpp"
#include "./rb_tree_iterator.hpp"

namespace ft
{
    enum rb_tree_color
    {
        _red_n = false,
        _black_n = true
    };
    //*********************
    template <class _N_ptr>
    inline bool _tree_is_left_child(_N_ptr _n)
    {
        return _n == _n->_parent->_left;
    }
    //*********************
    template <class _N_ptr>
    inline _N_ptr _tree_min(_N_ptr _n)
    {
        while (_n->_left != nullptr)
            _n = _n->_left;
        return _n;
    }
    template <class _N_ptr>
    inline _N_ptr _tree_max(_N_ptr _n)
    {
        while (_n->_right != nullptr)
            _n = _n->_right;
        return _n;
    }
    //*********************
    template <class _N_ptr> 
    inline _N_ptr _tree_next(_N_ptr _n)
    {
        if (_n->_right != nullptr)
            return (_tree_min(_n->_right));
        while (!_tree_is_left_child(_n))
            _n = _n->_parent;
        return (_n->_parent);
    }
    template <class _N_ptr> 
    inline _N_ptr _tree_prev(_N_ptr _n)
    {
        if (_n->_left != nullptr)
            return (_tree_max(_n->_left));
        _N_ptr _nt = _n;
        while (_tree_is_left_child(_nt))
            _nt = _nt->_parent;
        return (_nt->_parent);
    }
    //**************************

    template <class _Tp>
    struct rb_tree_node;

    template <class _Tp>
    struct rb_tree_node_base
    {
        typedef rb_tree_node_base*          n_base_ptr;
        typedef const rb_tree_node_base*    n_const_base_ptr;
        typedef rb_tree_node<_Tp>*          node_ptr;
    
        node_ptr        _parent;
        node_ptr        _left;
        node_ptr        _right;
        rb_tree_color   _color;
    };

    template <class _Tp>
    struct rb_tree_node : public rb_tree_node_base<_Tp>
    {
        typedef _Tp     node_value_type;

        node_value_type _value;
    };

    template <class _Tp, class _Compare, class _Alloc>
    class tree
    {
    public:
        typedef _Tp value_type;
        typedef _Compare value_compare;
        typedef _Alloc allocator_type;
        typedef value_type &refrence;
        typedef const value_type &const_refrence;
        typedef allocator_traits<allocator_type> alloc_traits;
        typedef typename alloc_traits::pointer pointer;
        typedef typename alloc_traits::const_pointer const_pointer;
        typedef typename alloc_traits::size_type size_type;
        typedef typename alloc_traits::difference_type difference_type;

        typedef typename rb_tree_node<value_type>::node_value_type node_value_type;
        typedef typename rb_tree_node<value_type>::node_ptr node_ptr;
        typedef typename rb_tree_node_base<value_type>::n_const_base_ptr n_const_base_ptr;
        typedef typename rb_tree_node_base<value_type>::n_base_ptr n_base_ptr;

        typedef rb_tree_iterator<value_type, node_ptr> iterator;
        typedef rb_tree_const_iterator<value_type, node_ptr> const_iterator;

    private:
        typedef typename allocator_type::template rebind<rb_tree_node<value_type> >::other node_allocator;
        typedef allocator_traits<node_allocator> n_alloc_traits;

    private:
        node_ptr        _begin_node;
        node_ptr        _end_node;
        allocator_type  _alloc;
        node_allocator  _n_alloc;
        value_compare   _k_comp;
        size_type       _size;

/* ************************************************************************** */
                            // Costructors :
/* ************************************************************************** */
    public:
        explicit tree(const value_compare &_comp, const allocator_type &_alloc)
            : _alloc(_alloc), _n_alloc(_alloc), _k_comp(_comp), _size(0)
        {
            _end_node = n_alloc_traits::allocate(_n_alloc, 1);
            _begin_node = _end_node;
            _end_node->_parent = _end_node->_left = _end_node->_right = nullptr;
        }

        tree(const tree &_t)
            : _alloc(_t._alloc), _n_alloc(_t._alloc), _k_comp(_t._k_comp), _size(0)
        {
            _end_node = n_alloc_traits::allocate(_n_alloc, 1);
            _begin_node = _end_node;
            _end_node->_parent = _end_node->_left = _end_node->_right = nullptr;
        }
        ~tree()
        {
            clear();
            n_alloc_traits::deallocate(_n_alloc, _end_node, 1);
        }
/* ************************************************************************** */
                            // Iterators :
/* ************************************************************************** */
        iterator begin() { return iterator(_begin_node); }

        iterator end() { return iterator(_end_node); }
        
        const_iterator begin() const { return const_iterator(_begin_node); }

        const_iterator end() const { return const_iterator(_end_node); }
        
/* ************************************************************************** */
                            // Capacity :
/* ************************************************************************** */
        size_type max_size() const
        {
            return (std::min<size_type>(alloc_traits::max_size(_n_alloc),
                            std::numeric_limits<difference_type>::max()));
        }
        size_type size() const { return (_size); }
/* ************************************************************************** */
                            // node handle :
/* ************************************************************************** */
    private:
        node_ptr _construct_node(const value_type &_val)
        {
            node_ptr _ret;
            _ret = n_alloc_traits::allocate(_n_alloc, 1);
            alloc_traits::construct(_alloc, &(_ret->_value), _val);
            _ret->_parent = _ret->_left = _ret->_right = nullptr;
            if (!_end_node->_left)
                _ret->_color = _black_n;
            else
                _ret->_color = _red_n;
            return (_ret);
        }
        void _destruct_node(node_ptr _n)
        {
            alloc_traits::destroy(_alloc, &(_n->_value));
            n_alloc_traits::deallocate(_n_alloc, _n, 1);
        }
/* ************************************************************************** */
                            // geters :
/* ************************************************************************** */
    public:
        const node_allocator &_node_alloc() const
        {
            return (_n_alloc);
        }
        const value_compare &value_comp() const
        {
            return (_k_comp);
        }
        value_compare &value_comp()
        {
            return (_k_comp);
        }
        const node_ptr &root() const 
        { 
            return _end_node->_left; 
        }
        const node_ptr &end_node() const 
        { 
            return _end_node; 
        }
        const allocator_type &alloc() const
        {
            return (_alloc);
        }

/* ************************************************************************** */
                            // Modifiers :
/* ************************************************************************** */
    public:
        void clear()
        {
            destroy(_end_node->_left);
            _end_node->_left = nullptr;
            _begin_node = _end_node;
            _size = 0;
        }
        void swap(tree &_t)
        {
            std::swap(_end_node, _t._end_node);
            std::swap(_begin_node, _t._begin_node);
            std::swap(_size, _t._size);
            // std::swap(_n_alloc, _t._n_alloc);
            // std::swap(_alloc, _t._alloc);
            // std::swap(_k_comp, _t._k_comp);
        }
        
        pair<iterator, bool> _insert_unique(const value_type &_val)
        {
            node_ptr    _parent_pos = root();
            bool        _is_left = true;
            bool        _inserted;
            
            _inserted = _find_parent(_parent_pos, _val, _is_left);

            node_ptr    _new_n = _parent_pos;
            if (_inserted)
            {
                _new_n = _construct_node(_val);
                _insert_node_at(_parent_pos, _new_n, _is_left);
            }
            return (pair<iterator, bool>(iterator(_new_n), _inserted));
        }
        iterator _insert_unique(node_ptr _hint, const value_type &_val)
        {
            node_ptr    _parent_pos = root();
            bool        _is_left = true;
            bool        _inserted;
            
            _inserted = _find_parent(_hint, _parent_pos, _val, _is_left);

            node_ptr    _new_n = _parent_pos;
            if (_inserted)
            {
                _new_n = _construct_node(_val);
                _insert_node_at(_parent_pos, _new_n, _is_left);
            }
            return (iterator(_new_n));
        }
        void _erase(node_ptr _pos)
        {
            if (_begin_node == _pos)
                _begin_node = _tree_next(_pos);
            _tree_delete_node(_end_node->_left, _pos);
            _destruct_node(_pos);
            --_size;
        }
/* ************************************************************************** */
                            // Lookup :
/* ************************************************************************** */
    public:
        node_ptr _lower_bound(const value_type &_val) const
        {
            node_ptr _pos = root();
            node_ptr _ret = _end_node;
            
            while (_pos)
            {
                if (!value_comp()(_pos->_value, _val))
                {
                    _ret = _pos;
                    _pos = _pos->_left;
                }
                else
                    _pos = _pos->_right;
            }
            return (_ret);
        }
        node_ptr _upper_bound(const value_type &_val) const
        {
            node_ptr _pos = root();
            node_ptr _ret = _end_node;
            
            while (_pos)
            {
                if (value_comp()(_val, _pos->_value))
                {
                    _ret = _pos;
                    _pos = _pos->_left;
                }
                else
                    _pos = _pos->_right;
            }
            return (_ret);
        }
        pair<node_ptr, node_ptr> _equal_range(const value_type &_val) const
        {
            node_ptr _pos = root();
            node_ptr _ret = _end_node;
            
            while (_pos)
            {
                if (value_comp()(_val, _pos->_value))
                {
                    _ret = _pos;
                    _pos = _pos->_left;
                }
                else if (value_comp()(_pos->_value, _val))
                    _pos = _pos->_right;
                else
                {
                    if (_pos->_right)
                        _ret = _tree_min(_pos->_right);
                    return (pair<node_ptr, node_ptr>(_pos, _ret));
                }
            }
            return (pair<node_ptr, node_ptr>(_ret, _ret));
        }

/* ************************************************************************** */
                            // Modifiers utils :
/* ************************************************************************** */
    public:
        bool _find_parent(node_ptr &_pos,const value_type &_val) const
        {
            if (!_pos)
                return(true);
                
            while (true)
            {
                if (value_comp()(_val, _pos->_value))
                {
                    if (_pos->_left)
                        _pos = _pos->_left;
                    else
                        return (true);
                }
                else if (value_comp()(_pos->_value, _val))
                {
                    if (_pos->_right)
                        _pos = _pos->_right;
                    else
                        return (true);
                }
                else
                    return (false);
            }
        }
    private:
        bool _find_parent(node_ptr &_parent_pos, const value_type &_val, bool &_is_left)
        {
            if (!_parent_pos)
                return(_parent_pos = _end_node, true);
                
            while (true)
            {
                if (value_comp()(_val, _parent_pos->_value))
                {
                    if (_parent_pos->_left)
                        _parent_pos = _parent_pos->_left;
                    else
                        return (true);
                }
                else if (value_comp()(_parent_pos->_value, _val))
                {
                    if (_parent_pos->_right)
                        _parent_pos = _parent_pos->_right;
                    else
                        return (_is_left = false, true);
                }
                else
                    return (false);
            }
        }
        bool _find_parent(node_ptr _hint, node_ptr &_parent_pos, const value_type &_val, bool &_is_left)
        {
            if (!_parent_pos)
                return(_parent_pos = _end_node, true);
                
            if (_hint != _end_node && value_comp()(_hint->_value, _val))
            {
                node_ptr _next = _tree_next(_hint);
                if (_next == _end_node || value_comp()(_val, _next->_value))
                {
                    if (_hint->_right)
                    {
                        _parent_pos = _tree_min(_hint->_right);
                        return (true);
                    }
                    else
                    {
                        _parent_pos = _hint;
                        return (_is_left = false, true);
                    }
                }
                else if (!value_comp()(_next->_value, _val))
                {
                    _parent_pos = _next;
                    return (false);
                }
            }
            else if (_hint != _end_node && !value_comp()(_val, _hint->_value))
            {
                _parent_pos = _hint;
                return (false);
            }
            return (_find_parent(_parent_pos, _val, _is_left));
        }
        void _insert_node_at(node_ptr _parent_pos, node_ptr _new_n, bool _is_left)
        {
            if (_is_left)
                _parent_pos->_left = _new_n;
            else
                _parent_pos->_right = _new_n;

            _new_n->_parent = _parent_pos;    
            if (_begin_node->_left)
                _begin_node = _begin_node->_left;
            _tree_balance_after_insert(root(), _new_n);
            ++_size;
        }
        void destroy(node_ptr _n)
        {
            if (_n)
            {
                destroy(_n->_left);
                destroy(_n->_right);
                _destruct_node(_n);
            }
        }
/* ************************************************************************** */
                            // private utils functions :
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
                            // insert node :
/* ************************************************************************** */
    private:
        void _right_rotate_tree(node_ptr _n) const
        {
            if (_tree_is_left_child(_n->_parent))
                _n->_parent->_parent->_left = _n;
            else
                _n->_parent->_parent->_right = _n;
            _n->_parent->_left = _n->_right;
            if (_n->_right)
                _n->_right->_parent = _n->_parent;
            _n->_right = _n->_parent;
            
            _n->_parent = _n->_right->_parent;
            _n->_right->_parent = _n;    
        }
        void _left_rotate_tree(node_ptr _n) const
        {
            if (_tree_is_left_child(_n->_parent))
                _n->_parent->_parent->_left = _n;
            else
                _n->_parent->_parent->_right = _n;
            _n->_parent->_right = _n->_left;
            if (_n->_left)
                _n->_left->_parent = _n->_parent;
            _n->_left = _n->_parent;
            
            _n->_parent = _n->_left->_parent;
            _n->_left->_parent = _n;    
        }
        bool _is_red_sibling(node_ptr _n) const
        {
            if (_tree_is_left_child(_n))
            {
                if (_n->_parent->_right)
                    return (_n->_parent->_right->_color == _red_n);
                return (false);
            }
            if (_n->_parent->_left)
                return (_n->_parent->_left->_color == _red_n);
            return (false);
        }
        void _tree_balance_after_insert(node_ptr _root, node_ptr _n) const
        {
            while (_n != _root)
            {
                if (_n->_parent->_color == _black_n)
                    return;
                // check parent sibling color
                if (!_is_red_sibling(_n->_parent))
                {
                    // do suitable rotation
                    if (_tree_is_left_child(_n->_parent))
                    {
                        if (!_tree_is_left_child(_n))
                            _left_rotate_tree(_n);
                        else
                            _n = _n->_parent;
                        _right_rotate_tree(_n);
                            
                    }
                    else
                    {
                        if (_tree_is_left_child(_n))
                            _right_rotate_tree(_n);
                        else
                            _n = _n->_parent;
                        _left_rotate_tree(_n);
                    }
                    // give black to the parent 
                    _n->_color = _black_n;
                    // and red to the children
                    _n->_left->_color = _n->_right->_color = _red_n;
                    return ; 
                }
                else
                {
                    // take the red to a higher level
                    if (_n->_parent->_parent != _root)
                        _n->_parent->_parent->_color = _red_n;
                    _n->_parent->_parent->_left->_color = _n->_parent->_parent->_right->_color = _black_n;
                    // move _n to the new red node and continue
                    _n = _n->_parent->_parent;
                }
            }
        }
/* ************************************************************************** */
                            // delete node :
/* ************************************************************************** */
        bool _is_leaf_red_node(node_ptr _n) const
        {
            if (_n->_color == _red_n && !_n->_left && !_n->_right)
                return true;
            return false;
        }
        bool _has_black_children(node_ptr _n) const
        {
            return ((!_n->_left || _n->_left->_color == _black_n) 
            && (!_n->_right || _n->_right->_color == _black_n));
        }
        void _assign_to_right_parent(node_ptr _n, node_ptr _val) const
        {
            if (_tree_is_left_child(_n))
                _n->_parent->_left = _val;
            else
                _n->_parent->_right = _val;
        }
        void _rotate_to_opposite_side(node_ptr _n) const
        {
            if (_tree_is_left_child(_n))
                _right_rotate_tree(_n);
            else
                _left_rotate_tree(_n);
        }
        void _change_children_parents(node_ptr _n1, node_ptr _n2) const
        {
             if (_n1->_right && _n1->_right != _n2)
                _n1->_right->_parent = _n2;
            if (_n2->_right)
                _n2->_right->_parent = _n1;
            if (_n1->_left && _n1->_left != _n2)
                _n1->_left->_parent = _n2;
            if (_n2->_left)
                _n2->_left->_parent = _n1;
        }
        void _swap_node(node_ptr _n1, node_ptr _n2) const
        {
            _change_children_parents(_n1, _n2);
            _assign_to_right_parent(_n1, _n2);
            _assign_to_right_parent(_n2, _n1);
    
            std::swap(_n1->_left, _n2->_left);
            std::swap(_n1->_right, _n2->_right);
            std::swap(_n1->_parent, _n2->_parent); 
    
            std::swap(_n1->_color, _n2->_color);
        }
        void _swap_related_nodes(node_ptr _n1, node_ptr _n2) const
        {
            _change_children_parents(_n1, _n2);
            _assign_to_right_parent(_n1, _n2);
                
            if (_tree_is_left_child(_n2))
            {
                std::swap(_n1->_right, _n2->_right);
                _n1->_left = _n2->_left;
                _n2->_left = _n1;
            }
            else
            {
                std::swap(_n1->_left, _n2->_left);
                _n1->_right = _n2->_right;
                _n2->_right = _n1;
            }
            _n2->_parent = _n1->_parent;
            _n1->_parent = _n2;
            
            std::swap(_n1->_color, _n2->_color);
        }
        void _get_leaf_node(node_ptr _n) const
        {
            node_ptr _nx = _n;
            
            while (_n->_left || _n->_right)
            {
                if (_n->_right)
                    _nx = _tree_next(_n);
                else
                    _nx = _tree_prev(_n);
                if (_nx->_parent != _n)
                    _swap_node(_n, _nx);
                else
                    _swap_related_nodes(_n, _nx);
            }
        } 
        node_ptr _get_node_sibling(node_ptr &_n, node_ptr _root) const
        {
            while ((!_n->_parent->_left || !_n->_parent->_right) && _n != _root)
                _n = _n->_parent;
            if (_tree_is_left_child(_n))
                return _n->_parent->_right;
            else
                return _n->_parent->_left;
        }
        void _tree_delete_node(node_ptr _root, node_ptr _n) const
        {
            _get_leaf_node(_n);
            // if the node to be deleted is red or it's the root of the tree
            // give null to its parent and exit
            if (_is_leaf_red_node(_n) || _n == _root)
                return _assign_to_right_parent(_n, (node_ptr)nullptr);
            
            //remember the leaf node to assigne null to its parent
            node_ptr _old_n = _n;
            node_ptr _s;
            _s = _get_node_sibling(_n, _root);
            // loop to until no double black
            while (_n->_color == _black_n)
            {
                if (_n == _root)
                    break;
                // check the color of the "double black node sibling" = _s
                if (_s->_color == _black_n)
                {
                    // check the color of _s children
                    if (_has_black_children(_s))
                    {
                        _s->_color = _red_n;
                        // if _s parent color is red change it to black and break the loop
                        if (_s->_parent->_color == _red_n)
                            { _s->_parent->_color = _black_n; break; }
                        // else move the double black to _s parent and continue
                        _n = _n->_parent;
                        _s = _get_node_sibling(_n, _root);
                        continue;
                    }
                    //get far and near nephews
                    node_ptr _far_n = nullptr;
                    node_ptr _near_n = nullptr;
                    if (_tree_is_left_child(_n))
                    { _far_n = _s->_right; _near_n = _s->_left; }
                    else
                    { _far_n = _s->_left; _near_n = _s->_right; }
                    
                    // if far nephew is red
                    if (_far_n && _far_n->_color == _red_n)
                    {
                        std::swap(_s->_color, _n->_parent->_color);
                        _rotate_to_opposite_side(_s);
                        _far_n->_color = _black_n;
                        break;
                    }
                    // if near nephew is red
                    else
                    {
                        std::swap(_s->_color, _near_n->_color);
                        _rotate_to_opposite_side(_near_n);
                        _s = _near_n; 
                    }
                }
                // if _s color is red
                else
                {
                    std::swap(_s->_color, _n->_parent->_color);
                    _rotate_to_opposite_side(_s);
                    _s = _get_node_sibling(_n, _root);
                }
            }
            return _assign_to_right_parent(_old_n, (node_ptr)nullptr);    
        }
    };
}

#endif