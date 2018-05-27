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
    VkDeviceSize        totalDedicatedReserved  = 0;

    VkDeviceSize        totalDynamicUsed        = 0;
    VkDeviceSize        totalStaticUsed         = 0;
    VkDeviceSize        totalDedicatedReserverd = 0;

    StaticStack<vk_MemoryHeapUsageTracker, VK_MAX_MEMORY_HEAPS> memoryHeapUsageTrackers = {};

    typedef StaticStack<vk_MemoryHeap, VK_MAX_MEMORY_HEAPS> MemHeapSet;
    typedef StaticStack<vk_MemoryType, VK_MAX_MEMORY_TYPES> MemTypeSet;


    MemTypeSet genericBufferMemoryTypes             = {};
    MemTypeSet stagingBufferMemoryTypes             = {};
    MemTypeSet lowFrequencyUBOBufferMemoryTypes     = {};
    MemTypeSet highFrequencyUBOBufferMemoryTypes    = {};
    MemTypeSet feedbackBufferMemoryTypes            = {};

public:
    explicit DeviceMemoryManager(DeviceInfo& deviceInfo);

    DeviceMemoryManager(const DeviceMemoryManager&) = delete;
    DeviceMemoryManager(DeviceMemoryManager&&)      = default;

    DeviceMemoryManager& operator=(const DeviceMemoryManager&)  = delete;
    DeviceMemoryManager& operator=(DeviceMemoryManager&&)       = default;

public:
    


private:
    void setupDeviceMemoryHeaps();

    typedef bool (*HasMemoryPropertyFunc)(VkMemoryType);
    void checkAndAssignMemProps(const MemHeapSet& heapSet, MemTypeSet& targetSet, vector<HasMemoryPropertyFunc> funcs);

    void pickGenericBufferMemoryTypes           (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);
    void pickStagingBufferMemoryTypes           (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);
    void pickLowFrequencyUBOBufferMemoryTypes   (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);
    void pickHighFrequencyUBOBufferMemoryTypes  (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);
    void pickFeedbackBufferMemoryTypes          (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);


private:
    static bool isHeapDeviceLocal(VkMemoryHeap memoryHeap);
    static vk_MemoryHeap getMemoryHeapMemoryTypes(uint32_t heapIndex,
                                                  const VkPhysicalDeviceMemoryProperties &memoryProperties);




};


#endif //VKRENDERER_DEVICEMEMORYSUBSYSTEM_H
