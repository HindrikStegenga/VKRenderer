//
// Created by Hindrik Stegenga on 3-11-17.
//

#ifndef VKRENDERER_VULKANUTILITYFUNCTIONS_H
#define VKRENDERER_VULKANUTILITYFUNCTIONS_H

#include "../Platform/VulkanPlatform.h"
#include "VkEnums.h"
#include "Parsable/VertexLayout.h"
#include <iostream>

using std::ostream;

auto operator<<(ostream& o, const VkPhysicalDeviceType& p) -> ostream&;

auto operator<<(ostream& o, const VkPhysicalDeviceProperties& p) -> ostream&;

auto operator<<(ostream& o, const VkQueueFamilyProperties& p) -> ostream&;

auto operator<<(ostream& o, const VkExtensionProperties& p) -> ostream&;

auto operator<<(ostream& o, const vk_MemoryHeap& p) -> ostream&;

auto operator<<(ostream& o, const vk_MemoryType& p) -> ostream&;


bool isDeviceLocal(VkMemoryType memoryType);
bool isHostVisible(VkMemoryType memoryType);
bool isHostCoherent(VkMemoryType memoryType);
bool isHostCached(VkMemoryType memoryType);
bool isLazilyAllocated(VkMemoryType memoryType);
bool isProtected(VkMemoryType memoryType);

bool isNotDeviceLocal(VkMemoryType memoryType);
bool isNotHostVisible(VkMemoryType memoryType);
bool isNotHostCoherent(VkMemoryType memoryType);
bool isNotHostCached(VkMemoryType memoryType);
bool isNotLazilyAllocated(VkMemoryType memoryType);
bool isNotProtected(VkMemoryType memoryType);


uint32_t deviceTypePriority(VkPhysicalDeviceType deviceType);

VkComponentMapping defaultComponentMapping();

VkImageSubresourceRange defaultImageSubresourceRange(VkImageAspectFlags aspectFlags);

uint32_t chooseMemoryTypeIndex(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags props);

VkFormat chooseSupportedFormat(VkPhysicalDevice physicalDevice, const vector<VkFormat>& availableFormats, VkImageTiling tiling, VkFormatFeatureFlags featureFlags);


VkCommandPoolCreateInfo getCommandPoolInfo(uint32_t familyIndex, bool individualReset, bool isTransient);

VkCommandBufferAllocateInfo getCommandBufferAllocateInfo(VkCommandPool pool, uint32_t bufferCount, VkCommandBufferLevel level);

VkCommandBufferBeginInfo getCommandBufferBeginInfoPrimary(PrimaryCommandBufferUsage usage);

VkPipelineMultisampleStateCreateInfo getMultisampleState(VkSampleCountFlagBits sampleCount);

VkPipelineInputAssemblyStateCreateInfo getAssemblyInputState(VkPrimitiveTopology topology, bool restartEnable);

VkPipelineViewportStateCreateInfo getViewportState(const VkViewport& viewport, const VkRect2D& scissors);

VkPipelineVertexInputStateCreateInfo getVertexInputState(const vector<VkVertexInputBindingDescription>& bindings, const vector<VkVertexInputAttributeDescription>& attributes);

#endif //VKRENDERER_VULKANUTILITYFUNCTIONS_H
