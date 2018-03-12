//
// Created by Hindrik  Stegenga on 12/03/2018.
//

#ifndef VKRENDERER_VKENUMS_H
#define VKRENDERER_VKENUMS_H

#include <cstdint>
#include <vulkan/vulkan.h>

enum class PrimaryCommandBufferUsage : VkCommandBufferUsageFlags {

    OneTimeSubmit   = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    Simultaneous    = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
};


#endif //VKRENDERER_VKENUMS_H
