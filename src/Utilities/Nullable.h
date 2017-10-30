//
// Created by Hindrik Stegenga on 30-10-17.
//

#ifndef VKRENDERER_NULLABLE_H
#define VKRENDERER_NULLABLE_H

#include "../Vulkan/VulkanRenderer.h"

template<typename T>
class Nullable final {
public:
    Nullable();
    ~Nullable();

    Nullable(const Nullable&)       = default;
    Nullable(Nullable&&) noexcept   = default;

    Nullable& operator=(const Nullable&)     = default;
    Nullable& operator=(Nullable&&) noexcept = default;

    const T& get() const;

    bool isSet() const;

    void set();
    void set(T &&object);
    void set(const T &object);

    explicit operator bool() const;
    const T* operator &() const;
    explicit operator T() const;

private:
    alignas(T) char data[sizeof(T)];
    bool isNull = true;
private:
    void cleanUp();
};

template<typename T>
Nullable<T>::~Nullable() {
    cleanUp();
}

template<typename T>
void Nullable<T>::cleanUp() {
    if (!isNull){
        auto t = (T*)(&data);
        t->~T();
    }
    isNull = true;
}

template<typename T>
Nullable<T>::Nullable() : data() {
}

template<typename T>
void Nullable<T>::set(const T &object) {
    cleanUp();
    auto t = (T*)(&data);
    *t = object;
    isNull = false;
}

template<typename T>
void Nullable<T>::set(T &&object) {
    cleanUp();
    auto t = (T*)(&data);
    *t = std::move(object);
    isNull = false;
}

template<typename T>
void Nullable<T>::set() {
    cleanUp();
}

template<typename T>
Nullable<T>::operator bool() const {
    return !isNull;
}

template<typename T>
Nullable<T>::operator T() const {
    return data;
}

template<typename T>
const T* Nullable<T>::operator&() const {
    return &data;
}

template<typename T>
bool Nullable<T>::isSet() const {
    return !isNull;
}

template<typename T>
const T& Nullable<T>::get() const {
    return data;
}

#endif //VKRENDERER_NULLABLE_H