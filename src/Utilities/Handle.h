//
// Created by Hindrik  Stegenga on 27/05/2018.
//

#ifndef VKRENDERER_HANDLE_H
#define VKRENDERER_HANDLE_H

#include <limits>

template<typename T, typename HandleType, HandleType defaultValue>
class Handle final {
private:
    HandleType value;

public:
    Handle() : value(defaultValue) {}
    ~Handle() = default;

    Handle(const Handle&)       = default;
    Handle(Handle&&) noexcept   = delete;

    Handle& operator=(const Handle&)        = default;
    Handle& operator=(Handle&&) noexcept    = delete;
public:

    explicit Handle(HandleType value) : value(value){}

    static Handle invalid() { return Handle(); };

    explicit operator bool() const { return value != defaultValue; }

    explicit operator HandleType() const { return value; }

    friend bool operator==(Handle lhs, Handle rhs) { return lhs.value == rhs.value; }
    friend bool operator!=(Handle lhs, Handle rhs) { return lhs.value != rhs.value; }
};


#define DECLARE_HANDLE64(Type) typedef Handle<Type,uint64_t, std::numeric_limits<uint64_t>::max()> Type##Handle64;
#define DECLARE_HANDLE32(Type) typedef Handle<Type,uint32_t, std::numeric_limits<uint32_t>::max()> Type##Handle32;
#define DECLARE_HANDLE16(Type) typedef Handle<Type,uint16_t, std::numeric_limits<uint16_t>::max()> Type##Handle16;
#define DECLARE_HANDLE8(Type) typedef Handle<Type,uint8_t, std::numeric_limits<uint8_t>::max()> Type##Handle8;

#endif //VKRENDERER_HANDLE_H