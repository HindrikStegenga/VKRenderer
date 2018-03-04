//
// Created by hindrik on 25-11-17.
//

#include "Swapchain.h"

Swapchain::Swapchain(SwapchainCreateInfo createInfo) : device(createInfo.deviceInfo.logical), physicalDevice(createInfo.deviceInfo.physical), surface(createInfo.surface) {

    //Assume swapchain support was checked!
    vk_SwapchainSettings settings = chooseSettings(createInfo.width, createInfo.height);
    createSwapchain(settings);


}

vk_SwapchainSettings Swapchain::chooseSettings(uint32_t width, uint32_t height) {

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

    VkSurfaceFormatKHR surfaceFormat = chooseSurfaceFormat(formats);
    VkPresentModeKHR presentMode = choosePresentMode(presentModes);
    VkExtent2D extent = chooseExtent(width, height, caps);

    uint32_t imageCount = caps.minImageCount + 1;
    if (caps.maxImageCount > 0 && imageCount > caps.maxImageCount) {
        imageCount = caps.maxImageCount;
    }



    vk_SwapchainSettings settings = {};
    settings.extent = extent;
    settings.presentMode = presentMode;
    settings.surfaceFormat = surfaceFormat;
    settings.imageCount = imageCount;
    settings.preTransform = caps.currentTransform;

    return settings;
}


VkSurfaceFormatKHR Swapchain::chooseSurfaceFormat(const vector<VkSurfaceFormatKHR>& availableFormats) {

    if (availableFormats.size() == 1 && availableFormats.front().format == VK_FORMAT_UNDEFINED) {
        //No preferred format, so we can pick freely!
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }

    for(const auto& format : availableFormats) {
        if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return format;
        }
    }

    return availableFormats.front();
}

VkPresentModeKHR Swapchain::choosePresentMode(const vector<VkPresentModeKHR>& availableModes) {

    //Guaranteed to be available
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

    for(const auto& mode : availableModes) {

        if(mode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return mode;
        } else if(mode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = mode;
        }
    }

    return bestMode;
}

VkExtent2D Swapchain::chooseExtent(uint32_t width, uint32_t height, VkSurfaceCapabilitiesKHR surfaceCaps) {

    if (surfaceCaps.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return surfaceCaps.currentExtent;
    } else {

        VkExtent2D actualExtent = {width, height};

        actualExtent.width = std::max(surfaceCaps.minImageExtent.width, std::min(surfaceCaps.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(surfaceCaps.minImageExtent.height, std::min(surfaceCaps.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

void Swapchain::createSwapchain(vk_SwapchainSettings settings) {

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType                        = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.pNext                        = nullptr;
    createInfo.surface                      = surface;
    createInfo.minImageCount                = settings.imageCount;
    createInfo.imageFormat                  = settings.surfaceFormat.format;
    createInfo.imageColorSpace              = settings.surfaceFormat.colorSpace;
    createInfo.imageExtent                  = settings.extent;
    createInfo.imageArrayLayers             = 1;
    createInfo.imageUsage                   = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageSharingMode             = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount        = 0;
    createInfo.pQueueFamilyIndices          = nullptr;
    createInfo.preTransform                 = settings.preTransform;
    createInfo.compositeAlpha               = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode                  = settings.presentMode;
    createInfo.clipped                      = VK_TRUE;
    createInfo.oldSwapchain                 = VK_NULL_HANDLE;

    VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, swapchain.reset(device, vkDestroySwapchainKHR));
    handleResult(result, "Swapchain creation failed!");
    Logger::success("Succesfully created the swapchain!");
}