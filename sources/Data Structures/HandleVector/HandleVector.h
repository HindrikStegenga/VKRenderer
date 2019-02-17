//
// Created by hindrik on 16-2-19.
//

#ifndef VKRENDERER_HANDLE_VECTOR_H
#define VKRENDERER_HANDLE_VECTOR_H

#include <cstdint>
#include <vector>

#include "../Handle.h"
#include "HandleVectorItem.h"

using std::vector;


template<typename T, typename HandleSize = uint16_t>
class HandleVector final {
    using HandleType = Handle<T, HandleSize>;
private:
    vector<HandleVectorItem<T>>     data            = {};
    vector<HandleSize>              dataToHandle    = {};
    vector<HandleSize>              handleToData    = {};

    HandleSize nextFreeHandleIndex = HandleType::invalidMaxValue;
public:
    HandleVector() = default;
    ~HandleVector();

    HandleVector(const HandleVector&)       = default;
    HandleVector(HandleVector&&) noexcept   = default;

    HandleVector& operator=(const HandleVector&)        = default;
    HandleVector& operator=(HandleVector&&) noexcept    = default;
public:
    T& operator[] (HandleType index);
public:
    template<typename ...Args>
    HandleType getItem(Args... args);

    void returnItem(HandleType& handle);


};

template<typename T, typename HandleSize>
HandleVector<T, HandleSize>::~HandleVector() {

    for (HandleVectorItem<T> item : data) {
        item.cleanUp();
    }
}

template<typename T, typename HandleSize>
T& HandleVector<T, HandleSize>::operator[](HandleType index) {
    return data[handleToData[static_cast<HandleSize>(index)]].get();
}

template<typename T, typename HandleSize>
template<typename... Args>
typename HandleVector<T, HandleSize>::HandleType HandleVector<T, HandleSize>::getItem(Args... args) {

    if(nextFreeHandleIndex == HandleType::invalidMaxValue) {
        //There are no gaps in the handle set, so we get a new handle and a new data item.

        //New data in the data vector
        data.emplace_back(std::forward<Args>(args)...);

        //Push a new handle pointing to the last index of data
        handleToData.emplace_back(data.size() - 1);

        //Push a new index pointing to the last index of handle
        dataToHandle.emplace_back(handleToData.size() - 1);

        //Return the index of the last handle
        return HandleType(dataToHandle.back());

    } else {
        //There is a handle we can recycle.

        //New data in the data vector
        data.emplace_back(std::forward<Args>(args)...);

        //Store copy, and set the nextFreeHandleIndex to the index pointed to by the handle in the handleToData vector.
        HandleSize nextFree = nextFreeHandleIndex;
        nextFreeHandleIndex = handleToData[nextFreeHandleIndex];

        //Set the handle to point to the last element of data.
        handleToData[nextFree] = data.size() - 1;

        //Put daataTohandle in the right place
        dataToHandle.emplace_back(nextFree);

        return HandleType(nextFree);
    }
}

template<typename T, typename HandleSize>
void HandleVector<T, HandleSize>::returnItem(HandleType &handle) {

    auto indexInHandle = static_cast<HandleSize>(handle);

    if(handleToData[indexInHandle] == data.size() - 1) {
        //We need to remove the last element

        //Pop back the element from data and it's ref to the handle.
        data.pop_back();
        dataToHandle.pop_back();

        if (indexInHandle == handleToData.size() - 1) {
            handleToData.pop_back();
        } else {
            handleToData[indexInHandle] = nextFreeHandleIndex;
            nextFreeHandleIndex = indexInHandle;
        }

    } else {
        //We need to remove an inner element.

        //Get last element of data' s index.
        HandleSize lastElementIndex = data.size() - 1;

        //Use it to look up what the last element's associated external handle is.
        HandleSize lastElementHandle = dataToHandle[lastElementIndex];

        //Get the item we need to remove.
        T& item = data[handleToData[indexInHandle]].get();

        //Get the last item. This one will be put into the slot of the removed item.
        T& lastItem = data[handleToData[lastElementHandle]].get();

        //Move the last item into the deleted item.
        item = std::move(lastItem);

        //Pop the back of data and dataToHandle
        data.pop_back();
        dataToHandle.pop_back();

        //Update handle to point to new location
        handleToData[lastElementHandle] = handleToData[indexInHandle];
        dataToHandle[lastElementIndex] = lastElementHandle;

        nextFreeHandleIndex = indexInHandle;


    }
}


#endif //VKRENDERER_HANDLE_VECTOR_H
