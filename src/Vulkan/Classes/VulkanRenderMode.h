//
// Created by hindrik on 12-11-17.
//

#ifndef VKRENDERER_VULKANRENDERMODE_H
#define VKRENDERER_VULKANRENDERMODE_H

#include "../Platform/VulkanPlatform.h"

class VulkanRenderMode {
private:
    string                      name;
    VKUH<VkSwapchainKHR>        swapChain;
    vector<VKUH<VkRenderPass>>  renderPasses;
    vector<VKUH<VkPipeline>>    pipelines;
    vector<VkCommandPool>       commandPools;
public:
    explicit VulkanRenderMode(string renderModeName);
    virtual ~VulkanRenderMode() = 0;
public:
    virtual void render() = 0;

};

inline VulkanRenderMode::~VulkanRenderMode() = default;

#endif //VKRENDERER_VULKANRENDERMODE_H
