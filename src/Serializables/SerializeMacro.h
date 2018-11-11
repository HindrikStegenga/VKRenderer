//
// Created by Hindrik Stegenga on 11/11/2018.
//

#ifndef VKRENDERER_SERIALIZEMACRO_H
#define VKRENDERER_SERIALIZEMACRO_H

#define SERIALIZE_START(Type) namespace meta { \
    template <> \
    inline auto registerMembers<Type>() \
    { \
        return members( \

#define SERIALIZE_MEMBER(name, member_var) member(name, &member_var)
#define SERIALIZE_GETSET(name, member_get, member_set) member(name, &member_get, &member_set)

#define SERIALIZE_END ); \
    } \
}


#endif //VKRENDERER_SERIALIZEMACRO_H
