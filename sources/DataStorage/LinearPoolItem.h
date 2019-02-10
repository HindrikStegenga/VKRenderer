//
// Created by hindrik on 10-2-19.
//

#ifndef VKRENDERER_LINEARPOOLITEM_H
#define VKRENDERER_LINEARPOOLITEM_H

#include <utility>

template<typename T>
class LinearPoolItem final
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
    LinearPoolItem() = default;
    ~LinearPoolItem();

    LinearPoolItem(const LinearPoolItem&)             = delete;
    LinearPoolItem& operator=(const LinearPoolItem&)  = delete;

    LinearPoolItem(LinearPoolItem&&)                  = delete;
    LinearPoolItem& operator=(LinearPoolItem&&)       = delete;

    void cleanUp();

    template<typename... Args>
    void reset(Args&&... arguments);
};

template<typename T>
inline LinearPoolItem<T>::~LinearPoolItem()
{
    cleanUp();
}

template<typename T>
inline void LinearPoolItem<T>::cleanUp()
{
    data.object.~T();
}

template<typename T>
template<typename... Args>
void LinearPoolItem<T>::reset(Args&&... arguments)
{
    void* tVoid = &(data.object);
    new (tVoid) T(std::forward<Args>(arguments)...);
}

#endif //VKRENDERER_LINEARPOOLITEM_H
