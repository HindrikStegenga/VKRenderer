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
private:
    VKUH<VkDevice>          device              = {};
    PhysicalDevice          physicalDevice      = PhysicalDevice();
    vk_Queue                presentationQueue   = vk_Queue();
    vector<vk_Queue>        transferQueues      = {};
    VkInstance              instance            = VK_NULL_HANDLE;
    DeviceMemorySubsystem   memory              = DeviceMemorySubsystem();
public:
    PresentDevice() = default;
    PresentDevice(VkInstance instance, const map<string, string>& params, const PresentDeviceCreateInfo& createInfo);
    ~PresentDevice();

    PresentDevice(const PresentDevice&)     = delete;
    PresentDevice(PresentDevice&&) noexcept = default;

    PresentDevice& operator=(const PresentDevice&)      = delete;
    PresentDevice& operator=(PresentDevice&&) noexcept  = default;
private:
    pair<PhysicalDevice, vk_QueueFamily>
    selectPhysicalDevice(VkInstance instance, vector<VkSurfaceKHR> surfaces, const map<string, string>& params, const vector<const char*>& extensions, const VkPhysicalDeviceFeatures& requiredFeatures);
    void createLogicalDeviceAndPresentationQueue(pair<PhysicalDevice, vk_QueueFamily> deviceAndQueueFamily, const vector<const char*>& extensions, VkPhysicalDeviceFeatures features);
public:
    const PhysicalDevice& getPhysicalDevice() const;
    PresentDeviceInfo getPresentDeviceInfo() const;
    DeviceInfo getDeviceInfo() const;

};


#endif //VKRENDERER_VULKANPRESENTDEVICE_H