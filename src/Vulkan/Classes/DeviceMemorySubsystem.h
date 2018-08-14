//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#ifndef VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
#define VKRENDERER_DEVICEMEMORYSUBSYSTEM_H

#include <cstdint>
#include "../../CommonInclude.h"
#include "../Platform/VulkanPlatform.h"
#include "DeviceMemoryManager.h"
#include "../../DataStorage/StaticReusablePool.h"

DECLARE_HANDLE_16(uint32_t)

class DeviceMemorySubsystem final {
private:
    DeviceInfo                      deviceInfo      = {};
    DeviceMemoryManager             memoryManager   = DeviceMemoryManager();
    StaticReusablePool<uint32_t>    pool = {};
public:
    DeviceMemorySubsystem(){

        uint32_tHandle16 handle = pool.getNewItem();

    };
    explicit DeviceMemorySubsystem(DeviceInfo deviceInfo);
    ~DeviceMemorySubsystem() = default;

    DeviceMemorySubsystem(const DeviceMemorySubsystem&)     = delete;
    DeviceMemorySubsystem(DeviceMemorySubsystem&&) noexcept = default;

    DeviceMemorySubsystem& operator=(const DeviceMemorySubsystem&)     = delete;
    DeviceMemorySubsystem& operator=(DeviceMemorySubsystem&&) noexcept = default;
public:






};


#endif //VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
