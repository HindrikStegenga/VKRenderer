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

    Nullable(const Nullable& rhs);
    Nullable(Nullable&& rhs) noexcept;

    Nullable& operator=(const Nullable& rhs);
    Nullable& operator=(Nullable&& rhs) noexcept;

    const T& get() const;

    bool isSet() const;

    void set();
    void set(T &&object);
    void set(const T &object);

    explicit operator bool() const;
    const T* operator &() const;
    explicit operator T() const;

private:
    alignas(T) char data[sizeof(T)] = {};
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
    return *(T*)(&data);
}

template<typename T>
Nullable<T>::Nullable(Nullable&& rhs) noexcept {

    isNull = rhs.isNull;

    if (!rhs.isNull){
        //move contained type...
        auto tData = (T*)&data;
        auto rData = (T*)&rhs.data;
        *tData = move(*rData);
    }
    rhs.isNull = true;
}

template<typename T>
Nullable<T>& Nullable<T>::operator=(Nullable&& rhs) noexcept {
    isNull = rhs.isNull;

    if (!rhs.isNull){
        //move contained type...
        auto tData = (T*)&data;
        auto rData = (T*)&rhs.data;
        *tData = move(*rData); //calls move ctor
    }
    rhs.isNull = true;
    return *this;
}

template<typename T>
Nullable<T>::Nullable(const Nullable& rhs) {
    isNull = rhs.isNull;
    if (!rhs.isNull){
        //copy contained type...
        auto tData = (T*)&data;
        auto rData = (T*)&rhs.data;
        *tData = *rData; //calls copy ctor
    }
}

template<typename T>
Nullable<T>& Nullable<T>::operator=(const Nullable& rhs) {
    isNull = rhs.isNull;
    if (!rhs.isNull){
        //copy contained type...
        auto tData = (T*)&data;
        auto rData = (T*)&rhs.data;
        *tData = *rData; //calls copy ctor
    }
    return *this;
}

#endif //VKRENDERER_NULLABLE_H