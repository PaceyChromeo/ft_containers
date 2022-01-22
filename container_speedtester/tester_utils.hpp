/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_utils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youssou <youssou@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:03:18 by youssou           #+#    #+#             */
/*   Updated: 2022/01/22 15:43:56 by sayari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stack/stack.hpp"
#include "../vector/vector.hpp"
#include "../set/set.hpp"
#include <vector>
#include <map>
#include <set>
#include <stack>


#ifndef NAME //Namespace Type to be tested
# define NAME ft
#endif

template<class T>
void fill_map(T &a, int b){
    for(int i=0; i < b; i++){
        a.insert(NAME::make_pair(i,i));
    }
}

template<class T>
void fill_set(T &a, int b){
    for(int i=0; i < b; i++){
        a.insert(i);
    }
}
