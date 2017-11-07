//
// Created by Hindrik Stegenga on 3-11-17.
//

#ifndef VKRENDERER_VULKANPRESENTDEVICE_H
#define VKRENDERER_VULKANPRESENTDEVICE_H

#include "Platform/VulkanPlatform.h"
#include "Utilities/PhysicalDevice.h"


struct DeviceSupportDescription {

    const vector<const char*>& extensions;
    const vector<const char*>& debugExtensions;
    const VkPhysicalDeviceFeatures& requiredFeatures;
};

class PresentDevice final {
public:
    PresentDevice(VkInstance instance, const map<string, string>& params, const DeviceSupportDescription& supportDescription);
    ~PresentDevice() = default;

    PresentDevice(const PresentDevice&) = delete;
    PresentDevice(PresentDevice&&)      = default;

    PresentDevice& operator=(const PresentDevice&)  = delete;
    PresentDevice& operator=(PresentDevice&&)       = default;
private:
    VKUH<VkDevice> device = VKUH<VkDevice>(vkDestroyDevice);
    VkInstance instance;
private:
    PhysicalDevice selectPhysicalDevice(VkInstance instance, const map<string, string>& params, const vector<const char*>& extensions, const VkPhysicalDeviceFeatures& requiredFeatures);
};


#endif //VKRENDERER_VULKANPRESENTDEVICE_H