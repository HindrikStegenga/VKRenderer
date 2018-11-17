//
// Created by Hindrik Stegenga on 30-10-17.
//

#ifndef VKRENDERER_NULLABLE_H
#define VKRENDERER_NULLABLE_H

#include <utility>

template<typename T>
class Nullable final {
public:
    Nullable();

    explicit Nullable(const T& item);
    explicit Nullable(T&& item);
    template<typename ...Args>
    explicit Nullable(Args&&... args);


    ~Nullable();

    Nullable(const Nullable& rhs);
    Nullable(Nullable&& rhs) noexcept;

    Nullable& operator=(const Nullable& rhs);
    Nullable& operator=(Nullable&& rhs) noexcept;

    T*operator->();

    inline const T& get() const;
    inline T& get();

    inline T* getPointer();
    inline T const * const getPointer() const;

    bool isSet() const;

    void set();
    void set(T &&object);
    void set(const T &object);

    template<typename ...Args>
    void set(Args&&... args);


    explicit operator bool() const;
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
Nullable<T>::Nullable(const T &item) : data() {
    set(item);
}

template<typename T>
Nullable<T>::Nullable(T &&item) : data(){
    set(item);
}

template<typename T>
template<typename... Args>
Nullable<T>::Nullable(Args&&... args) {
    set(std::forward<Args>(args)...);
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
template<typename... Args>
void Nullable<T>::set(Args&&... args) {
    cleanUp();
    auto t = (T*)(&data);
    *t = T(std::forward<Args>(args)...);
    isNull = false;
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
bool Nullable<T>::isSet() const {
    return !isNull;
}

template<typename T>
inline const T& Nullable<T>::get() const {
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

template<typename T>
inline T& Nullable<T>::get()
{
    return *(T*)(&data);
}

template<typename T>
T* Nullable<T>::getPointer() {
    return &data;
}

template<typename T>
T const *const Nullable<T>::getPointer() const {
    return &data;
}

template<typename T>
T *Nullable<T>::operator->() {
    return (T*)&data;
}


#endif //VKRENDERER_NULLABLE_H