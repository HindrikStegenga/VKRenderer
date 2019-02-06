//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#ifndef VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
#define VKRENDERER_DEVICEMEMORYSUBSYSTEM_H

#include <cstdint>
#include "../../../CommonInclude.h"
#include "../Platform/VulkanPlatform.h"
#include "DeviceMemoryManager.h"

class DeviceMemorySubsystem final {
private:
    DeviceInfo                      deviceInfo      = {};
    DeviceMemoryManager             memoryManager   = DeviceMemoryManager();
public:
    DeviceMemorySubsystem() = default;
    explicit DeviceMemorySubsystem(DeviceInfo deviceInfo);
    ~DeviceMemorySubsystem() = default;

    DeviceMemorySubsystem(const DeviceMemorySubsystem&)     = delete;
    DeviceMemorySubsystem(DeviceMemorySubsystem&&) noexcept = default;

    DeviceMemorySubsystem& operator=(const DeviceMemorySubsystem&)     = delete;
    DeviceMemorySubsystem& operator=(DeviceMemorySubsystem&&) noexcept = default;
public:






};


#endif //VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
