/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <eabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:55:40 by eabdelha          #+#    #+#             */
/*   Updated: 2022/09/22 14:43:43 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
    
    template<class Tp>
    struct  iterator_traits<Tp*>
    {
        typedef ptrdiff_t difference_type;
        typedef Tp value_type;
        typedef Tp* pointer;
        typedef Tp& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
    
}