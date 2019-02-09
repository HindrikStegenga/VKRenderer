//
// Created by hindrik on 7-2-19.
//

#ifndef VKRENDERER_TYPEID_H
#define VKRENDERER_TYPEID_H

#include <cstdint>

class TypeID {
public:
    static uint64_t count;
public:
    template<typename U>
    static uint64_t get() {
        static uint64_t typeID { count++ };
        return typeID;
    }
};

#endif //VKRENDERER_TYPEID_H
