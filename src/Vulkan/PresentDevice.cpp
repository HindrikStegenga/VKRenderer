//
// Created by Hindrik Stegenga on 3-11-17.
//

#include "PresentDevice.h"

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

    PhysicalDevice physicalDevice = selectPhysicalDevice(instance, params, usedExtensions, supportDescription.requiredFeatures);

}

PhysicalDevice PresentDevice::selectPhysicalDevice(VkInstance instance, const map<string, string>& params, const vector<const char*>& extensions, const VkPhysicalDeviceFeatures& requiredFeatures)
{
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);

    if (physicalDeviceCount == 0) {
        Logger::failure("No physical Vulkan capable devices available!");
    }

    vector<VkPhysicalDevice> devices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, devices.data());

    vector<PhysicalDevice> possibleDevices;

    for (auto deviceHandle : devices) {
        PhysicalDevice device(deviceHandle);

        if (device.isSuitable(extensions, requiredFeatures)) {
            possibleDevices.push_back(device);
        }
    }
    if (possibleDevices.empty()) {
        Logger::failure("Vulkan devices were found, but none were capable enough!");
    }




}
