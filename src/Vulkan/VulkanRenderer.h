//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VULKANRENDERER_H
#define VKRENDERER_VULKANRENDERER_H

#include "VulkanPlatform.h"
#include "RenderWindow.h"
#include "../Utilities/Nullable.h"

static const char* debugLayers[] = {
        "VK_LAYER_LUNARG_standard_validation",
        "VK_LAYER_LUNARG_api_dump"
};

class VulkanRenderer final {
public:
    explicit VulkanRenderer(string appName, bool debugEnabled = false);
    ~VulkanRenderer() = default;

    VulkanRenderer(const VulkanRenderer&) = delete;
    VulkanRenderer(VulkanRenderer&&) = default;

    VulkanRenderer& operator= (const VulkanRenderer&) = delete;
    VulkanRenderer& operator= (VulkanRenderer&&) = default;
private:
    VKUH<VkInstance> instance = VKUH<VkInstance>(vkDestroyInstance);
    Nullable<RenderWindow> renderWindow;
public:
    bool processEvents() const;

private:
    void initInstance(map<string,string> args);



};


#endif //VKRENDERER_VULKANRENDERER_H
