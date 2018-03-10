//
// Created by hindrik on 12-11-17.
//

#include "VulkanRenderMode.h"

VulkanRenderMode::VulkanRenderMode(const VulkanRenderModeCreateInfo& createInfo)
        : name(createInfo.name),
          device(createInfo.deviceInfo.logical),
          physicalDevice(createInfo.deviceInfo.physical),
          presentQueue(createInfo.deviceInfo.presentQueue)
{

    Logger::log("Initializing rendermode: " + name);
}

vector<VKUH<VkFramebuffer>> VulkanRenderMode::createFrameBuffersFromSwapchain(VkRenderPass renderPass, vk_RendermodeSwapchainInfo swapchainInfo)
{

    vector<VKUH<VkFramebuffer>> frameBuffers;
    frameBuffers.resize(swapchainInfo.colorImageViews.size());

    for(size_t i = 0; i < swapchainInfo.colorImageViews.size(); ++i) {

        VkImageView imageView = swapchainInfo.colorImageViews[i];

        VkFramebufferCreateInfo frameBufferCreateInfo   = {};
        frameBufferCreateInfo.sType                     = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        frameBufferCreateInfo.pNext                     = nullptr;
        frameBufferCreateInfo.renderPass                = renderPass;
        frameBufferCreateInfo.attachmentCount           = 1;
        frameBufferCreateInfo.pAttachments              = &imageView;
        frameBufferCreateInfo.flags                     = {};
        frameBufferCreateInfo.width                     = swapchainInfo.width;
        frameBufferCreateInfo.height                    = swapchainInfo.height;
        frameBufferCreateInfo.layers                    = 1;

        VkResult result = vkCreateFramebuffer(device, &frameBufferCreateInfo, nullptr, frameBuffers[i].reset(device, vkDestroyFramebuffer));
        handleResult(result, "Failed creating frame buffer!");
        Logger::success("Succesfully created frame buffer!");
    }

    return frameBuffers;
}
