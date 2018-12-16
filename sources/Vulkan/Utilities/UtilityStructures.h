//
// Created by Hindrik Stegenga on 7-11-17.
//

#ifndef VKRENDERER_UTILITYSTRUCTURES_H
#define VKRENDERER_UTILITYSTRUCTURES_H

#include "../Platform/VulkanPlatform.h"
#include "../../Serializables/ConfigTypes.h"

struct vk_GeneralSettings {
    ApplicationSettings applicationSettings = {};
    GraphicsSettings graphicsSettings       = {};
    VulkanSettings vulkanSettings           = {};
};

struct vk_QueueFamily final {
    uint32_t                queueFamilyIndex        = UINT32_MAX;
    VkQueueFamilyProperties queueFamilyProperties   = {};
};

struct vk_Queue final {
    VkQueue         queue       = VK_NULL_HANDLE;
    vk_QueueFamily  queueFamily = {};
};

struct vk_SwapchainSettings final {

    uint32_t                        preferredFramesInFlight = 0;
    VkExtent2D                      extent                  = {};
    VkSurfaceFormatKHR              surfaceFormat           = {};
    VkPresentModeKHR                presentMode             = {};
    uint32_t                        imageCount              = 0;
    VkSurfaceTransformFlagBitsKHR   preTransform            = {};

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

    VkFence     submitDoneFence         = VK_NULL_HANDLE;

    uint32_t    imageIndex              = 0;
    VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore renderFinishedSemaphore = VK_NULL_HANDLE;
    bool        mustRecreateSwapchain   = false;

};

struct vk_MemoryHeap final {

    VkMemoryHeap    memoryHeap                              = {};
    uint32_t        memoryTypeCount                         = 0;
    VkMemoryType    memoryTypes      [VK_MAX_MEMORY_TYPES]  = {};
    uint32_t        memoryTypeIndices[VK_MAX_MEMORY_TYPES]  = {};

};

struct vk_MemoryHeapUsageTracker final {

    uint32_t        heapIndex       = 0;
    VkDeviceSize    usedHeapSize    = 0;
    VkMemoryHeap    memoryHeap      = {};

};

struct vk_MemoryType final {

    uint32_t        memoryTypeIndex = 0;
    VkMemoryType    memoryType      = {};

};

struct vk_MemoryAllocation final {

    VkDeviceMemory  allocation          = VK_NULL_HANDLE;
    VkDeviceSize    size                = 0;
    vk_MemoryType   memoryType          = {};

};

struct vk_Allocation final {

    VkDeviceSize offset     = 0;
    VkDeviceSize size       = 0;
    VkBuffer     buffer     = VK_NULL_HANDLE;

};



#endif //VKRENDERER_UTILITYSTRUCTURES_H
