//
// Created by hindrik on 14-2-18.
//

#ifndef VKRENDERER_VULKANRENDERMODECREATEINFO_H
#define VKRENDERER_VULKANRENDERMODECREATEINFO_H

#include "../Platform/VulkanPlatform.h"

struct ForwardRenderModeCreateInfo
{
    PresentDeviceInfo               deviceInfo      = {};
    VkSurfaceKHR                    surface         = VK_NULL_HANDLE;
    vk_RendermodeSwapchainInfo      swapchainInfo   = {};
};


#endif //VKRENDERER_VULKANRENDERMODECREATEINFO_H
