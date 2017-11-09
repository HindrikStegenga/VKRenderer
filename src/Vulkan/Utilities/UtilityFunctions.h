//
// Created by Hindrik Stegenga on 3-11-17.
//

#ifndef VKRENDERER_VULKANUTILITYFUNCTIONS_H
#define VKRENDERER_VULKANUTILITYFUNCTIONS_H

#include "../Platform/VulkanPlatform.h"
#include <iostream>

using std::ostream;

ostream& operator<<(ostream& o, VkPhysicalDeviceType& t);

ostream& operator<<(ostream& o, VkPhysicalDeviceProperties& p);

ostream& operator<<(ostream& o, VkQueueFamilyProperties p);

ostream& operator<<(ostream& o, VkExtensionProperties p);

uint32_t deviceTypePriority(VkPhysicalDeviceType deviceType);

#endif //VKRENDERER_VULKANUTILITYFUNCTIONS_H
