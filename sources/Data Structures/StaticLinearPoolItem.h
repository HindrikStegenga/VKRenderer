//
// Created by hindrik on 10-2-19.
//

#ifndef VKRENDERER_STATICLINEARPOOLITEM_H
#define VKRENDERER_STATICLINEARPOOLITEM_H

#include <utility>

template<typename T>
class StaticLinearPoolItem final
{
public:
    union Data
    {
    public:
        T object;
    public:
        //Implement constructor/destructor as no-op, because they NEED to be defined in case of T having a non trivial constructor
        Data() { (void)0; };
        ~Data(){ (void)0; };

        Data(const Data&)       = delete;
        Data(Data&&) noexcept   = delete;

        Data& operator=(const Data&)     = delete;
        Data& operator=(Data&&) noexcept = delete;
    };

    alignas(T) Data data;
public:
    StaticLinearPoolItem() = default;
    ~StaticLinearPoolItem();

    StaticLinearPoolItem(const StaticLinearPoolItem&)             = delete;
    StaticLinearPoolItem& operator=(const StaticLinearPoolItem&)  = delete;

    StaticLinearPoolItem(StaticLinearPoolItem&&)                  = delete;
    StaticLinearPoolItem& operator=(StaticLinearPoolItem&&)       = delete;

    void cleanUp();

    template<typename... Args>
    void reset(Args&&... arguments);
};

template<typename T>
inline StaticLinearPoolItem<T>::~StaticLinearPoolItem()
{
    cleanUp();
}

template<typename T>
inline void StaticLinearPoolItem<T>::cleanUp()
{
    data.object.~T();
}

template<typename T>
template<typename... Args>
void StaticLinearPoolItem<T>::reset(Args&&... arguments)
{
    void* tVoid = &(data.object);
    new (tVoid) T(std::forward<Args>(arguments)...);
}

#endif //VKRENDERER_HANDLE_VECTOR_ITEM_H
