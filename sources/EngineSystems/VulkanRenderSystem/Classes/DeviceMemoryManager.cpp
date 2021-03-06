//
// Created by Hindrik  Stegenga on 21/05/2018.
//

#include "DeviceMemoryManager.h"
#include "../Utilities/UtilityFunctions.h"

DeviceMemoryManager::DeviceMemoryManager(DeviceInfo& deviceInfo) : device(deviceInfo.logical), physicalDevice(deviceInfo.physical) {

    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(physicalDevice, &properties);
    deviceType = properties.deviceType;

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
        for(uint32_t idx = 0; idx < heap.memoryTypeCount; ++idx)        
        {
            bool isValid = true;
            VkMemoryType type = heap.memoryTypes[idx];                  
            for(auto& func : funcs)
            {                                                           
                if(!func(type))                                         
                {                                                       
                    isValid = false;                                    
                    break;                                              
                }                                                       
                                                                        
            }
            if(!isValid) {
                continue;
            }
            else {
                //Check if it already exists in the target set
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
            }                                                           
        }
    }
}


void DeviceMemoryManager::pickGenericBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps, const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{

    checkAndAssignMemProps(deviceLocalHeaps, genericBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isNotHostCoherent, isNotHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, genericBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isNotHostCoherent, isHostVisible    });

    //TODO: Implement proper device type memory selection
    if (deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
        checkAndAssignMemProps(deviceLocalHeaps, genericBufferMemoryTypes,
                               {isDeviceLocal, isHostCached, isHostCoherent, isHostVisible});
    }
    /*
    checkAndAssignMemProps(deviceLocalHeaps, genericBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isHostCoherent,    isNotHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, genericBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isHostCoherent,    isHostVisible    });
    */

    assert(!genericBufferMemoryTypes.empty());
    std::stringstream stream;
    stream << "Assigned the following memory types to be used as generic buffer memory: " << std::endl;
    for(size_t i = 0; i < genericBufferMemoryTypes.size(); ++i)
    {
        auto type = genericBufferMemoryTypes[i];
        stream << "Priority: " + std::to_string(i) << std::endl;
        stream << type;
    }
    Logger::log(stream.str());
}

void DeviceMemoryManager::pickStagingBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps,
                                                       const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{
    checkAndAssignMemProps(deviceLocalHeaps, stagingBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isNotHostCoherent, isHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, stagingBufferMemoryTypes, { isDeviceLocal, isHostCached,    isNotHostCoherent, isHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, stagingBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isHostCoherent,    isHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, stagingBufferMemoryTypes, { isDeviceLocal, isHostCached,    isHostCoherent,    isHostVisible });

    checkAndAssignMemProps(hostLocalHeaps, stagingBufferMemoryTypes, { isHostCached,    isNotHostCoherent, isHostVisible });
    checkAndAssignMemProps(hostLocalHeaps, stagingBufferMemoryTypes, { isHostCached,    isHostCoherent,    isHostVisible });
    checkAndAssignMemProps(hostLocalHeaps, stagingBufferMemoryTypes, { isNotHostCached, isHostCoherent,    isHostVisible });

    assert(!stagingBufferMemoryTypes.empty());
    std::stringstream stream;
    stream << "Assigned the following memory types to be used as staging buffer memory: " << std::endl;
    for(size_t i = 0; i < stagingBufferMemoryTypes.size(); ++i)
    {
        auto type = stagingBufferMemoryTypes[i];
        stream << "Priority: " + std::to_string(i) << std::endl;
        stream << type;
    }
    Logger::log(stream.str());

}

void DeviceMemoryManager::pickLowFrequencyUBOBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps,
                                                               const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{
    checkAndAssignMemProps(deviceLocalHeaps, lowFrequencyUBOBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isNotHostCoherent, isNotHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, lowFrequencyUBOBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isNotHostCoherent, isHostVisible    });

    //TODO: Implement proper device type memory selection
    if (deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
        checkAndAssignMemProps(deviceLocalHeaps, lowFrequencyUBOBufferMemoryTypes,
                               {isDeviceLocal, isHostCached, isHostCoherent, isHostVisible});
    }

    assert(!lowFrequencyUBOBufferMemoryTypes.empty());
    std::stringstream stream;
    stream << "Assigned the following memory types to be used as low frequency UBO buffer memory: " << std::endl;

    for(size_t i = 0; i < lowFrequencyUBOBufferMemoryTypes.size(); ++i)
    {
        auto type = lowFrequencyUBOBufferMemoryTypes[i];
        stream << "Priority: " + std::to_string(i) << std::endl;
        stream << type;
    }
    Logger::log(stream.str());
}

void DeviceMemoryManager::pickHighFrequencyUBOBufferMemoryTypes(const DeviceMemoryManager::MemHeapSet &deviceLocalHeaps,
                                                                const DeviceMemoryManager::MemHeapSet &hostLocalHeaps)
{
    checkAndAssignMemProps(hostLocalHeaps, highFrequencyUBOBufferMemoryTypes, { isHostCached,    isNotHostCoherent, isHostVisible });
    checkAndAssignMemProps(hostLocalHeaps, highFrequencyUBOBufferMemoryTypes, { isHostCached,    isHostCoherent,    isHostVisible });
    checkAndAssignMemProps(hostLocalHeaps, highFrequencyUBOBufferMemoryTypes, { isNotHostCached, isHostCoherent,    isHostVisible });

    checkAndAssignMemProps(deviceLocalHeaps, highFrequencyUBOBufferMemoryTypes, { isDeviceLocal, isHostCached,    isNotHostCoherent, isHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, highFrequencyUBOBufferMemoryTypes, { isDeviceLocal, isHostCached,    isHostCoherent,    isHostVisible });
    checkAndAssignMemProps(deviceLocalHeaps, highFrequencyUBOBufferMemoryTypes, { isDeviceLocal, isNotHostCached, isHostCoherent,    isHostVisible });

    assert(!highFrequencyUBOBufferMemoryTypes.empty());
    std::stringstream stream;
    stream << "Assigned the following memory types to be used as high frequency UBO buffer memory: " << std::endl;

    for(size_t i = 0; i < highFrequencyUBOBufferMemoryTypes.size(); ++i)
    {
        auto type = highFrequencyUBOBufferMemoryTypes[i];
        stream << "Priority: " + std::to_string(i) << std::endl;
        stream << type;
    }
    Logger::log(stream.str());
}

vk_MemoryAllocation DeviceMemoryManager::allocateFromMemTypeSet(VkDeviceSize size, const DeviceMemoryManager::MemTypeSet &set) {

    VkMemoryAllocateInfo allocateInfo   = {};
    allocateInfo.sType                  = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.pNext                  = nullptr;
    allocateInfo.allocationSize         = size;

    for (auto memType : set) {
        vk_MemoryHeapUsageTracker& tracker = memoryHeapUsageTrackers[memType.memoryType.heapIndex];

        if(size >= tracker.memoryHeap.size)
            continue;

        if(size >= tracker.memoryHeap.size - tracker.usedHeapSize)
            continue;

        allocateInfo.memoryTypeIndex = memType.memoryTypeIndex;

        VkDeviceMemory memory = VK_NULL_HANDLE;
        VkResult result = vkAllocateMemory(device, &allocateInfo, nullptr, &memory);
        handleResult(result, "Could not allocate buffer!");

        Logger::success("Allocated memory buffer on heap " + std::to_string(memType.memoryType.heapIndex) + " with type " + std::to_string(memType.memoryTypeIndex) + " of " + std::to_string(size) + " bytes.");

        vk_MemoryAllocation allocation = {};
        allocation.memoryType       = memType;
        allocation.allocation       = memory;
        allocation.size             = size;

        tracker.usedHeapSize += size;

        return allocation;
    }

    return vk_MemoryAllocation{};
}

void DeviceMemoryManager::freeMemoryAllocation(vk_MemoryAllocation allocation) {

    for(auto& tracker : memoryHeapUsageTrackers)
    {
        if(allocation.memoryType.memoryType.heapIndex == tracker.heapIndex)
        {
            vkFreeMemory(device, allocation.allocation, nullptr);
            tracker.usedHeapSize -= allocation.size;

            Logger::log("Freed memory from heap " + std::to_string(tracker.heapIndex) + " with type " + std::to_string(allocation.memoryType.memoryTypeIndex) + " of " + std::to_string(allocation.size) + " bytes.");
            return;
        }
    }

    Logger::failure("Failure location memory heap. This should never happen!");
}

vk_MemoryAllocation DeviceMemoryManager::allocateGenericMemory(VkDeviceSize size) {
    return allocateFromMemTypeSet(size, genericBufferMemoryTypes);
}

vk_MemoryAllocation DeviceMemoryManager::allocateStagingMemory(VkDeviceSize size) {
    return allocateFromMemTypeSet(size, stagingBufferMemoryTypes);
}

vk_MemoryAllocation DeviceMemoryManager::allocateLowFrequencyUBOMemory(VkDeviceSize size) {
    return allocateFromMemTypeSet(size, lowFrequencyUBOBufferMemoryTypes);
}

vk_MemoryAllocation DeviceMemoryManager::allocateHighFrequencyUBOMemory(VkDeviceSize size) {
    return allocateFromMemTypeSet(size, highFrequencyUBOBufferMemoryTypes);
}