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

#endif //VKRENDERER_UTILITYSTRUCTURES_H
