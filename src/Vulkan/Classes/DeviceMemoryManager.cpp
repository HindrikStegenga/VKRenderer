//
// Created by Hindrik  Stegenga on 21/05/2018.
//

#include "DeviceMemoryManager.h"
#include "../Utilities/UtilityFunctions.h"

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

        std::stringstream ss;
        ss << std::endl << memoryHeap;

        Logger::log(ss.str());

        if(isHeapDeviceLocal(properties.memoryHeaps[idx])) {
            deviceLocalHeaps.push(memoryHeap);
        } else {
            hostLocalHeaps.push(memoryHeap);
        }

        vk_MemoryHeapUsageTracker tracker = {};

        tracker.memoryHeap      = memoryHeap.memoryHeap;
        tracker.heapIndex       = idx;
        tracker.usedHeapSize    = 0;

        memoryHeapUsageTrackers.push(tracker);
    }

    assert(!(deviceLocalHeaps.empty() && hostLocalHeaps.empty()));

    //Okay, we gathered heaps and types. Now we must classify them.

    pickGenericBufferMemoryTypes          (deviceLocalHeaps, hostLocalHeaps);
    pickStagingBufferMemoryTypes          (deviceLocalHeaps, hostLocalHeaps);
    pickLowFrequencyUBOBufferMemoryTypes  (deviceLocalHeaps, hostLocalHeaps);
    pickHighFrequencyUBOBufferMemoryTypes (deviceLocalHeaps, hostLocalHeaps);
    pickFeedbackBufferMemoryTypes         (deviceLocalHeaps, hostLocalHeaps);

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

void DeviceMemoryManager::checkAndAssignMemProps(const DeviceMemoryManager::MemHeapSet &heapSet, DeviceMemoryManager::MemTypeSet &targetSet, vector<DeviceMemoryManager::HasMemoryPropertyFunc> funcs) {

    for(auto& heap : heapSet)
    {                                                                   
        bool isValid = true;                                            
        for(uint32_t idx = 0; idx < heap.memoryTypeCount; ++idx)        
        {                                                               
            VkMemoryType type = heap.memoryTypes[idx];                  
            for(auto& func : funcs)
            {                                                           
                if(!func(type))                                         
                {                                                       
                    isValid = false;                                    
                    break;                                              
                }                                                       
                                                                        
            }                                                           
            if(!isValid)                                                
                continue;                                               
            else {                                                      
                vk_MemoryType t = { heap.memoryTypeIndices[idx], type };

                bool hasFoundIdentical = false;
                for(auto& item : targetSet)
                {
                    if(item.memoryTypeIndex == t.memoryTypeIndex)
                    {
                        hasFoundIdentical = true;
                        break;
                    }
                }

                if(hasFoundIdentical)
                    continue;

                targetSet.push(t);
                break;                                                  
            }                                                           
        }                                                               
        if(isValid) break;
    }
    
}


void DeviceMemoryManager::pickGenericBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps, const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{

    checkAndAssignMemProps(deviceLocalHeaps, genericBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isNotHostCoherent });
    checkAndAssignMemProps(deviceLocalHeaps, genericBufferMemoryTypes, { isDeviceLocal, isNotHostCached });


    assert(!genericBufferMemoryTypes.empty());
    std::stringstream stream;
    stream << "Assigned the following memory types to be used as generic buffer memory: " << std::endl;
    for(auto& type : genericBufferMemoryTypes)
    {
        stream << type;
    }
    Logger::log(stream.str());
}

void DeviceMemoryManager::pickStagingBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps,
                                                       const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{

}

void DeviceMemoryManager::pickLowFrequencyUBOBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps,
                                                               const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{

}

void DeviceMemoryManager::pickHighFrequencyUBOBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps,
                                                                const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{

}

void DeviceMemoryManager::pickFeedbackBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps,
                                                        const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{

}


