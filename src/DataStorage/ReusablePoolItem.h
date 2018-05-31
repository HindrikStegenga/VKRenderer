//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#ifndef VKRENDERER_REUSABLEPOOLITEM_H
#define VKRENDERER_REUSABLEPOOLITEM_H

#include <cstdint>
#include "../Utilities/Handle.h"

template<typename T, typename HandleType = Handle<T, uint16_t>>
class ReusablePoolItem final {
public:
    ReusablePoolItem()  = default;
    ~ReusablePoolItem() = default;

    ReusablePoolItem(const ReusablePoolItem&)       = delete;
    ReusablePoolItem(ReusablePoolItem&&) noexcept;

    ReusablePoolItem& operator=(const ReusablePoolItem&)        = delete;
    ReusablePoolItem& operator=(ReusablePoolItem&&) noexcept;

public:


private:
    union Data
    {
        Data()  = default;
        ~Data() = default;

        Data(const Data&) = delete;
        Data(Data&&) = delete;

        Data& operator=(const Data&) = delete;
        Data& operator=(Data&&) = delete;

        T object;
        typename HandleType::HandleSize nextIndex;

    };

    alignas(T) Data data;




};

template<typename T, typename HandleType>
ReusablePoolItem<T, HandleType>& ReusablePoolItem<T, HandleType>::operator=(ReusablePoolItem&&) noexcept {

    return *this;
}

template<typename T, typename HandleType>
ReusablePoolItem<T, HandleType>::ReusablePoolItem(ReusablePoolItem &&) noexcept {

}


#endif //VKRENDERER_REUSABLEPOOLITEM_H
