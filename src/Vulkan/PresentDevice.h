//
// Created by Hindrik Stegenga on 3-11-17.
//

#ifndef VKRENDERER_VULKANPRESENTDEVICE_H
#define VKRENDERER_VULKANPRESENTDEVICE_H

#include "Platform/VulkanPlatform.h"


struct DeviceSupportDescription {

    const vector<const char*>& extensions;
    const vector<const char*>& debugExtensions;
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
};


#endif //VKRENDERER_VULKANPRESENTDEVICE_H