//
// Created by hindrik on 12-11-17.
//

#include "VulkanRenderMode.h"

VulkanRenderMode::VulkanRenderMode(const VulkanRenderModeCreateInfo& createInfo)
        : name(createInfo.name),
          device(createInfo.deviceInfo.logical),
          physicalDevice(createInfo.deviceInfo.physical)
{

    Logger::log("Initializing rendermode: " + name);


    


}