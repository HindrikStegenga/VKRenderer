//
// Created by Hindrik Stegenga on 11/11/2018.
//

#ifndef VKRENDERER_SERIALIZEMACRO_H
#define VKRENDERER_SERIALIZEMACRO_H

#define SERIALIZE_START(Type) namespace meta { \
    template <> \
    inline auto registerMembers<Test>() \
    { \
        return members( \

#define SERIALIZE_MEMBER(name, member_var) member(name, &member_var)

#define SERIALIZE_END ); \
    } \
}


#endif //VKRENDERER_SERIALIZEMACRO_H
