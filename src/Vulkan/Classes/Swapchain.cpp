//
// Created by hindrik on 25-11-17.
//

#include "Swapchain.h"

Swapchain::Swapchain(SwapchainCreateInfo createInfo) : device(createInfo.deviceInfo.logical), physicalDevice(createInfo.deviceInfo.physical), surface(createInfo.surface) {

    bool result = checkSupport();
    if (!result)
    {
        Logger::failure("Swapchain support was insufficient!");
    }


}

bool Swapchain::checkSupport() {

    VkSurfaceCapabilitiesKHR caps = {};

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &caps);

    uint32_t surfaceCount       = 0;
    uint32_t presentModeCount   = 0;

    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceCount, nullptr);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

    vector<VkSurfaceFormatKHR>  formats(surfaceCount);
    vector<VkPresentModeKHR>    presentModes(presentModeCount);

    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceCount, formats.data());
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data());

    if (formats.size() == 1 && formats.front().format == VK_FORMAT_UNDEFINED) {
        //No preferred format, so we can pick freely!

        


    }



    return true;
}
