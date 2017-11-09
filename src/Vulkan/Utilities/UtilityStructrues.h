//
// Created by Hindrik Stegenga on 7-11-17.
//

#ifndef VKRENDERER_UTILITYSTRUCTRUES_H
#define VKRENDERER_UTILITYSTRUCTRUES_H

#include "../Platform/VulkanPlatform.h"

struct vk_QueueFamily {
    uint32_t                queueFamilyIndex        = UINT32_MAX;
    VkQueueFamilyProperties queueFamilyProperties   = {};
};

struct vk_Queue {
    VkQueue         queue       = VK_NULL_HANDLE;
    vk_QueueFamily  queueFamily = {};
};

#endif //VKRENDERER_UTILITYSTRUCTRUES_H
