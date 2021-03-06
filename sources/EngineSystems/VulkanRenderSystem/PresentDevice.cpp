//
// Created by Hindrik Stegenga on 3-11-17.
//

#include "PresentDevice.h"
#include "Utilities/UtilityFunctions.h"

PresentDevice::PresentDevice(VkInstance instance, vk_GeneralSettings settings, const PresentDeviceCreateInfo& createInfo) : instance(instance)
{
    vector<const char*> usedExtensions;
    bool debug = settings.applicationSettings.debugMode;

    if (debug) {
        auto dExtensions(createInfo.extensions);
        dExtensions.insert(std::end(dExtensions), std::begin(createInfo.debugExtensions), std::end(createInfo.debugExtensions));

        usedExtensions.swap(dExtensions);
    } else {
        usedExtensions = createInfo.extensions;
    }

    auto physicalDevice = selectPhysicalDevice(instance, settings, createInfo.surfaces, usedExtensions, createInfo.requiredFeatures);

    std::stringstream ss;
    ss << std::endl << physicalDevice.first.properties;
    Logger::log("Selected device: " + ss.str());

    createLogicalDeviceAndPresentationQueue(physicalDevice, usedExtensions, createInfo.requiredFeatures);

    auto deviceInfo = getDeviceInfo();
    memory = DeviceMemorySubsystem(deviceInfo);
}

pair<PhysicalDevice, vk_QueueFamily> PresentDevice::selectPhysicalDevice(VkInstance instance, vk_GeneralSettings settings, vector<VkSurfaceKHR> surfaces, const vector<const char*>& extensions, const VkPhysicalDeviceFeatures& requiredFeatures)
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

        auto presentQueueAndSupport = device.isSuitableAndReturnPresentQueue(extensions, requiredFeatures, surfaces);
        if (presentQueueAndSupport.first) {
            possibleDevices.emplace_back(device, presentQueueAndSupport.second);
        }
    }
    if (possibleDevices.empty()) {
        Logger::failure("Vulkan devices were found, but none were capable enough!");
    }

    bool preferIGPU = settings.graphicsSettings.preferIGPU;
    std::sort(std::begin(possibleDevices), std::end(possibleDevices), [=](const pair<PhysicalDevice, vk_QueueFamily>& a, const pair<PhysicalDevice, vk_QueueFamily>& b) -> bool {
        return deviceTypePriority(a.first.properties.deviceType, preferIGPU) > deviceTypePriority(b.first.properties.deviceType, preferIGPU);
    });

    return possibleDevices.front();
}

void PresentDevice::createLogicalDeviceAndPresentationQueue(pair<PhysicalDevice, vk_QueueFamily> deviceAndQueueFamily, const vector<const char*>& extensions, VkPhysicalDeviceFeatures features)
{
    vector<VkDeviceQueueCreateInfo> queues = {};

    float priority = 1.0;
    vector<float> transferQueuePriorities = {};

    VkDeviceQueueCreateInfo presentQueueCreateInfo  = {};
    presentQueueCreateInfo.sType                    = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    presentQueueCreateInfo.pNext                    = nullptr;
    presentQueueCreateInfo.queueCount               = 1;
    presentQueueCreateInfo.queueFamilyIndex         = deviceAndQueueFamily.second.queueFamilyIndex;
    presentQueueCreateInfo.flags                    = {};
    presentQueueCreateInfo.pQueuePriorities         = &priority;

    queues.push_back(presentQueueCreateInfo);


    pair<bool, vk_QueueFamily> transferFamily = deviceAndQueueFamily.first.hasTransferQueueFamily();

    if(transferFamily.first) {

        transferQueuePriorities.resize(transferFamily.second.queueFamilyProperties.queueCount);
        for(size_t i = 0; i < transferQueuePriorities.size(); ++i)
        {
            transferQueuePriorities[i] = 1.0f;
        }

        VkDeviceQueueCreateInfo transferQueue  = {};
        transferQueue.sType                    = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        transferQueue.pNext                    = nullptr;
        transferQueue.queueCount               = transferFamily.second.queueFamilyProperties.queueCount;
        transferQueue.queueFamilyIndex         = transferFamily.second.queueFamilyIndex;
        transferQueue.flags                    = {};
        transferQueue.pQueuePriorities         = transferQueuePriorities.data();

        queues.push_back(transferQueue);

        Logger::log("Found transfer queue. Will enable it!");
    }


    VkDeviceCreateInfo deviceCreateInfo     = {};
    deviceCreateInfo.sType                  = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext                  = nullptr;
    deviceCreateInfo.flags                  = {};
    deviceCreateInfo.queueCreateInfoCount   = static_cast<uint32_t >(queues.size());
    deviceCreateInfo.pQueueCreateInfos      = queues.data();
    deviceCreateInfo.enabledLayerCount      = 0;
    deviceCreateInfo.ppEnabledLayerNames    = nullptr;
    deviceCreateInfo.enabledExtensionCount  = static_cast<uint32_t >(extensions.size());
    deviceCreateInfo.ppEnabledExtensionNames= extensions.data();
    deviceCreateInfo.pEnabledFeatures       = &features;

    VkResult result = vkCreateDevice(deviceAndQueueFamily.first.physicalDevice, &deviceCreateInfo, nullptr, device.reset(vkDestroyDevice));
    handleResult(result, "Device creation has failed!");


    physicalDevice = deviceAndQueueFamily.first;
    vk_Queue present = {};
    present.queueFamily = deviceAndQueueFamily.second;

    vkGetDeviceQueue(device.get(), deviceAndQueueFamily.second.queueFamilyIndex, 0, &present.queue);

    if(transferFamily.first) {
        transferQueues.clear();
        transferQueues.resize(transferFamily.second.queueFamilyProperties.queueCount);
        for(uint32_t i = 0; i < transferFamily.second.queueFamilyProperties.queueCount; ++i) {

            vk_Queue transfer = {};
            transfer.queueFamily = transferFamily.second;
            vkGetDeviceQueue(device.get(), transferFamily.second.queueFamilyIndex, i, &transfer.queue);
            transferQueues[i] = transfer;
        }
    }

    presentationQueue = present;
    Logger::success("Logical device creation succeeded!");

    for(auto& item : extensions)
    {
        auto itemstr = string(item);
        auto pre = string("Enabled device extension: ");
        Logger::log(pre + itemstr);
    }
}

const PhysicalDevice& PresentDevice::getPhysicalDevice() const
{
    return physicalDevice;
}

PresentDeviceInfo PresentDevice::getPresentDeviceInfo() const {
    return { device.get(), physicalDevice.physicalDevice, presentationQueue };
}

PresentDevice::~PresentDevice() {

    if(device.get() != VK_NULL_HANDLE)
    {
        vkDeviceWaitIdle(device.get());
    }
}

DeviceInfo PresentDevice::getDeviceInfo() const {
    return { device.get(), physicalDevice.physicalDevice };
}
