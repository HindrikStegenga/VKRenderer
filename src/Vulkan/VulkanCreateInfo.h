//
// Created by hindrik on 14-2-18.
//

#ifndef VKRENDERER_VULKANCREATEINFO_H
#define VKRENDERER_VULKANCREATEINFO_H

#include "../CommonInclude.h"
#include "Utilities/UtilityStructures.h"
#include <vulkan/vulkan.h>


struct VulkanInstanceCreateInfo final {

    const vector<const char*>& validationLayers;
    const vector<const char*>& extensions;
    const vector<const char*>& debugValidationLayers;
    const vector<const char*>& debugExtensions;
};

struct PresentDeviceCreateInfo final {

    const vector<const char*>&          extensions;
    const vector<const char*>&          debugExtensions;
    const VkPhysicalDeviceFeatures&     requiredFeatures;
    VkSurfaceKHR                        surfaceHandle       = VK_NULL_HANDLE;
};

struct PresentDeviceInfo final {

    VkDevice            logical         = VK_NULL_HANDLE;
    VkPhysicalDevice    physical        = VK_NULL_HANDLE;
    vk_Queue            presentQueue    = {};
};


struct DeviceInfo final {

    VkDevice            logical     = VK_NULL_HANDLE;
    VkPhysicalDevice    physical    = VK_NULL_HANDLE;

};

struct VulkanRenderModeCreateInfo final {

    string              name            = "";
    PresentDeviceInfo   deviceInfo      = {};
    VkSurfaceKHR        surface         = VK_NULL_HANDLE;
};

struct SwapchainCreateInfo final {

    uint32_t            width       = 0;
    uint32_t            height      = 0;
    PresentDeviceInfo   deviceInfo  = {};
    VkSurfaceKHR        surface     = VK_NULL_HANDLE;

};


#endif //VKRENDERER_VULKANCREATEINFO_H
