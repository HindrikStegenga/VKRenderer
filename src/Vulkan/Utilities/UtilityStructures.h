//
// Created by Hindrik Stegenga on 7-11-17.
//

#ifndef VKRENDERER_UTILITYSTRUCTURES_H
#define VKRENDERER_UTILITYSTRUCTURES_H

#include "../Platform/VulkanPlatform.h"

struct vk_QueueFamily final {
    uint32_t                queueFamilyIndex        = UINT32_MAX;
    VkQueueFamilyProperties queueFamilyProperties   = {};
};

struct vk_Queue final {
    VkQueue         queue       = VK_NULL_HANDLE;
    vk_QueueFamily  queueFamily = {};
};

struct vk_SwapchainSettings final {

    VkExtent2D                      extent          = {};
    VkSurfaceFormatKHR              surfaceFormat   = {};
    VkPresentModeKHR                presentMode     = {};
    uint32_t                        imageCount      = 0;
    VkSurfaceTransformFlagBitsKHR   preTransform    = {};

};

struct vk_RendermodeSwapchainInfo {

    uint32_t            width               = 0;
    uint32_t            height              = 0;
    VkFormat            format              = VK_FORMAT_UNDEFINED;
    vector<VkImageView> colorImageViews     = {};
    VkViewport          fullscreenViewport  = {};
    VkRect2D            fullscreenScissor   = {};

};

class Fence;

struct vk_PresentImageInfo {

    Fence*      waitFence               = nullptr;
    uint32_t    imageIndex              = 0;
    bool        mustRecreateSwapchain   = false;

};


struct vk_RenderFrameInfo {

    uint32_t    imageIndex      = 0;
    VkSemaphore imageAvailable  = VK_NULL_HANDLE;
    VkSemaphore renderFinished  = VK_NULL_HANDLE;
    Fence*      waitFence       = nullptr;

};






#endif //VKRENDERER_UTILITYSTRUCTURES_H
