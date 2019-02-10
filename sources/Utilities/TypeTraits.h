//
// Created by Hindrik  Stegenga on 09/03/2018.
//

#ifndef VKRENDERER_TYPETRAITS_H
#define VKRENDERER_TYPETRAITS_H

#include <typeinfo>

template<typename T>
struct TypeTraits final {
    static const char* name();
};

template <typename T>
inline const char* TypeTraits<T>::name()  {
    return typeid(T).name();
}

#endif //VKRENDERER_TYPETRAITS_H