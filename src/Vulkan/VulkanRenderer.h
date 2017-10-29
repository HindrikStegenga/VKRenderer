//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VULKANRENDERER_H
#define VKRENDERER_VULKANRENDERER_H

#include "VulkanPlatform.h"

class VulkanRenderer final {
public:
    explicit VulkanRenderer(string appName);
    ~VulkanRenderer() = default;

    VulkanRenderer(const VulkanRenderer&) = delete;
    VulkanRenderer(VulkanRenderer&&) = default;

    VulkanRenderer& operator= (const VulkanRenderer&) = delete;
    VulkanRenderer& operator= (VulkanRenderer&&) = default;
private:


public:






};


#endif //VKRENDERER_VULKANRENDERER_H
