//
// Created by hindrik on 14-11-17.
//

#ifndef VKRENDERER_DEFERREDRENDERMODE_H
#define VKRENDERER_DEFERREDRENDERMODE_H


#include "../Classes/VulkanRenderMode.h"

class DeferredRenderMode : public VulkanRenderMode {

public:
    DeferredRenderMode(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    ~DeferredRenderMode() override = default;
    void render() override;

    void windowHasResized(uint32_t width, uint32_t height) override;
};


#endif //VKRENDERER_DEFERREDRENDERMODE_H
