//
// Created by Hindrik  Stegenga on 30/05/2018.
//

#include "DeviceMemorySubsystem.h"

DeviceMemorySubsystem::DeviceMemorySubsystem(DeviceInfo deviceInfo) : deviceInfo(deviceInfo), memoryManager(deviceInfo)
{
    //vk_MemoryAllocation allocation = memoryManager.allocateStagingMemory(1024 * 1024 * 1024);
    //memoryManager.freeMemoryAllocation(allocation);
}
