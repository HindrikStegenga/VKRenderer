//
// Created by hindrik on 12-11-17.
//

#include "VulkanRenderMode.h"

VulkanRenderMode::VulkanRenderMode(string renderModeName, VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
        : name(std::move(renderModeName)),
          device(device), physicalDevice(physicalDevice), surface(surface){

    Logger::log("Initialized rendermode: " + name);

}