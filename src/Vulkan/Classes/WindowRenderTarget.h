//
// Created by Hindrik  Stegenga on 14/08/2018.
//

#ifndef VKRENDERER_WINDOWRENDERTARGET_H
#define VKRENDERER_WINDOWRENDERTARGET_H

#include <memory>
#include "Swapchain.h"
#include "VulkanRenderMode.h"
#include "../Platform/RenderWindow.h"

struct WindowRenderTarget final {
    VKUH<VkSurfaceKHR>              surface         = VKUH<VkSurfaceKHR>();
    Swapchain                       swapchain       = Swapchain();
    RenderWindow*                   renderWindow    = nullptr;
    unique_ptr<VulkanRenderMode>    renderMode      = nullptr;
};


#endif //VKRENDERER_WINDOWRENDERTARGET_H
