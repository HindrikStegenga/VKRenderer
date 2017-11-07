//
// Created by Hindrik Stegenga on 6-11-17.
//

#ifndef VKRENDERER_PHYSICALDEVICE_H
#define VKRENDERER_PHYSICALDEVICE_H

#include "../Platform/VulkanPlatform.h"

struct PhysicalDevice final
{
public:
    explicit PhysicalDevice(VkPhysicalDevice physicalDevice);
    ~PhysicalDevice() = default;

    PhysicalDevice(const PhysicalDevice&)               = default;

    PhysicalDevice& operator=(const PhysicalDevice&)    = default;
public:
    VkPhysicalDevice                    physicalDevice;
    VkPhysicalDeviceProperties          properties;
    VkPhysicalDeviceFeatures            features;
    vector<VkExtensionProperties>       extensionProperties;
    VkPhysicalDeviceMemoryProperties    memoryProperties;
public:
    bool isSuitable(const vector<const char*>& extensionNames, const VkPhysicalDeviceFeatures& requiredFeatures);
private:
    static bool meetsRequiredPhysicalDeviceFeatures(const VkPhysicalDeviceFeatures& features, const VkPhysicalDeviceFeatures& requirements);
    static pair<bool, string> meetsRequiredExtensions(const vector<VkExtensionProperties> &extensions, const vector<const char *>& requirements);
};


#endif //VKRENDERER_PHYSICALDEVICE_H
