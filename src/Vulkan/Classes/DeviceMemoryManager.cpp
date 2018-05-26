//
// Created by Hindrik  Stegenga on 21/05/2018.
//

#include "DeviceMemoryManager.h"

DeviceMemoryManager::DeviceMemoryManager(DeviceInfo& deviceInfo) : device(deviceInfo.logical), physicalDevice(deviceInfo.physical) {

    setupDeviceMemoryHeaps();

}

void DeviceMemoryManager::setupDeviceMemoryHeaps() {

    StaticStack<vk_MemoryHeap, VK_MAX_MEMORY_HEAPS> deviceLocalHeaps;
    StaticStack<vk_MemoryHeap, VK_MAX_MEMORY_HEAPS> hostLocalHeaps;

    VkPhysicalDeviceMemoryProperties properties = {};
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &properties);

    for(uint32_t idx = 0; idx < properties.memoryHeapCount; ++idx) {

        vk_MemoryHeap memoryHeap = getMemoryHeapMemoryTypes(idx, properties);

        if(isHeapDeviceLocal(properties.memoryHeaps[idx])) {
            Logger::log("Found device local memory heap of " + std::to_string(memoryHeap.memoryHeap.size) + " bytes");
            deviceLocalHeaps.push(memoryHeap);
        } else {
            Logger::log("Found device host local memory heap of " + std::to_string(memoryHeap.memoryHeap.size) + " bytes");
            hostLocalHeaps.push(memoryHeap);
        }
    }

    //Okay, we gathered heaps and types. Now we must classify them.
    






}

bool DeviceMemoryManager::isHeapDeviceLocal(VkMemoryHeap memoryHeap) {
    return (memoryHeap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) != 0;
}

vk_MemoryHeap DeviceMemoryManager::getMemoryHeapMemoryTypes(uint32_t heapIndex, const VkPhysicalDeviceMemoryProperties& memoryProperties) {

    StaticStack<uint32_t, VK_MAX_MEMORY_TYPES> heapMemoryTypes = {};


    for (uint32_t idx = 0; idx < memoryProperties.memoryTypeCount; ++idx)
    {
        VkMemoryType memoryType = memoryProperties.memoryTypes[idx];

        if(memoryType.heapIndex != heapIndex)
            continue;

        heapMemoryTypes.push(idx);
    }

    assert(!heapMemoryTypes.empty());

    vk_MemoryHeap memoryHeap = {};

    memoryHeap.memoryHeap = memoryProperties.memoryHeaps[heapIndex];
    memoryHeap.memoryTypeCount = static_cast<uint32_t >(heapMemoryTypes.size());

    for (size_t idx = 0; idx < heapMemoryTypes.size(); ++idx)
    {
        uint32_t memoryTypeIndex = heapMemoryTypes[idx];
        VkMemoryType memoryType = memoryProperties.memoryTypes[memoryTypeIndex];

        memoryHeap.memoryTypes[idx] = memoryType;
        memoryHeap.memoryTypeIndices[idx] = memoryTypeIndex;
    }

    return memoryHeap;
}
