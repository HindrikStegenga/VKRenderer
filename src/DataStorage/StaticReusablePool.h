//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#ifndef VKRENDERER_STATICREUSABLEPOOL_H
#define VKRENDERER_STATICREUSABLEPOOL_H

#include <cstdint>
#include <array>

using std::array;

#include "../Utilities/Handle.h"
#include "ReusablePoolItem.h"

template<typename T, typename HandleType = Handle<T, uint16_t, std::numeric_limits<uint16_t>::max()> >
class StaticReusablePool final {
private:

    //array<ReusablePoolItem<T, HandleType>, std::numeric_limits<MaxSize>::max()> data = {};


public:



public:




};


#endif //VKRENDERER_STATICREUSABLEPOOL_H
