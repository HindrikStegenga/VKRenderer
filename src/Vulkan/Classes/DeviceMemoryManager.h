//
// Created by Hindrik  Stegenga on 21/05/2018.
//

#ifndef VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
#define VKRENDERER_DEVICEMEMORYSUBSYSTEM_H

#include "../../CommonInclude.h"
#include "../Platform/VulkanPlatform.h"
#include "../../Utilities/StaticStack.h"


class DeviceMemoryManager final {
private:
    VkDevice            device          = VK_NULL_HANDLE;
    VkPhysicalDevice    physicalDevice  = VK_NULL_HANDLE;

    VkDeviceSize        totalDynamicReserved    = 0;
    VkDeviceSize        totalStaticReserved     = 0;

    VkDeviceSize        totalDynamicUsed        = 0;
    VkDeviceSize        totalStaticUsed         = 0;


public:
    explicit DeviceMemoryManager(DeviceInfo& deviceInfo);

    DeviceMemoryManager(const DeviceMemoryManager&) = delete;
    DeviceMemoryManager(DeviceMemoryManager&&)      = default;

    DeviceMemoryManager& operator=(const DeviceMemoryManager&)  = delete;
    DeviceMemoryManager& operator=(DeviceMemoryManager&&)       = default;

public:
    


private:
    void setupDeviceMemoryHeaps();



    static bool isHeapDeviceLocal(VkMemoryHeap memoryHeap);
    static vk_MemoryHeap getMemoryHeapMemoryTypes(uint32_t heapIndex,
                                                  const VkPhysicalDeviceMemoryProperties &memoryProperties);


};


#endif //VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
