//
// Created by Hindrik Stegenga on 6-11-17.
//

#ifndef VKRENDERER_PHYSICALDEVICE_H
#define VKRENDERER_PHYSICALDEVICE_H

#include "../Platform/VulkanPlatform.h"
#include "UtilityStructures.h"

struct PhysicalDevice final {
public:
    VkPhysicalDevice                    physicalDevice      = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties          properties          = {};
    VkPhysicalDeviceFeatures            features            = {};
    vector<VkExtensionProperties>       extensionProperties = {};
    VkPhysicalDeviceMemoryProperties    memoryProperties    = {};
    vector<vk_QueueFamily>              queueFamilies       = {};
public:
    PhysicalDevice() = default;
    explicit PhysicalDevice(VkPhysicalDevice physicalDevice);
    ~PhysicalDevice() = default;

    PhysicalDevice(const PhysicalDevice&)               = default;
    PhysicalDevice& operator=(const PhysicalDevice&)    = default;

    PhysicalDevice(PhysicalDevice&&) noexcept = default;
    PhysicalDevice& operator=(PhysicalDevice&&) noexcept = default;

public:
    pair<bool, vk_QueueFamily> isSuitableAndReturnPresentQueue(const vector<const char *> &extensionNames,
                                                              const VkPhysicalDeviceFeatures &requiredFeatures,
                                                               vector<VkSurfaceKHR> surfaces);
    pair<bool, vk_QueueFamily> hasTransferQueueFamily() const;
private:
    static bool                         meetsRequiredPhysicalDeviceFeatures(const VkPhysicalDeviceFeatures& features, const VkPhysicalDeviceFeatures& requirements);
    static pair<bool, string>           meetsRequiredExtensions(const vector<VkExtensionProperties> &extensions, const vector<const char *>& requirements);
    static vector<vk_QueueFamily>       getQueueFamilies(VkPhysicalDevice physicalDevice);
    static pair<bool, vk_QueueFamily>   meetsRequiredSurfaceSupport(VkPhysicalDevice physicalDevice, vector<VkSurfaceKHR> surfaces, const vector<vk_QueueFamily>& queueFamilies);
    static bool                         meetsRequiredQueueTypes(const vector<vk_QueueFamily>& queueFamilies);
    static pair<bool, vk_QueueFamily>   findFirstGraphicsComputeQueueFamily(const vector<vk_QueueFamily> &queueFamilies);
};


#endif //VKRENDERER_PHYSICALDEVICE_H
