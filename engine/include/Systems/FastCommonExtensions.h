//
// Created by Admin on 08/08/2025.
//

#ifndef FASTCOMMONEXTENSIONS_H
#define FASTCOMMONEXTENSIONS_H

#include <vector>
#endif //FASTCOMMONEXTENSIONS_H




///Does not preserve order, but will quickly remove an element
template<typename T>
void erase_at( std::vector<T> &v, typename std::vector<T>::size_type i ) {
    if ( i < v.size() ) {
        if ( i < v.size() - 1 )
            v[i] = std::move( v.back() );
        v.pop_back();
    }
}
