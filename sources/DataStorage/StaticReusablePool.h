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
    void returnItem(HandleType handle);
    void reset();

    T& operator[](const HandleType& index);
    T& at(const HandleType& index);

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
    reset();
}


template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
StaticReusablePool<T, HandleType, poolSize>::~StaticReusablePool() {
    reset();
}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
void StaticReusablePool<T, HandleType, poolSize>::returnItem(HandleType handle) {
    if (static_cast<HandleSize>(handle) < 0 || static_cast<HandleSize>(handle) > poolSize) {
        throw std::out_of_range("Given handle was not valid for this collection.");
    }

    auto& item = data[static_cast<HandleSize>(handle)];
    item.cleanUp();
    item.data.nextIndex = getFirstFreeIndex();
    firstFreeIndex = static_cast<HandleSize>(handle);
    inUseCounter--;
}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
template<typename... Args>
HandleType StaticReusablePool<T, HandleType, poolSize>::getNewItem(Args&&... args) {

    if (getFirstFreeIndex() == poolSize) {
        throw NoMoreItemsException();
    }

    HandleSize tempIndex = getFirstFreeIndex();
    firstFreeIndex = data[tempIndex].data.nextIndex;
    data[tempIndex].reset(std::forward<Args>(args)...);
    inUseCounter++;
    return HandleType(tempIndex);
}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
void StaticReusablePool<T, HandleType, poolSize>::reset() {

    for(HandleSize i = 0; i < maxSize(); ++i) {

        if(data[i].isUsed){
            data[i].cleanUp();
        }

        if(i != maxSize() - 1)
            data[i].data.nextIndex = (i + 1);
        else
            data[i].data.nextIndex = poolSize;
    }
}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
T& StaticReusablePool<T, HandleType, poolSize>::at(const HandleType &index) {

    if (static_cast<HandleType>(index) > 0
    && static_cast<HandleType>(index) < maxSize()
    && data[static_cast<HandleSize>(index)].isUsed) {
        return data[static_cast<HandleSize>(index)].data.object;
    }

    throw std::out_of_range("The given handle was invalid for this collection");
}

template<typename T, typename HandleType, typename HandleType::HandleSize poolSize>
T& StaticReusablePool<T, HandleType, poolSize>::operator[](const HandleType& index) {
    return data[static_cast<HandleSize>(index)].data.object;
}




#endif //VKRENDERER_STATICREUSABLEPOOL_H
