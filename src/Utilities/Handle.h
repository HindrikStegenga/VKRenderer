//
// Created by Hindrik  Stegenga on 27/05/2018.
//

#ifndef VKRENDERER_HANDLE_H
#define VKRENDERER_HANDLE_H

#include <limits>

template<typename T, typename HandleSizeType>
class Handle final {
private:
    HandleSizeType value;
public:
    using HandleSize = HandleSizeType;
    constexpr static int invalidMaxValue = std::numeric_limits<HandleSizeType>::max();
public:
    Handle() : value(invalidMaxValue) {}
    ~Handle() = default;

    Handle(const Handle&)       = default;
    Handle(Handle&&) noexcept   = delete;

    Handle& operator=(const Handle&)        = default;
    Handle& operator=(Handle&&) noexcept    = delete;
public:

    explicit Handle(HandleSizeType value) : value(value){}

    static Handle invalid() { return Handle(); };

    explicit operator bool() const { return value != invalidMaxValue; }

    explicit operator HandleSizeType() const { return value; }

    friend bool operator==(Handle lhs, Handle rhs) { return lhs.value == rhs.value; }
    friend bool operator!=(Handle lhs, Handle rhs) { return lhs.value != rhs.value; }
};


#define DECLARE_HANDLE_64(Type) typedef Handle<Type,uint64_t> Type##Handle64;
#define DECLARE_HANDLE_32(Type) typedef Handle<Type,uint32_t> Type##Handle32;
#define DECLARE_HANDLE_16(Type) typedef Handle<Type,uint16_t> Type##Handle16;
#define DECLARE_HANDLE_8(Type) typedef Handle<Type, uint8_t > Type##Handle8;

#endif //VKRENDERER_HANDLE_H