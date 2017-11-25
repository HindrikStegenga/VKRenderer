//
// Created by Hindrik Stegenga on 3-11-17.
//

#include "PresentDevice.h"
#include "Utilities/UtilityFunctions.h"

PresentDevice::PresentDevice(VkInstance instance, const map<string, string>& params, const DeviceSupportDescription& supportDescription) : instance(instance)
{
    vector<const char*> usedExtensions;
    bool debug = params.at("debug") == "true";

    if (debug) {
        auto dExtensions(supportDescription.extensions);
        dExtensions.insert(std::end(dExtensions), std::begin(supportDescription.debugExtensions), std::end(supportDescription.debugExtensions));

        usedExtensions.swap(dExtensions);
    } else {
        usedExtensions = supportDescription.extensions;
    }

    auto physicalDevice = selectPhysicalDevice(instance, supportDescription.surfaceHandle, params, usedExtensions, supportDescription.requiredFeatures);

    std::stringstream ss;
    ss << std::endl << physicalDevice.first.properties;
    Logger::log("Selected device: " + ss.str());

    createLogicalDeviceAndPresentationQueue(physicalDevice, usedExtensions, supportDescription.requiredFeatures);
    this->surface.reset(supportDescription.surfaceHandle, instance, vkDestroySurfaceKHR);
}

pair<PhysicalDevice, vk_QueueFamily> PresentDevice::selectPhysicalDevice(VkInstance instance, VkSurfaceKHR surface, const map<string, string>& params, const vector<const char*>& extensions, const VkPhysicalDeviceFeatures& requiredFeatures)
{
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);

    if (physicalDeviceCount == 0) {
        Logger::failure("No physical Vulkan capable devices available!");
    }

    vector<VkPhysicalDevice> devices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, devices.data());

    vector<pair<PhysicalDevice, vk_QueueFamily>> possibleDevices;

    for (auto deviceHandle : devices) {
        PhysicalDevice device(deviceHandle);

        auto presentQueueAndSupport = device.isSuitableAndReturnPresentQueue(extensions, requiredFeatures, surface);
        if (presentQueueAndSupport.first) {
            possibleDevices.emplace_back(device, presentQueueAndSupport.second);
        }
    }
    if (possibleDevices.empty()) {
        Logger::failure("Vulkan devices were found, but none were capable enough!");
    }

    std::sort(std::begin(possibleDevices), std::end(possibleDevices), [](const pair<PhysicalDevice, vk_QueueFamily>& a, const pair<PhysicalDevice, vk_QueueFamily>& b) -> bool {
        return deviceTypePriority(a.first.properties.deviceType) > deviceTypePriority(b.first.properties.deviceType);
    });

    return possibleDevices.front();
}

void PresentDevice::createLogicalDeviceAndPresentationQueue(pair<PhysicalDevice, vk_QueueFamily> deviceAndQueueFamily, const vector<const char*>& extensions, VkPhysicalDeviceFeatures features)
{
    VkDeviceQueueCreateInfo presentQueueCreateInfo  = {};
    presentQueueCreateInfo.sType                    = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    presentQueueCreateInfo.pNext                    = nullptr;
    presentQueueCreateInfo.queueCount               = 1;
    presentQueueCreateInfo.queueFamilyIndex         = deviceAndQueueFamily.second.queueFamilyIndex;
    presentQueueCreateInfo.flags                    = {};
    float priority = 1.0;
    presentQueueCreateInfo.pQueuePriorities         = &priority;

    VkDeviceCreateInfo deviceCreateInfo     = {};
    deviceCreateInfo.sType                  = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext                  = nullptr;
    deviceCreateInfo.flags                  = {};
    deviceCreateInfo.queueCreateInfoCount   = 1;
    deviceCreateInfo.pQueueCreateInfos      = &presentQueueCreateInfo;
    deviceCreateInfo.enabledLayerCount      = 0;
    deviceCreateInfo.ppEnabledLayerNames    = nullptr;
    deviceCreateInfo.enabledExtensionCount  = static_cast<uint32_t >(extensions.size());
    deviceCreateInfo.ppEnabledExtensionNames= extensions.data();
    deviceCreateInfo.pEnabledFeatures       = &features;

    VkResult result = vkCreateDevice(deviceAndQueueFamily.first.physicalDevice, &deviceCreateInfo, nullptr, device.reset(vkDestroyDevice));
    handleResult(result, "Device creation has failed!");

    physicalDevice.set(deviceAndQueueFamily.first);
    vk_Queue present = {};
    present.queueFamily = deviceAndQueueFamily.second;
    vkGetDeviceQueue(device.get(), deviceAndQueueFamily.second.queueFamilyIndex, 0, &present.queue);
    presentationQueue = present;
    Logger::succes("Logical device creation succeeded!");
}

VkDevice PresentDevice::getDevice() {
    return device.get();
}

PhysicalDevice& PresentDevice::getPhysicalDevice() {
    return physicalDevice.getMutable();
}

VkSurfaceKHR PresentDevice::getSurface() {
    return surface.get();
}
