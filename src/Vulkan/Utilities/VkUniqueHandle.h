//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VKUNIQUEHANDLE_H
#define VKRENDERER_VKUNIQUEHANDLE_H

#include <functional>
#include <vulkan/vulkan.h>

using std::function;

template<typename T>
class VkUniqueHandle final {
private:
    T object = VK_NULL_HANDLE;
    function<void(T)> deleteFunc;
public:
    VkUniqueHandle() = default;
    explicit VkUniqueHandle(function<void(T, VkAllocationCallbacks*)> deleteFunc);
    VkUniqueHandle(VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks*)> deleteFunc);
    VkUniqueHandle(VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks*)> deleteFunc);

    VkUniqueHandle(T handle, function<void(T, VkAllocationCallbacks*)> deleteFunc);
    VkUniqueHandle(T handle, VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks*)> deleteFunc);
    VkUniqueHandle(T handle, VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks*)> deleteFunc);

    ~VkUniqueHandle();

    VkUniqueHandle(VkUniqueHandle&& rhs) noexcept;
    VkUniqueHandle& operator= (VkUniqueHandle&& rhs) noexcept;

    VkUniqueHandle(const VkUniqueHandle&) = delete;
    VkUniqueHandle& operator= (const VkUniqueHandle&) = delete;
private:
    auto cleanUp() -> void;
public:
    auto release()                      -> T;
    auto get()              const       -> T;
    auto reset(T handle)                -> void;
    auto reset()                        -> T*;

    auto reset(function<void(T, VkAllocationCallbacks*)> deleteFunc)                                  -> T*;
    auto reset(VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks*)> deleteFunc) -> T*;
    auto reset(VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks*)> deleteFunc)       -> T*;


    auto swap(VkUniqueHandle& rhs)      -> void;

    auto reset(T handle, function<void(T, VkAllocationCallbacks*)> deleteFunc)                                  -> void;
    auto reset(T handle, VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks*)> deleteFunc) -> void;
    auto reset(T handle, VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks*)> deleteFunc)       -> void;

    auto resetDeleter(function<void(T, VkAllocationCallbacks *)> deleteFunc)                                    -> void;
    auto resetDeleter(VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks *)> deleteFunc)   -> void;
    auto resetDeleter(VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks *)> deleteFunc)         -> void;

    auto getDeleter() const -> function<void(T)>;

    explicit operator bool() const;
    const T* operator &() const;
    explicit operator T() const;

};

template<typename T>
VkUniqueHandle<T>::~VkUniqueHandle() {
    cleanUp();
}

template<typename T>
VkUniqueHandle<T>::VkUniqueHandle(VkUniqueHandle&& rhs) noexcept {
    cleanUp();
    object      = std::move(rhs.object);
    deleteFunc  = rhs.deleteFunc;

    rhs.object  = VK_NULL_HANDLE;
    rhs.deleteFunc = nullptr;
}

template<typename T>
VkUniqueHandle<T>& VkUniqueHandle<T>::operator=(VkUniqueHandle&& rhs) noexcept {
    cleanUp();

    object      = std::move(rhs.object);
    deleteFunc  = rhs.deleteFunc;

    rhs.object  = VK_NULL_HANDLE;
    rhs.deleteFunc = nullptr;

    return *this;
}

template<typename T>
auto VkUniqueHandle<T>::cleanUp() -> void {

    if (object != VK_NULL_HANDLE){
        if (deleteFunc != nullptr) {
            deleteFunc(object);
        } else {
            Logger::warn("Could not deallocate VulkanHandle because of invalid delete function!");
        }
    }
    object = VK_NULL_HANDLE;
}

template<typename T>
VkUniqueHandle<T>::VkUniqueHandle(function<void(T, VkAllocationCallbacks *)> deleteFunc) {
    this->deleteFunc = [=](T obj){
        deleteFunc(obj, nullptr);
    };
};

template<typename T>
VkUniqueHandle<T>::VkUniqueHandle(VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks *)> deleteFunc) {
    this->deleteFunc = [=](T obj){
        deleteFunc(instance, obj, nullptr);
    };
}

template<typename T>
VkUniqueHandle<T>::VkUniqueHandle(VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks *)> deleteFunc) {
    this->deleteFunc = [=](T obj){
        deleteFunc(device, obj, nullptr);
    };
}

template<typename T>
VkUniqueHandle<T>::VkUniqueHandle(T handle, function<void(T, VkAllocationCallbacks *)> deleteFunc) {
    this->deleteFunc = [=](T obj){
        deleteFunc(obj, nullptr);
    };
    object = handle;
};

template<typename T>
VkUniqueHandle<T>::VkUniqueHandle(T handle, VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks *)> deleteFunc) {
    this->deleteFunc = [=](T obj){
        deleteFunc(instance, obj, nullptr);
    };
    object = handle;
}

template<typename T>
VkUniqueHandle<T>::VkUniqueHandle(T handle, VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks *)> deleteFunc) {
    this->deleteFunc = [=](T obj){
        deleteFunc(device, obj, nullptr);
    };
    object = handle;
}

template<typename T>
auto VkUniqueHandle<T>::release() -> T {
    T handle = object;
    object = VK_NULL_HANDLE;
    return handle;
}

template<typename T>
auto VkUniqueHandle<T>::get() const -> T {
    return object;
}

template<typename T>
auto VkUniqueHandle<T>::reset(T handle) -> void {
    cleanUp();
    object = handle;
}

template<typename T>
auto VkUniqueHandle<T>::getDeleter() const -> function<void(T)> {
    return deleteFunc;
}

template<typename T>
auto VkUniqueHandle<T>::resetDeleter(function<void(T, VkAllocationCallbacks *)> deleteFunc) -> void {
    this->deleteFunc = [=](T obj){
        deleteFunc(obj, nullptr);
    };
}

template<typename T>
auto VkUniqueHandle<T>::resetDeleter(VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks *)> deleteFunc) -> void {
    this->deleteFunc = [=](T obj){
        deleteFunc(instance, obj, nullptr);
    };
}

template<typename T>
auto VkUniqueHandle<T>::resetDeleter(VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks *)> deleteFunc) -> void {
    cleanUp();
    this->deleteFunc = [=](T obj){
        deleteFunc(device, obj, nullptr);
    };
}

template<typename T>
auto VkUniqueHandle<T>::reset(T handle, function<void(T, VkAllocationCallbacks *)> deleteFunc) -> void {
    cleanUp();
    object = handle;
    this->deleteFunc = [=](T obj){
        deleteFunc(obj, nullptr);
    };
}

template<typename T>
auto VkUniqueHandle<T>::reset(T handle, VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks *)> deleteFunc) -> void {
    cleanUp();
    object = handle;
    this->deleteFunc = [=](T obj){
        deleteFunc(instance, obj, nullptr);
    };
}

template<typename T>
auto VkUniqueHandle<T>::reset(T handle, VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks *)> deleteFunc) -> void {
    cleanUp();
    object = handle;
    this->deleteFunc = [=](T obj){
        deleteFunc(device, obj, nullptr);
    };
}

template<typename T>
auto VkUniqueHandle<T>::reset(function<void(T, VkAllocationCallbacks *)> deleteFunc) -> T* {
    cleanUp();
    this->deleteFunc = [=](T obj){
        deleteFunc(obj, nullptr);
    };
    return &object;
}

template<typename T>
auto VkUniqueHandle<T>::reset(VkInstance instance, function<void(VkInstance, T, VkAllocationCallbacks *)> deleteFunc) -> T* {
    cleanUp();
    this->deleteFunc = [=](T obj){
        deleteFunc(instance, obj, nullptr);
    };
    return &object;
}

template<typename T>
auto VkUniqueHandle<T>::reset(VkDevice device, function<void(VkDevice, T, VkAllocationCallbacks *)> deleteFunc) -> T* {
    cleanUp();
    this->deleteFunc = [=](T obj){
        deleteFunc(device, obj, nullptr);
    };
    return &object;
}

template<typename T>
auto VkUniqueHandle<T>::swap(VkUniqueHandle& rhs) -> void {
    auto del = deleteFunc;
    auto obj = object;

    deleteFunc  = rhs.deleteFunc;
    object      = rhs.object;

    rhs.deleteFunc  = del;
    rhs.object      = obj;
}

template<typename T>
VkUniqueHandle<T>::operator bool() const -> bool {
    return object != VK_NULL_HANDLE;
}

template<typename T>
auto VkUniqueHandle<T>::reset() -> T* {
    cleanUp();
    return &object;
}

template<typename T>
const T* VkUniqueHandle<T>::operator&() const {
    return &object;
}

template<typename T>
VkUniqueHandle<T>::operator T() const {
    return object;
}


#endif //VKRENDERER_VKUNIQUEHANDLE_H
