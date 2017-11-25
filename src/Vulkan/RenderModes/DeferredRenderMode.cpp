//
// Created by hindrik on 14-11-17.
//

#include "DeferredRenderMode.h"

DeferredRenderMode::DeferredRenderMode(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
        : VulkanRenderMode("Deferred", device, physicalDevice, surface){

    Logger::warn("Currently deferred rendering is not yet implemented!");

}

void DeferredRenderMode::render() {

}
