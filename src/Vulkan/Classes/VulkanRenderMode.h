//
// Created by hindrik on 12-11-17.
//

#ifndef VKRENDERER_VULKANRENDERMODE_H
#define VKRENDERER_VULKANRENDERMODE_H

#include "../Platform/VulkanPlatform.h"
#include "Swapchain.h"
#include "../../Utilities/Nullable.h"

class VulkanRenderMode {
protected:
    string                      name            = "";
    VkDevice                    device          = VK_NULL_HANDLE;
    VkPhysicalDevice            physicalDevice  = VK_NULL_HANDLE;
    vk_Queue                    presentQueue    = {};
public:
    explicit VulkanRenderMode(const VulkanRenderModeCreateInfo& createInfo);
    virtual ~VulkanRenderMode() = 0;

    VulkanRenderMode(const VulkanRenderMode&)       = delete;
    VulkanRenderMode(VulkanRenderMode&&) noexcept   = default;

    VulkanRenderMode& operator=(const VulkanRenderMode&)    = delete;
    VulkanRenderMode& operator=(VulkanRenderMode&&)         = default;
public:
    virtual void render(vk_RenderFrameInfo renderFrameInfo) = 0;
    virtual void windowHasResized(vk_RendermodeSwapchainInfo swapchainInfo) = 0;
protected:
    vector<VKUH<VkFramebuffer>> createFrameBuffersFromSwapchain(VkRenderPass renderPass, vk_RendermodeSwapchainInfo swapchainInfo);

};

inline VulkanRenderMode::~VulkanRenderMode() = default;

#endif //VKRENDERER_VULKANRENDERMODE_H
