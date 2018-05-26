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

struct vk_RendermodeSwapchainInfo final {

    uint32_t            width               = 0;
    uint32_t            height              = 0;
    VkFormat            format              = VK_FORMAT_UNDEFINED;
    vector<VkImageView> colorImageViews     = {};
    VkViewport          fullscreenViewport  = {};
    VkRect2D            fullscreenScissor   = {};

};

struct vk_PresentImageInfo final {

    VkFence     submitDoneFence         = nullptr;
    uint32_t    imageIndex              = 0;
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderFinishedSemaphore = VK_NULL_HANDLE;
    bool        mustRecreateSwapchain   = false;

};

struct vk_RenderFrameInfo final {

    uint32_t    imageIndex                  = 0;
    VkSemaphore imageAvailableSemaphore     = VK_NULL_HANDLE;
    VkSemaphore renderFinishedSemaphore     = VK_NULL_HANDLE;
    VkFence     submitDoneFence             = nullptr;

};

struct vk_MemoryHeap final {

    VkMemoryHeap    memoryHeap                              = {};
    uint32_t        memoryTypeCount                         = 0;
    VkMemoryType    memoryTypes      [VK_MAX_MEMORY_TYPES]  = {};
    uint32_t        memoryTypeIndices[VK_MAX_MEMORY_TYPES]  = {};

};

struct vk_MemoryAllocation final {

    VkDeviceMemory  allocation;
    VkDeviceSize    size;
    uint32_t        memoryTypeIndex;

};

struct vk_Allocation final {

    VkDeviceSize offset;
    VkDeviceSize size;
    VkBuffer     buffer;

};



#endif //VKRENDERER_UTILITYSTRUCTURES_H
