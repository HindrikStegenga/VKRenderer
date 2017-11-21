//
// Created by Hindrik Stegenga on 3-11-17.
//

#ifndef VKRENDERER_VULKANPRESENTDEVICE_H
#define VKRENDERER_VULKANPRESENTDEVICE_H

#include "Platform/VulkanPlatform.h"
#include "Utilities/PhysicalDevice.h"
#include "../Utilities/Nullable.h"


struct DeviceSupportDescription {

    const vector<const char*>& extensions;
    const vector<const char*>& debugExtensions;
    const VkPhysicalDeviceFeatures& requiredFeatures;
    VkSurfaceKHR surfaceHandle  = VK_NULL_HANDLE;
};

class PresentDevice final {
public:
    PresentDevice(VkInstance instance, const map<string, string>& params, const DeviceSupportDescription& supportDescription);
    ~PresentDevice() = default;

    PresentDevice(const PresentDevice&)     = delete;
    PresentDevice(PresentDevice&&) noexcept = default;

    PresentDevice& operator=(const PresentDevice&)      = delete;
    PresentDevice& operator=(PresentDevice&&) noexcept  = default;
private:
    VKUH<VkDevice>              device = VKUH<VkDevice>(vkDestroyDevice);
    VKUH<VkSurfaceKHR>          surface = VKUH<VkSurfaceKHR>();
    Nullable<PhysicalDevice>    physicalDevice;
    vk_Queue                    presentationQueue;
    VkInstance                  instance;
private:
    pair<PhysicalDevice, vk_QueueFamily>
    selectPhysicalDevice(VkInstance instance, VkSurfaceKHR surface, const map<string, string>& params, const vector<const char*>& extensions, const VkPhysicalDeviceFeatures& requiredFeatures);
    void createLogicalDeviceAndPresentationQueue(pair<PhysicalDevice, vk_QueueFamily> deviceAndQueueFamily, const vector<const char*>& extensions, VkPhysicalDeviceFeatures features);
};


#endif //VKRENDERER_VULKANPRESENTDEVICE_H