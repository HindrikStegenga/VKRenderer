//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#ifndef VKRENDERER_REUSABLEPOOLITEM_H
#define VKRENDERER_REUSABLEPOOLITEM_H

#include <cstdint>
#include "../Utilities/Handle.h"

template<typename T, typename HandleType = Handle<T, uint16_t, std::numeric_limits<uint16_t>::max()>>
class ReusablePoolItem final {
public:
    ReusablePoolItem()  = default;
    ~ReusablePoolItem() = default;

    ReusablePoolItem(const ReusablePoolItem&)       = delete;
    ReusablePoolItem(ReusablePoolItem&&) noexcept   = default;

    ReusablePoolItem& operator=(const ReusablePoolItem&)        = delete;
    ReusablePoolItem& operator=(ReusablePoolItem&&) noexcept    = default;

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

        typename HandleType::HandleType nextIndex;

    };



};


#endif //VKRENDERER_REUSABLEPOOLITEM_H
