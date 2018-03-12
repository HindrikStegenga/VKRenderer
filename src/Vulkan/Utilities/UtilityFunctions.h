//
// Created by Hindrik Stegenga on 3-11-17.
//

#ifndef VKRENDERER_VULKANUTILITYFUNCTIONS_H
#define VKRENDERER_VULKANUTILITYFUNCTIONS_H

#include "../Platform/VulkanPlatform.h"
#include "VkEnums.h"
#include <iostream>

using std::ostream;

auto operator<<(ostream& o, VkPhysicalDeviceType& t) -> ostream&;

auto operator<<(ostream& o, VkPhysicalDeviceProperties& p) -> ostream&;

auto operator<<(ostream& o, VkQueueFamilyProperties p) -> ostream&;

auto operator<<(ostream& o, VkExtensionProperties p) -> ostream&;

uint32_t deviceTypePriority(VkPhysicalDeviceType deviceType);

VkComponentMapping defaultComponentMapping();

VkImageSubresourceRange defaultImageSubresourceRange(VkImageAspectFlags aspectFlags);

uint32_t chooseMemoryTypeIndex(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags props);

VkFormat chooseSupportedFormat(VkPhysicalDevice physicalDevice, const vector<VkFormat>& availableFormats, VkImageTiling tiling, VkFormatFeatureFlags featureFlags);


VkCommandPoolCreateInfo getCommandPoolInfo(uint32_t familyIndex, bool individualReset, bool isTransient);

VkCommandBufferAllocateInfo getCommandBufferAllocateInfo(VkCommandPool pool, uint32_t bufferCount, VkCommandBufferLevel level);

VkCommandBufferBeginInfo getCommandBufferBeginInfoPrimary(PrimaryCommandBufferUsage usage);



VkPipelineInputAssemblyStateCreateInfo getAssemblyInputState(VkPrimitiveTopology topology, bool restartEnable);

VkPipelineViewportStateCreateInfo getViewportState(const VkViewport& viewport, const VkRect2D& scissors);


#endif //VKRENDERER_VULKANUTILITYFUNCTIONS_H
