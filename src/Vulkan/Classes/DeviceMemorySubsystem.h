//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#ifndef VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
#define VKRENDERER_DEVICEMEMORYSUBSYSTEM_H

#include "../../CommonInclude.h"
#include "../Platform/VulkanPlatform.h"
#include "DeviceMemoryManager.h"
#include "../../DataStorage/StaticReusablePool.h"

class DeviceMemorySubsystem final {
private:
    DeviceInfo deviceInfo = {};

    DeviceMemoryManager memoryManager;


    StaticReusablePool<uint32_t> pool = {};

public:
    explicit DeviceMemorySubsystem(DeviceInfo deviceInfo);
    ~DeviceMemorySubsystem() = default;

    DeviceMemorySubsystem(const DeviceMemorySubsystem&) = delete;
    DeviceMemorySubsystem(DeviceMemorySubsystem&&)      = default;

    DeviceMemorySubsystem& operator=(const DeviceMemorySubsystem&)     = delete;
    DeviceMemorySubsystem& operator=(DeviceMemorySubsystem&&) noexcept = default;
public:






};


#endif //VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
