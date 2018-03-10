//
// Created by Hindrik  Stegenga on 09/03/2018.
//

#ifndef VKRENDERER_VKTYPETRAITS_H
#define VKRENDERER_VKTYPETRAITS_H

#include <vulkan/vulkan.h>

#include "../../Utilities/TypeTraits.h"
#include "../../Utilities/Macros.h"

REGISTER_PARSE_TYPE(VkInstance)
REGISTER_PARSE_TYPE(VkDevice)
REGISTER_PARSE_TYPE(VkSurfaceKHR)
REGISTER_PARSE_TYPE(VkSwapchainKHR)
REGISTER_PARSE_TYPE(VkImage)
REGISTER_PARSE_TYPE(VkImageView)
REGISTER_PARSE_TYPE(VkDeviceMemory)
REGISTER_PARSE_TYPE(VkShaderModule)
REGISTER_PARSE_TYPE(VkPipelineLayout)
REGISTER_PARSE_TYPE(VkPipeline)
REGISTER_PARSE_TYPE(VkRenderPass)

#endif //VKRENDERER_VKTYPETRAITS_H
