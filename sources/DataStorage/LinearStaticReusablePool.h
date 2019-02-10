//
// Created by hindrik on 10-2-19.
//

#ifndef VKRENDERER_LINEARSTATICREUSABLEPOOL_H
#define VKRENDERER_LINEARSTATICREUSABLEPOOL_H


#include "LinearPoolItem.h"
#include "StaticReusablePool.h"
#include <iostream>

template <typename T, typename HandleType = Handle<T, uint16_t>, typename HandleType::HandleSizeType poolSize = HandleType::invalidMaxValue - 1 >
class LinearStaticReusablePool final
{
    static_assert(poolSize >= 0 && poolSize < HandleType::invalidMaxValue, "You must select a size between (and including) 2 and handleSize - 1");
    typedef typename HandleType::HandleSizeType HandleSizeType;
    using IndexPoolHandleType = Handle<HandleSizeType, HandleSizeType>;
public:
    LinearStaticReusablePool();
    ~LinearStaticReusablePool();
private:
    array <LinearPoolItem<T>, poolSize>                     items;
    array <HandleSizeType, poolSize>                            mappedIndices;
    StaticReusablePool  <HandleSizeType, IndexPoolHandleType, poolSize>  indices;

    HandleSizeType inUseCounter = 0;
public:

    LinearStaticReusablePool(const LinearStaticReusablePool& rhs);
    LinearStaticReusablePool(LinearStaticReusablePool&& rhs) noexcept;
    LinearStaticReusablePool& operator=(LinearStaticReusablePool&& rhs) noexcept;
    LinearStaticReusablePool& operator=(const LinearStaticReusablePool& rhs);

    template<typename... Args>
    HandleType getItem(Args... args);

    void returnItem(HandleType index);

    T& operator[] (HandleType index);

    T* begin();
    T* end();

    HandleSizeType size() const;
    HandleSizeType maxSize() const;

    void reset();
};

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
template<typename... Args>
HandleType LinearStaticReusablePool<T, HandleType, poolSize>::getItem(Args... args) {

    HandleSizeType newIndex = indices.getItem(inUseCounter);
    items[newIndex].reset(std::move(args)...);
    ++inUseCounter;
    indices[IndexPoolHandleType (newIndex)] = newIndex;
    mappedIndices[newIndex] = newIndex;
    return HandleType(newIndex);
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
void LinearStaticReusablePool<T, HandleType, poolSize>::returnItem(HandleType index) {

    if(static_cast<HandleSizeType>(index) == HandleType::invalidMaxValue)
        throw "Invalid index";

    HandleSizeType mappedIndex = indices[IndexPoolHandleType(static_cast<HandleSizeType>(index))];

    if(mappedIndex == inUseCounter - 1)
    {
        items[mappedIndex].cleanUp();
        mappedIndices[HandleSizeType(index)] = HandleType::invalidMaxValue;
        indices.returnItem(IndexPoolHandleType(static_cast<HandleSizeType>(index)));
        --inUseCounter;
    }
    else
    {
        //Oude wegsmijten
        items[mappedIndex].cleanUp();
        mappedIndices[HandleSizeType(index)] = HandleType::invalidMaxValue;
        indices.returnItem(IndexPoolHandleType(HandleSizeType(index)));

        //Laatste plaatsen op mappedIndex
        HandleSizeType nonMappedLastIndex = inUseCounter - static_cast<HandleSizeType>(1);
        HandleSizeType mappedLastIndex = indices[IndexPoolHandleType(nonMappedLastIndex)];

        //laatste moven en index setten
        indices[IndexPoolHandleType(mappedLastIndex)] = mappedIndex;
        items[mappedIndex].data.object = std::move(items[nonMappedLastIndex].data.object);

        --inUseCounter;
    }
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
LinearStaticReusablePool<T, HandleType, poolSize>::LinearStaticReusablePool() {
    for(HandleSizeType i = 0; i < poolSize; ++i)
    {
        mappedIndices[i] = HandleType::invalidMaxValue;
    }
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
typename HandleType::HandleSizeType LinearStaticReusablePool<T, HandleType, poolSize>::maxSize() const {
    return poolSize;
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
T& LinearStaticReusablePool<T, HandleType, poolSize>::operator[](const HandleType index) {
    HandleSizeType mappedIndex = indices[index];
    return items[mappedIndex].data.object;
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
T* LinearStaticReusablePool<T, HandleType, poolSize>::begin() {
    return &(items.begin()->data.object);
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
T* LinearStaticReusablePool<T, HandleType, poolSize>::end() {
    return &(items.begin() + size())->data.object;
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
typename HandleType::HandleSizeType LinearStaticReusablePool<T, HandleType, poolSize>::size() const {
    return inUseCounter;
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
LinearStaticReusablePool<T, HandleType, poolSize>::LinearStaticReusablePool(const LinearStaticReusablePool<T, HandleType, poolSize> & rhs)
{
    indices = std::move(rhs.indices);
    inUseCounter = rhs.inUseCounter;
    mappedIndices = rhs.mappedIndices;


    for(HandleSizeType i = 0; i < rhs.size(); ++i)
    {
        items[i].data.object = rhs.items[i].data.object;
    }
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
LinearStaticReusablePool<T, HandleType, poolSize>::LinearStaticReusablePool(LinearStaticReusablePool<T, HandleType, poolSize> && rhs) noexcept
{
    indices = std::move(rhs.indices);
    inUseCounter = rhs.inUseCounter;
    mappedIndices = rhs.mappedIndices;


    for(HandleSizeType i = 0; i < rhs.size(); ++i)
    {
        items[i].data.object = std::move(rhs.items[i].data.object);
    }
    rhs.reset();
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
LinearStaticReusablePool<T, HandleType, poolSize>& LinearStaticReusablePool<T, HandleType, poolSize>::operator=(LinearStaticReusablePool<T, HandleType, poolSize> && rhs) noexcept
{
    indices = std::move(rhs.indices);
    inUseCounter = rhs.inUseCounter;
    mappedIndices = rhs.mappedIndices;


    for(HandleSizeType i = 0; i < rhs.size(); ++i)
    {
        items[i].data.object = std::move(rhs.items[i].data.object);
    }
    rhs.reset();
    return *this;
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
LinearStaticReusablePool<T, HandleType, poolSize>& LinearStaticReusablePool<T, HandleType, poolSize>::operator=(const LinearStaticReusablePool<T, HandleType, poolSize> & rhs)
{
    indices = std::move(rhs.indices);
    inUseCounter = rhs.inUseCounter;
    mappedIndices = rhs.mappedIndices;


    for(HandleSizeType i = 0; i < rhs.size(); ++i)
    {
        items[i].data.object = rhs.items[i].data.object;
    }
    return *this;
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
void LinearStaticReusablePool<T, HandleType, poolSize>::reset()
{
    for(HandleSizeType  i = 0; i < inUseCounter; ++i)
    {
        items[i].cleanUp();
    }

    for(HandleSizeType i = 0; i < poolSize; ++i)
    {
        mappedIndices[i] = HandleType::invalidMaxValue;
    }

    indices.reset();

    inUseCounter = 0;
}

template<typename T, typename HandleType, typename HandleType::HandleSizeType poolSize>
LinearStaticReusablePool<T, HandleType, poolSize>::~LinearStaticReusablePool() = default;


#endif //VKRENDERER_LINEARSTATICREUSABLEPOOL_H
