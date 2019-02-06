//
// Created by Hindrik  Stegenga on 21/05/2018.
//

#ifndef VKRENDERER_DEVICEMEMORY_MANAGER_H
#define VKRENDERER_DEVICEMEMORY_MANAGER_H

#include "../../../CommonInclude.h"
#include "../Platform/VulkanPlatform.h"
#include "../../../DataStorage/StaticStack.h"
#include "../Utilities/VkEnums.h"


class DeviceMemoryManager final {
private:
    typedef StaticStack<vk_MemoryHeap, VK_MAX_MEMORY_HEAPS> MemHeapSet;
    typedef StaticStack<vk_MemoryType, VK_MAX_MEMORY_TYPES> MemTypeSet;
    typedef bool (*HasMemoryPropertyFunc)(VkMemoryType);
private:
    VkDevice                device          = VK_NULL_HANDLE;
    VkPhysicalDevice        physicalDevice  = VK_NULL_HANDLE;
    VkPhysicalDeviceType    deviceType      = VK_PHYSICAL_DEVICE_TYPE_BEGIN_RANGE;

    StaticStack<vk_MemoryHeapUsageTracker, VK_MAX_MEMORY_HEAPS> memoryHeapUsageTrackers = {};

    MemTypeSet genericBufferMemoryTypes             = {};
    MemTypeSet stagingBufferMemoryTypes             = {};
    MemTypeSet lowFrequencyUBOBufferMemoryTypes     = {};
    MemTypeSet highFrequencyUBOBufferMemoryTypes    = {};
public:
    DeviceMemoryManager() = default;
    explicit DeviceMemoryManager(DeviceInfo& deviceInfo);

    DeviceMemoryManager(const DeviceMemoryManager&)     = delete;
    DeviceMemoryManager(DeviceMemoryManager&&) noexcept = default;

    DeviceMemoryManager& operator=(const DeviceMemoryManager&)      = delete;
    DeviceMemoryManager& operator=(DeviceMemoryManager&&) noexcept  = default;

public:
    
    vk_MemoryAllocation allocateGenericMemory           (VkDeviceSize size);
    vk_MemoryAllocation allocateStagingMemory           (VkDeviceSize size);
    vk_MemoryAllocation allocateLowFrequencyUBOMemory   (VkDeviceSize size);
    vk_MemoryAllocation allocateHighFrequencyUBOMemory  (VkDeviceSize size);

    void freeMemoryAllocation(vk_MemoryAllocation allocation);

private:
    void setupDeviceMemoryHeaps();
    void checkAndAssignMemProps(const MemHeapSet& heapSet, MemTypeSet& targetSet, vector<HasMemoryPropertyFunc> funcs);

    void pickGenericBufferMemoryTypes           (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);
    void pickStagingBufferMemoryTypes           (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);
    void pickLowFrequencyUBOBufferMemoryTypes   (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);
    void pickHighFrequencyUBOBufferMemoryTypes  (const MemHeapSet& deviceLocalHeaps, const MemHeapSet& hostLocalHeaps);

    vk_MemoryAllocation allocateFromMemTypeSet(VkDeviceSize size, const MemTypeSet& set);

private:
    static bool isHeapDeviceLocal(VkMemoryHeap memoryHeap);
    static vk_MemoryHeap getMemoryHeapMemoryTypes(uint32_t heapIndex, const VkPhysicalDeviceMemoryProperties &memoryProperties);
};


#endif //VKRENDERER_DEVICEMEMORY_MANAGER_H
