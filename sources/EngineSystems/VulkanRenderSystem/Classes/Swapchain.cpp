//
// Created by hindrik on 25-11-17.
//

#include "Swapchain.h"
#include "../Utilities/UtilityFunctions.h"

Swapchain::Swapchain(SwapchainCreateInfo createInfo) : device(createInfo.deviceInfo.logical), physicalDevice(createInfo.deviceInfo.physical), surface(createInfo.surface), presentQueue(createInfo.deviceInfo.presentQueue), preventTearing(createInfo.preventTearing), limitFrameRate(createInfo.limitFrameRate) {

    //Assume swapchain support was checked!
    recreateSwapchain(createInfo.width, createInfo.height, createInfo.preferredFramesInFlight, createInfo.preventTearing, createInfo.limitFrameRate);
}

vk_RendermodeSwapchainInfo Swapchain::recreateSwapchain(uint32_t width, uint32_t height, uint32_t preferredFramesInFlight, bool preventTearing, bool limitFrameRate) {

    vk_SwapchainSettings swapchainSettings = chooseSettings(width, height, preferredFramesInFlight, preventTearing, limitFrameRate);
    createSwapchain(swapchainSettings);

    return getRendermodeSwapchainInfo();
}

vk_SwapchainSettings Swapchain::chooseSettings(uint32_t width, uint32_t height, uint32_t preferredFramesInFlight, bool preventTearing, bool limitFrameRate) {

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
    VkPresentModeKHR presentMode = choosePresentMode(presentModes, preventTearing, limitFrameRate);
    VkExtent2D extent = chooseExtent(width, height, caps);

    uint32_t imageCount = caps.minImageCount + 1;
    if (caps.maxImageCount > 0 && imageCount > caps.maxImageCount) {
        imageCount = caps.maxImageCount;
    }

    vk_SwapchainSettings settings       = {};
    settings.extent                     = extent;
    settings.presentMode                = presentMode;
    settings.surfaceFormat              = surfaceFormat;
    settings.imageCount                 = imageCount;
    settings.preTransform               = caps.currentTransform;
    settings.preferredFramesInFlight    = preferredFramesInFlight;

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

VkPresentModeKHR Swapchain::choosePresentMode(const vector<VkPresentModeKHR>& availableModes, bool preventTearing, bool limitFrameRate) {

    using std::begin;
    using std::end;

    //Guaranteed to be available
    if (preventTearing && limitFrameRate) {
        Logger::log("Selected FIFO presentmode.");
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    //TEARING - NO LIMIT

    if (!preventTearing && !limitFrameRate) {
        if (std::find(begin(availableModes), end(availableModes), VK_PRESENT_MODE_IMMEDIATE_KHR) != end(availableModes)) {
            Logger::log("Selected IMMEDIATE presentmode.");
            return VK_PRESENT_MODE_IMMEDIATE_KHR;
        }
        if (std::find(begin(availableModes), end(availableModes), VK_PRESENT_MODE_MAILBOX_KHR) != end(availableModes)) {
            Logger::log("Selected MAILBOX presentmode.");
            return VK_PRESENT_MODE_MAILBOX_KHR;
        }
        Logger::warn("We could not find a present mode which provided no limit and allowed tearing!");

        if (std::find(begin(availableModes), end(availableModes), VK_PRESENT_MODE_FIFO_RELAXED_KHR) != end(availableModes)) {
            Logger::log("Selected FIFO_RELAXED presentmode.");
            return VK_PRESENT_MODE_FIFO_RELAXED_KHR;
        }

        Logger::log("Selected FIFO presentmode.");
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    //TEARING - LIMIT

    if (!preventTearing) {
        if (std::find(begin(availableModes), end(availableModes), VK_PRESENT_MODE_FIFO_RELAXED_KHR) != end(availableModes)) {
            Logger::log("Selected FIFO_RELAXED presentmode.");
            return VK_PRESENT_MODE_FIFO_RELAXED_KHR;
        }
        Logger::log("Selected FIFO presentmode.");
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    //NO TEARING - NO LIMIT
    if (std::find(begin(availableModes), end(availableModes), VK_PRESENT_MODE_MAILBOX_KHR) != end(availableModes)) {
        Logger::log("Selected MAILBOX presentmode.");
        return VK_PRESENT_MODE_MAILBOX_KHR;
    }
    if (std::find(begin(availableModes), end(availableModes), VK_PRESENT_MODE_FIFO_RELAXED_KHR) != end(availableModes)) {
        Logger::log("Selected FIFO_RELAXED presentmode.");
        return VK_PRESENT_MODE_FIFO_RELAXED_KHR;
    }

    Logger::warn("We could not find a present mode which provided no tearing and no limit!");
    Logger::log("Selected FIFO presentmode.");
    return VK_PRESENT_MODE_FIFO_KHR;
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

    VKUH<VkSwapchainKHR> oldSwapchain = VKUH<VkSwapchainKHR>(std::move(swapchain));

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
    createInfo.oldSwapchain                 = oldSwapchain.get();

    VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, swapchain.reset(device, vkDestroySwapchainKHR));
    handleResult(result, "Swapchain creation failed!");

    if(oldSwapchain.get() != VK_NULL_HANDLE) {
        vkDeviceWaitIdle(device);
        oldSwapchain.reset();
    }

    this->settings = settings;

    retrieveImages(settings.preferredFramesInFlight);
    createImageViews();
    createDepthStencil();
    createFences();
    createSemaphores();

    Logger::success("Succesfully created the swapchain!");
}

void Swapchain::retrieveImages(uint32_t preferredFramesInFlight) {

    images.clear();

    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(device, swapchain.get(), &imageCount, nullptr);

    if (imageCount == 0) {
        Logger::failure("There cannot be 0 swapchain images!");
    }

    if (preferredFramesInFlight == 0) {
        framesInFlight = 1;
    } else {
        if (preferredFramesInFlight > 0 && preferredFramesInFlight <= imageCount) {
            framesInFlight = preferredFramesInFlight;
        } else {
            framesInFlight = imageCount;
        }
    }

    Logger::log("Frames that will be simultaneously in flight: " + std::to_string(framesInFlight));


    images.resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapchain.get(), &imageCount, images.data());
}

void Swapchain::createImageViews() {

    imageViews.resize(images.size());

    for(size_t i = 0; i < imageViews.size(); ++i) {

        //Create image view

        VkImageViewCreateInfo createInfo = {};
        createInfo.sType        = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.pNext        = nullptr;
        createInfo.image        = images[i];
        createInfo.viewType     = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format       = settings.surfaceFormat.format;
        createInfo.components   = defaultComponentMapping();

        VkImageSubresourceRange range   = {};
        range.aspectMask                = VK_IMAGE_ASPECT_COLOR_BIT;
        range.baseMipLevel              = 0;
        range.levelCount                = 1;
        range.baseArrayLayer            = 0;
        range.layerCount                = 1;

        createInfo.subresourceRange = range;

        VkImageView imageView = VK_NULL_HANDLE;
        VkResult result = vkCreateImageView(device, &createInfo, nullptr, &imageView);
        handleResult(result, "Swapchain imageview creation failed.");

        imageViews[i] = VkUniqueHandle<VkImageView>(imageView, device, vkDestroyImageView);
    }
}

void Swapchain::createDepthStencil() {

    VkFormat format = chooseDepthStencilFormat();

    createDepthStencilImage(format);
    allocateDepthStencilMemory();
    createDepthStencilImageView(format);

}

VkFormat Swapchain::chooseDepthStencilFormat(bool requiresStencil) const {

    static const vector<VkFormat> stencilFormats = { VK_FORMAT_D32_SFLOAT_S8_UINT,
                                                     VK_FORMAT_D24_UNORM_S8_UINT };

    static const vector<VkFormat> withNonStencilFormats = { VK_FORMAT_D32_SFLOAT,
                                                            VK_FORMAT_D32_SFLOAT_S8_UINT,
                                                            VK_FORMAT_D24_UNORM_S8_UINT };

    return chooseSupportedFormat(physicalDevice, requiresStencil ? stencilFormats : withNonStencilFormats, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}

void Swapchain::createDepthStencilImage(VkFormat format) {

    VkImageCreateInfo imageCreateInfo = {};

    imageCreateInfo.sType                   = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.pNext                   = nullptr;
    imageCreateInfo.flags                   = {};
    imageCreateInfo.imageType               = VK_IMAGE_TYPE_2D;
    imageCreateInfo.format                  = format;
    imageCreateInfo.extent                  = VkExtent3D { settings.extent.width, settings.extent.height, 1};
    imageCreateInfo.mipLevels               = 1;
    imageCreateInfo.arrayLayers             = 1;
    imageCreateInfo.samples                 = VK_SAMPLE_COUNT_1_BIT;
    imageCreateInfo.usage                   = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    imageCreateInfo.sharingMode             = VK_SHARING_MODE_EXCLUSIVE;
    imageCreateInfo.queueFamilyIndexCount   = 0;
    imageCreateInfo.pQueueFamilyIndices     = nullptr;
    imageCreateInfo.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;

    VkResult result = vkCreateImage(device, &imageCreateInfo, nullptr, depthStencilImage.reset(device, vkDestroyImage));

    handleResult(result, "Depth/stencil image creation has failed!");
}

void Swapchain::allocateDepthStencilMemory() {

    VkMemoryRequirements memoryRequirements = {};
    vkGetImageMemoryRequirements(device, depthStencilImage.get(), &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo   = {};
    allocateInfo.sType                  = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.pNext                  = nullptr;
    allocateInfo.allocationSize         = memoryRequirements.size;
    allocateInfo.memoryTypeIndex        = chooseMemoryTypeIndex(physicalDevice, memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    VkResult result = vkAllocateMemory(device, &allocateInfo, nullptr, depthStencilMemory.reset(device, vkFreeMemory));

    handleResult(result, "Could not allocate memory for depth/stencil image!");

    vkBindImageMemory(device, depthStencilImage.get(), depthStencilMemory.get(), 0);
}

void Swapchain::createDepthStencilImageView(VkFormat format) {

    VkImageViewCreateInfo viewCreateInfo = {};

    viewCreateInfo.sType                = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewCreateInfo.pNext                = nullptr;
    viewCreateInfo.flags                = {};
    viewCreateInfo.image                = depthStencilImage.get();
    viewCreateInfo.viewType             = VK_IMAGE_VIEW_TYPE_2D;
    viewCreateInfo.format               = format;
    viewCreateInfo.subresourceRange     = defaultImageSubresourceRange(VK_IMAGE_ASPECT_DEPTH_BIT);

    VkResult result = vkCreateImageView(device, &viewCreateInfo, nullptr, depthStencilImageView.reset(device, vkDestroyImageView));

    handleResult(result, "Depth/stencil imageView creation has failed!");
}

vk_RendermodeSwapchainInfo Swapchain::getRendermodeSwapchainInfo() const {

    vk_RendermodeSwapchainInfo swapchainInfo = {};

    swapchainInfo.width  = settings.extent.width;
    swapchainInfo.height = settings.extent.height;
    swapchainInfo.format = settings.surfaceFormat.format;

    VkViewport viewport = {};
    viewport.x          = 0.0f;
    viewport.y          = 0.0f;
    viewport.maxDepth   = 1.0;
    viewport.minDepth   = 0.0f;
    viewport.width      = swapchainInfo.width;
    viewport.height     = swapchainInfo.height;

    VkRect2D scissor    = {};
    scissor.offset      = VkOffset2D { 0, 0 };
    scissor.extent      = VkExtent2D { swapchainInfo.width, swapchainInfo.height };

    swapchainInfo.fullscreenViewport = viewport;
    swapchainInfo.fullscreenScissor = scissor;

    swapchainInfo.colorImageViews.resize(imageViews.size());
    for(size_t i = 0; i < imageViews.size(); ++i) {
        swapchainInfo.colorImageViews[i] = imageViews[i].get();
    }

    return swapchainInfo;
}

void Swapchain::createFences() {

    currentFrameIndex = 0;

    imageFences.clear();
    imageFences.reserve(framesInFlight);

    for(uint32_t i = 0; i < framesInFlight; ++i)
    {
        imageFences.emplace_back(device, true);
    }
}

void Swapchain::createSemaphores() {

    imageAvailableSemaphores.clear();
    renderFinishedSemaphores.clear();
    imageAvailableSemaphores.resize(framesInFlight);
    renderFinishedSemaphores.resize(framesInFlight);

    VkSemaphoreCreateInfo createInfo    = {};
    createInfo.sType                    = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    createInfo.pNext                    = nullptr;
    createInfo.flags                    = {};


    for(uint32_t i = 0; i < framesInFlight; ++i) {
        VkResult result = vkCreateSemaphore(device, &createInfo, nullptr, imageAvailableSemaphores[i].reset(device, vkDestroySemaphore));
        handleResult(result, "Failed to create image available semaphore!");

        result = vkCreateSemaphore(device, &createInfo, nullptr, renderFinishedSemaphores[i].reset(device, vkDestroySemaphore));
        handleResult(result, "Failed to create render finished semaphore!");
    }

    Logger::success("Succesfully created semaphores!");
}

vk_PresentImageInfo Swapchain::acquireNextImage() {

    Fence& fence = imageFences[currentFrameIndex];

    fence.wait();
    fence.reset();

    uint32_t imageIndex = 0;
    VkResult result = vkAcquireNextImageKHR(device, swapchain.get(), std::numeric_limits<uint64_t >::max(), imageAvailableSemaphores[currentFrameIndex].get(), VK_NULL_HANDLE, &imageIndex);

    vk_PresentImageInfo info = {};

    switch(result) {
        case VK_SUCCESS:
        case VK_SUBOPTIMAL_KHR:

            info.imageIndex                 = imageIndex;
            info.submitDoneFence            = fence.get();
            info.mustRecreateSwapchain      = false;
            info.renderFinishedSemaphore    = renderFinishedSemaphores[currentFrameIndex].get();
            info.imageAvailableSemaphore    = imageAvailableSemaphores[currentFrameIndex].get();

            break;
        case VK_ERROR_OUT_OF_DATE_KHR:

            info.imageIndex = std::numeric_limits<uint32_t >::max();
            info.submitDoneFence            = VK_NULL_HANDLE;
            info.mustRecreateSwapchain      = true;
            info.renderFinishedSemaphore    = VK_NULL_HANDLE;
            info.imageAvailableSemaphore    = VK_NULL_HANDLE;

            break;
        default:
            Logger::failure("Failed getting the next swapchain image!");
    }
    return info;
}

void Swapchain::presentImage(uint32_t imageIndex, bool &mustRecreateSwapchain) {

    VkSemaphore renderFinished  = renderFinishedSemaphores[currentFrameIndex].get();
    VkSwapchainKHR cSwapchain   = swapchain.get();

    VkPresentInfoKHR presentInfo    = {};
    presentInfo.sType               = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pNext               = nullptr;
    presentInfo.waitSemaphoreCount  = 1;
    presentInfo.pWaitSemaphores     = &renderFinished;
    presentInfo.pImageIndices       = &imageIndex;
    presentInfo.pResults            = nullptr;
    presentInfo.swapchainCount      = 1;
    presentInfo.pSwapchains         = &cSwapchain;

    //Determine semaphore to use and fence to wait on for next frame.
    currentFrameIndex = (currentFrameIndex + 1) % static_cast<uint32_t >(framesInFlight);

    VkResult result = vkQueuePresentKHR(presentQueue.queue, &presentInfo);

    switch(result) {
        case VK_SUCCESS:
            return;
        case VK_ERROR_OUT_OF_DATE_KHR:
            mustRecreateSwapchain = true;
            return;
        case VK_SUBOPTIMAL_KHR:
            return;
        default:
            Logger::failure("Failed getting the next swapchain image!");
            return;
    }
}

uint32_t Swapchain::preferredFramesInFlight() {
    return settings.preferredFramesInFlight;
}

bool Swapchain::preferredTearingSetting() {
    return preventTearing;
}

bool Swapchain::preferredFrameLimitingSetting() {
    return limitFrameRate;
}
