//
// Created by Hindrik Stegenga on 3-11-17.
//

#ifndef VKRENDERER_VULKANPRESENTDEVICE_H
#define VKRENDERER_VULKANPRESENTDEVICE_H

#include "Platform/VulkanPlatform.h"
#include "Utilities/PhysicalDevice.h"
#include "../Utilities/Nullable.h"
#include "Classes/DeviceMemorySubsystem.h"

class PresentDevice final {
public:
    PresentDevice(VkInstance instance, const map<string, string>& params, const PresentDeviceCreateInfo& createInfo);
    ~PresentDevice();

    PresentDevice(const PresentDevice&)     = delete;
    PresentDevice(PresentDevice&&) noexcept = default;

    PresentDevice& operator=(const PresentDevice&)      = delete;
    PresentDevice& operator=(PresentDevice&&) noexcept  = default;
private:
    VKUH<VkDevice>                  device = {};
    VKUH<VkSurfaceKHR>              surface = {};
    Nullable<PhysicalDevice>        physicalDevice;
    vk_Queue                        presentationQueue;
    vector<vk_Queue>                transferQueues;
    VkInstance                      instance;
    Nullable<DeviceMemorySubsystem> memory;
private:
    pair<PhysicalDevice, vk_QueueFamily>
    selectPhysicalDevice(VkInstance instance, VkSurfaceKHR surface, const map<string, string>& params, const vector<const char*>& extensions, const VkPhysicalDeviceFeatures& requiredFeatures);
    void createLogicalDeviceAndPresentationQueue(pair<PhysicalDevice, vk_QueueFamily> deviceAndQueueFamily, const vector<const char*>& extensions, VkPhysicalDeviceFeatures features);
public:
    PhysicalDevice& getPhysicalDevice();
    VkSurfaceKHR getSurface();
    PresentDeviceInfo getPresentDeviceInfo() const;
    DeviceInfo getDeviceInfo() const;

};


#endif //VKRENDERER_VULKANPRESENTDEVICE_H