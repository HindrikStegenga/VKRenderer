//
// Created by Hindrik Stegenga on 3-11-17.
//

#include "UtilityFunctions.h"

auto operator<<(ostream& o, VkPhysicalDeviceType& t) -> ostream&
{
    switch(t)
    {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            o << "Other";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            o << "Integrated GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            o << "Discrete GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            o << "Virtual GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            o << "CPU";
            break;
        default:
            o << t;
            break;
    }
    return o;
}

auto operator<<(ostream& o, VkPhysicalDeviceProperties& p) -> ostream&
{

    string vendorName = std::to_string(p.vendorID);

    o << "---------------DEVICE---------------" << std::endl;

    o << "Name: "               << p.deviceName     << std::endl;
    o << "Type: "               << p.deviceType     << std::endl;
    o << "Vendor: "             << vendorName       << std::endl;
    o << "PresentDevice ID: "          << p.deviceID       << std::endl;
    o << "API Version: "        << p.apiVersion     << std::endl;
    o << "Driver Version: "     << p.driverVersion  << std::endl;

    o << "------------------------------------"     << std::endl;

    return o;
}

auto operator<<(ostream &o, VkQueueFamilyProperties p) -> ostream&
{

    o << "------------QUEUE_FAMILY------------" << std::endl;

    o << "Queue count: " << p.queueCount << std::endl;

    o << "------------------------------------" << std::endl;
    o << "Graphics: "               << (static_cast<bool>(p.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? "Yes" : "No")          << std::endl;
    o << "Compute: "                << (static_cast<bool>(p.queueFlags & VK_QUEUE_COMPUTE_BIT)  ? "Yes" : "No")          << std::endl;
    o << "Transfer: "               << (static_cast<bool>(p.queueFlags & VK_QUEUE_TRANSFER_BIT) ? "Yes" : "No")          << std::endl;
    o << "Sparse binding: "         << (static_cast<bool>(p.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? "Yes" : "No")    << std::endl;

    o << "------------------------------------" << std::endl;

    return o;
}

auto operator<<(ostream &o, VkExtensionProperties p) -> ostream&
{

    o << "------------------------------EXTENSION PROPERTIES------------------------------" << std::endl;
    o << "Extension name: "         << p.extensionName  << std::endl;
    o << "Extension spec version: " << p.specVersion    << std::endl;
    o << "------------------------------------------------------------------------------" << std::endl;

    return o;
}

uint32_t deviceTypePriority(VkPhysicalDeviceType deviceType)
{
    switch (deviceType) {
        case VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE:
            return 0;
        case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:
            return 1;
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return 2;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return 3;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return 4;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return 5;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return 6;
    }
}

VkComponentMapping defaultComponentMapping() {

    VkComponentMapping mapping = {};
    mapping.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    mapping.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    mapping.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    mapping.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    return mapping;

}

VkFormat chooseSupportedFormat(VkPhysicalDevice physicalDevice, const vector<VkFormat> &availableFormats, VkImageTiling tiling, VkFormatFeatureFlags featureFlags) {

    for(const auto format : availableFormats) {

        VkFormatProperties props = {};
        vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

        if (tiling == VK_IMAGE_TILING_OPTIMAL && ((props.optimalTilingFeatures & featureFlags) == featureFlags)) {
            return format;

        } else if(tiling == VK_IMAGE_TILING_LINEAR && ((props.linearTilingFeatures & featureFlags) == featureFlags)) {
            return format;
        }
    }

    Logger::failure("Could not find an appropriate format!");
    return VK_FORMAT_UNDEFINED;
}

VkImageSubresourceRange defaultImageSubresourceRange(VkImageAspectFlags aspectFlags) {

    VkImageSubresourceRange range   = {};
    range.layerCount                = 1;
    range.baseArrayLayer            = 0;
    range.levelCount                = 1;
    range.baseMipLevel              = 0;
    range.aspectMask                = aspectFlags;

    return range;
}

uint32_t chooseMemoryTypeIndex(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags props) {

    VkPhysicalDeviceMemoryProperties memProperties = {};
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; ++i) {
        if ((typeFilter & (1 << i)) && ((memProperties.memoryTypes[i].propertyFlags & props) == props)) {
            return i;
        }
    }

    Logger::failure("Could not find appropriate memory type!");
    return std::numeric_limits<uint32_t>::max();
}

VkPipelineInputAssemblyStateCreateInfo getAssemblyInputState(VkPrimitiveTopology topology, bool restartEnable) {

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
    inputAssemblyStateCreateInfo.sType                                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCreateInfo.pNext                                  = nullptr;
    inputAssemblyStateCreateInfo.topology                               = topology;
    inputAssemblyStateCreateInfo.primitiveRestartEnable                 = restartEnable ? VK_TRUE : VK_FALSE;
    inputAssemblyStateCreateInfo.flags                                  = {};

    return inputAssemblyStateCreateInfo;
}

VkPipelineViewportStateCreateInfo getViewportState(const VkViewport &viewport, const VkRect2D &scissor) {

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo   = {};
    viewportStateCreateInfo.sType                               = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCreateInfo.pNext                               = nullptr;
    viewportStateCreateInfo.viewportCount                       = 1;
    viewportStateCreateInfo.pViewports                          = &viewport;
    viewportStateCreateInfo.scissorCount                        = 1;
    viewportStateCreateInfo.pScissors                           = &scissor;

    return viewportStateCreateInfo;
}

VkCommandPoolCreateInfo getCommandPoolInfo(uint32_t familyIndex, bool individualReset, bool isTransient) {

    VkCommandPoolCreateInfo commandPoolCreateInfo = {};

    VkCommandPoolCreateFlags bits = {};

    if(isTransient)
        bits |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    if (individualReset)
        bits |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.pNext = nullptr;
    commandPoolCreateInfo.flags = bits;
    commandPoolCreateInfo.queueFamilyIndex = familyIndex;

    return commandPoolCreateInfo;
}

VkCommandBufferBeginInfo getCommandBufferBeginInfoPrimary(PrimaryCommandBufferUsage usage) {

    VkCommandBufferBeginInfo beginInfo  = {};
    beginInfo.sType                     = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.pNext                     = nullptr;
    beginInfo.flags                     = static_cast<VkCommandBufferUsageFlags>(usage);
    beginInfo.pInheritanceInfo          = nullptr;

    return beginInfo;
}

VkCommandBufferAllocateInfo getCommandBufferAllocateInfo(VkCommandPool pool, uint32_t bufferCount, VkCommandBufferLevel level) {

    VkCommandBufferAllocateInfo allocateInfo    = {};
    allocateInfo.sType                          = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.pNext                          = nullptr;
    allocateInfo.commandPool                    = pool;
    allocateInfo.commandBufferCount             = bufferCount;
    allocateInfo.level                          = level;

    return allocateInfo;
}

VkPipelineMultisampleStateCreateInfo getMultisampleState(VkSampleCountFlagBits sampleCount) {

    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
    multisampleStateCreateInfo.sType                                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.pNext                                = nullptr;
    multisampleStateCreateInfo.flags                                = {};
    multisampleStateCreateInfo.alphaToCoverageEnable                = VK_FALSE;
    multisampleStateCreateInfo.alphaToOneEnable                     = VK_FALSE;
    multisampleStateCreateInfo.sampleShadingEnable                  = VK_FALSE;
    multisampleStateCreateInfo.minSampleShading                     = 1.0f;
    multisampleStateCreateInfo.pSampleMask                          = nullptr;
    multisampleStateCreateInfo.rasterizationSamples                 = sampleCount;

    return multisampleStateCreateInfo;
}
