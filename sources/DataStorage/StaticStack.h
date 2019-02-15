//
// Created by Hindrik  Stegenga on 21/05/2018.
//

#ifndef VKRENDERER_STATICK_STACK_H
#define VKRENDERER_STATICK_STACK_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <cstring>

//TODO: Modify so it doesn' t require default inizitalizables anymore.
template<typename T, size_t container_size>
class StaticStack final {
private:
    T data[container_size];
    size_t usedCount        = 0;
public:
    StaticStack()  = default;
    ~StaticStack() = default;

    StaticStack(const StaticStack&)     = default;
    StaticStack(StaticStack&&) noexcept = default;

    StaticStack& operator=(const StaticStack&)      = default;
    StaticStack& operator=(StaticStack&&) noexcept  = default;

    T& operator[] (size_t index);
    const T& operator[] (size_t index) const;

    size_t capacity() const;
    size_t size() const;

    void push(const T& item);
    void emplace(T&& item);

    template<typename ...Args>
    void push(Args... args);

    template<typename ...Args>
    void emplace(Args... args);

    bool empty() const;

    void pop();
    T&   top();
    const T& top() const;

    T* begin();
    T* end();

    T const* const begin() const;
    T const* const end() const;

};

template<typename T, size_t container_size>
T &StaticStack<T, container_size>::operator[](const size_t index) {
    return data[index];
}

template<typename T, size_t container_size>
const T& StaticStack<T, container_size>::operator[](size_t index) const {
    return data[index];
}

template<typename T, size_t container_size>
size_t StaticStack<T, container_size>::capacity() const {
    return container_size;
}

template<typename T, size_t container_size>
size_t StaticStack<T, container_size>::size() const {
    return usedCount;
}

template<typename T, size_t container_size>
void StaticStack<T, container_size>::push(const T &item) {

    if(usedCount >= container_size)
        throw std::runtime_error("Out of bounds!");

    data[usedCount] = item;
    usedCount++;
}

template<typename T, size_t container_size>
void StaticStack<T, container_size>::emplace(T &&item) {

    if(usedCount >= container_size)
        throw std::runtime_error("Out of bounds!");

    data[usedCount] = std::move(item);
    usedCount++;
}

template<typename T, size_t container_size>
template<typename... Args>
void StaticStack<T, container_size>::push(Args... args) {
    if(usedCount >= container_size)
        throw std::runtime_error("Out of bounds!");

    new (data[usedCount]) T(std::forward<Args>(args)...);
    usedCount++;
}

template<typename T, size_t container_size>
template<typename... Args>
void StaticStack<T, container_size>::emplace(Args... args) {
    if(usedCount >= container_size)
        throw std::runtime_error("Out of bounds!");

    void* place = &data[usedCount];
    new (place) T(std::forward<Args>(args)...);
    usedCount++;
}

template<typename T, size_t container_size>
void StaticStack<T, container_size>::pop() {

    if(usedCount == 0)
        return;

    memset(data[usedCount], 0, sizeof(T));
    usedCount--;
}

template<typename T, size_t container_size>
bool StaticStack<T, container_size>::empty() const {
    return usedCount == 0;
}

template<typename T, size_t container_size>
T& StaticStack<T, container_size>::top() {
    return data[usedCount-1];
}

template<typename T, size_t container_size>
const T &StaticStack<T, container_size>::top() const {
    return data[usedCount-1];
}

template<typename T, size_t container_size>
T const *const StaticStack<T, container_size>::begin() const {

    return usedCount > 0 ? &data[0] : nullptr;
}

template<typename T, size_t container_size>
T* StaticStack<T, container_size>::begin() {

    return usedCount > 0 ? &data[0] : nullptr;
}

template<typename T, size_t container_size>
T const *const StaticStack<T, container_size>::end() const {

    return usedCount > 0 ? &data[usedCount] : nullptr;
}

template<typename T, size_t container_size>
T* StaticStack<T, container_size>::end() {

    return usedCount > 0 ? &data[usedCount] : nullptr;
}

#endif //VKRENDERER_STATICK_STACK_H
