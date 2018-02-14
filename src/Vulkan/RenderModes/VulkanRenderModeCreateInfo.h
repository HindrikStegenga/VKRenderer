//
// Created by hindrik on 14-2-18.
//

#ifndef VKRENDERER_VULKANRENDERMODECREATEINFO_H
#define VKRENDERER_VULKANRENDERMODECREATEINFO_H

#include "../Platform/VulkanPlatform.h"

struct ForwardRenderModeCreateInfo
{
    PresentDeviceInfo   deviceInfo      = {};
    VkSurfaceKHR        surface         = VK_NULL_HANDLE;
};


#endif //VKRENDERER_VULKANRENDERMODECREATEINFO_H
