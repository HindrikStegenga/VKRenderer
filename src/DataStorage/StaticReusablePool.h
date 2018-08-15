//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#ifndef VKRENDERER_STATICREUSABLEPOOL_H
#define VKRENDERER_STATICREUSABLEPOOL_H

#include <cstdint>
#include <array>
#include "Exceptions/NoMoreItemsException.h"

using std::array;

#include "Handle.h"
#include "ReusablePoolItem.h"

template<typename T, typename HandleType = Handle<T, uint16_t>, typename HandleType::HandleSize poolSize = HandleType::invalidMaxValue - 1>
class StaticReusablePool final {
    static_assert(poolSize >= 0 && poolSize < HandleType::invalidMaxValue, "You must select a size between (and including) 2 and handleSize - 1");
    typedef typename HandleType::HandleSize HandleSize;
private:
    array<ReusablePoolItem<T, HandleType>, poolSize> data = {};
    HandleSize inUseCounter     = 0;
    HandleSize firstFreeIndex   = 0;
public:
    StaticReusablePool();
    ~StaticReusablePool();

    StaticReusablePool(const StaticReusablePool&)     = delete;
    StaticReusablePool(StaticReusablePool&&) noexcept = default;

    StaticReusablePool& operator=(const StaticReusablePool&)        = delete;
    StaticReusablePool& operator=(StaticReusablePool&&) noexcept    = default;

    HandleSize size() const;
    HandleSize maxSize() const;
    HandleSize getFirstFreeIndex() const;

    template<typename ... Args>
    HandleType getNewItem(Args&&... args);

};

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
typename HandleType::HandleSize StaticReusablePool<T, HandleType, poolSize>::size() const {
    return inUseCounter;
}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
typename HandleType::HandleSize StaticReusablePool<T, HandleType, poolSize>::maxSize() const {
    return poolSize;
}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
typename HandleType::HandleSize StaticReusablePool<T, HandleType, poolSize>::getFirstFreeIndex() const {
    return firstFreeIndex;
}



template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
StaticReusablePool<T, HandleType, poolSize>::StaticReusablePool() {
    for(HandleSize i = 0; i < maxSize(); ++i) {
        if(i != maxSize() - 1)
            data[i].data.nextIndex = (i + 1);
        else
            data[i].data.nextIndex = HandleType::invalidMaxValue;
    }
}



template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
StaticReusablePool<T, HandleType, poolSize>::~StaticReusablePool() {

}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
template<typename... Args>
HandleType StaticReusablePool<T, HandleType, poolSize>::getNewItem(Args&&... args) {

    if (getFirstFreeIndex() == HandleType::invalidMaxValue) {
        throw NoMoreItemsException();
    }

    HandleSize tempIndex = getFirstFreeIndex();
    firstFreeIndex = data[tempIndex].data.nextIndex;
    data[tempIndex].reset(std::forward(args)...);
    inUseCounter++;
    return HandleType(tempIndex);
}


#endif //VKRENDERER_STATICREUSABLEPOOL_H
