//
// Created by Hindrik Stegenga on 6-11-17.
//

#include <cstring>
#include "PhysicalDevice.h"

PhysicalDevice::PhysicalDevice(VkPhysicalDevice physicalDevice) : physicalDevice(physicalDevice)
{
    vkGetPhysicalDeviceProperties(physicalDevice, &properties);
    vkGetPhysicalDeviceFeatures  (physicalDevice, &features);
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
    extensionProperties.resize(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensionProperties.data());
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
    queueFamilies = getQueueFamilies(physicalDevice);
}

bool PhysicalDevice::meetsRequiredPhysicalDeviceFeatures(const VkPhysicalDeviceFeatures& features, const VkPhysicalDeviceFeatures& requirements)
{
    if(requirements.robustBufferAccess == VK_TRUE && features.robustBufferAccess == VK_FALSE) { return false; }
    if(requirements.fullDrawIndexUint32 == VK_TRUE && features.fullDrawIndexUint32 == VK_FALSE) { return false; }
    if(requirements.imageCubeArray == VK_TRUE && features.imageCubeArray == VK_FALSE) { return false; }
    if(requirements.independentBlend == VK_TRUE && features.independentBlend == VK_FALSE) { return false; }
    if(requirements.geometryShader == VK_TRUE && features.geometryShader == VK_FALSE) { return false; }
    if(requirements.tessellationShader == VK_TRUE && features.tessellationShader == VK_FALSE) { return false; }
    if(requirements.sampleRateShading == VK_TRUE && features.sampleRateShading == VK_FALSE) { return false; }
    if(requirements.dualSrcBlend == VK_TRUE && features.dualSrcBlend == VK_FALSE) { return false; }
    if(requirements.logicOp == VK_TRUE && features.logicOp == VK_FALSE) { return false; }
    if(requirements.multiDrawIndirect == VK_TRUE && features.multiDrawIndirect == VK_FALSE) { return false; }
    if(requirements.drawIndirectFirstInstance == VK_TRUE && features.drawIndirectFirstInstance == VK_FALSE) { return false; }
    if(requirements.depthClamp == VK_TRUE && features.depthClamp == VK_FALSE) { return false; }
    if(requirements.depthBiasClamp == VK_TRUE && features.depthBiasClamp == VK_FALSE) { return false; }
    if(requirements.fillModeNonSolid == VK_TRUE && features.fillModeNonSolid == VK_FALSE) { return false; }
    if(requirements.depthBounds == VK_TRUE && features.depthBounds == VK_FALSE) { return false; }
    if(requirements.wideLines == VK_TRUE && features.wideLines == VK_FALSE) { return false; }
    if(requirements.largePoints == VK_TRUE && features.largePoints == VK_FALSE) { return false; }
    if(requirements.alphaToOne == VK_TRUE && features.alphaToOne == VK_FALSE) { return false; }
    if(requirements.multiViewport == VK_TRUE && features.multiViewport == VK_FALSE) { return false; }
    if(requirements.samplerAnisotropy == VK_TRUE && features.samplerAnisotropy == VK_FALSE) { return false; }
    if(requirements.textureCompressionETC2 == VK_TRUE && features.textureCompressionETC2 == VK_FALSE) { return false; }
    if(requirements.textureCompressionASTC_LDR == VK_TRUE && features.textureCompressionASTC_LDR == VK_FALSE) { return false; }
    if(requirements.textureCompressionBC == VK_TRUE && features.textureCompressionBC == VK_FALSE) { return false; }
    if(requirements.occlusionQueryPrecise == VK_TRUE && features.occlusionQueryPrecise == VK_FALSE) { return false; }
    if(requirements.pipelineStatisticsQuery == VK_TRUE && features.pipelineStatisticsQuery == VK_FALSE) { return false; }
    if(requirements.vertexPipelineStoresAndAtomics == VK_TRUE && features.vertexPipelineStoresAndAtomics == VK_FALSE) { return false; }
    if(requirements.fragmentStoresAndAtomics == VK_TRUE && features.fragmentStoresAndAtomics == VK_FALSE) { return false; }
    if(requirements.shaderTessellationAndGeometryPointSize == VK_TRUE && features.shaderTessellationAndGeometryPointSize == VK_FALSE) { return false; }
    if(requirements.shaderImageGatherExtended == VK_TRUE && features.shaderImageGatherExtended == VK_FALSE) { return false; }
    if(requirements.shaderStorageImageExtendedFormats == VK_TRUE && features.shaderStorageImageExtendedFormats == VK_FALSE) { return false; }
    if(requirements.shaderStorageImageMultisample == VK_TRUE && features.shaderStorageImageMultisample == VK_FALSE) { return false; }
    if(requirements.shaderStorageImageReadWithoutFormat == VK_TRUE && features.shaderStorageImageReadWithoutFormat == VK_FALSE) { return false; }
    if(requirements.shaderStorageImageWriteWithoutFormat == VK_TRUE && features.shaderStorageImageWriteWithoutFormat == VK_FALSE) { return false; }
    if(requirements.shaderUniformBufferArrayDynamicIndexing == VK_TRUE && features.shaderUniformBufferArrayDynamicIndexing == VK_FALSE) { return false; }
    if(requirements.shaderSampledImageArrayDynamicIndexing == VK_TRUE && features.shaderSampledImageArrayDynamicIndexing == VK_FALSE) { return false; }
    if(requirements.shaderStorageBufferArrayDynamicIndexing == VK_TRUE && features.shaderStorageBufferArrayDynamicIndexing == VK_FALSE) { return false; }
    if(requirements.shaderStorageImageArrayDynamicIndexing == VK_TRUE && features.shaderStorageImageArrayDynamicIndexing == VK_FALSE) { return false; }
    if(requirements.shaderClipDistance == VK_TRUE && features.shaderClipDistance == VK_FALSE) { return false; }
    if(requirements.shaderCullDistance == VK_TRUE && features.shaderCullDistance == VK_FALSE) { return false; }
    if(requirements.shaderFloat64 == VK_TRUE && features.shaderFloat64 == VK_FALSE) { return false; }
    if(requirements.shaderInt64 == VK_TRUE && features.shaderInt64 == VK_FALSE) { return false; }
    if(requirements.shaderInt16 == VK_TRUE && features.shaderInt16 == VK_FALSE) { return false; }
    if(requirements.shaderResourceResidency == VK_TRUE && features.shaderResourceResidency == VK_FALSE) { return false; }
    if(requirements.shaderResourceMinLod == VK_TRUE && features.shaderResourceMinLod == VK_FALSE) { return false; }
    if(requirements.sparseBinding == VK_TRUE && features.sparseBinding == VK_FALSE) { return false; }
    if(requirements.sparseResidencyBuffer == VK_TRUE && features.sparseResidencyBuffer == VK_FALSE) { return false; }
    if(requirements.sparseResidencyImage2D == VK_TRUE && features.sparseResidencyImage2D == VK_FALSE) { return false; }
    if(requirements.sparseResidencyImage3D == VK_TRUE && features.sparseResidencyImage3D == VK_FALSE) { return false; }
    if(requirements.sparseResidency2Samples == VK_TRUE && features.sparseResidency2Samples == VK_FALSE) { return false; }
    if(requirements.sparseResidency4Samples == VK_TRUE && features.sparseResidency4Samples == VK_FALSE) { return false; }
    if(requirements.sparseResidency8Samples == VK_TRUE && features.sparseResidency8Samples == VK_FALSE) { return false; }
    if(requirements.sparseResidency16Samples == VK_TRUE && features.sparseResidency16Samples == VK_FALSE) { return false; }
    if(requirements.sparseResidencyAliased == VK_TRUE && features.sparseResidencyAliased == VK_FALSE) { return false; }
    if(requirements.variableMultisampleRate == VK_TRUE && features.variableMultisampleRate == VK_FALSE) { return false; }
    return !(requirements.inheritedQueries == VK_TRUE && features.inheritedQueries == VK_FALSE);
}

pair<bool, string> PhysicalDevice::meetsRequiredExtensions(const vector<VkExtensionProperties>& extensions, const vector<const char *>& requirements)
{
    for (const char* extensionName : requirements)
    {
        for (const auto &extensionProps : extensions)
        {
            if (strcmp(extensionName, extensionProps.extensionName) == 0)
            {
                return make_pair(true, "SUCCESS");
            }
        }
        return make_pair(false, string(extensionName));
    }
    return make_pair(true, "SUCCESS");
}

pair<bool, vk_QueueFamily> PhysicalDevice::isSuitableAndReturnPresentQueue(const vector<const char *> &extensionNames,
                                                                          const VkPhysicalDeviceFeatures &requiredFeatures,
                                                                          VkSurfaceKHR surface)
{
    auto pair = meetsRequiredExtensions(extensionProperties, extensionNames);
    if (!pair.first) {
        Logger::warn(string("Device extension not supported for device: " + pair.second));
        return make_pair(false, vk_QueueFamily{});
    }
    bool support = meetsRequiredPhysicalDeviceFeatures(features, requiredFeatures);
    if (!support) { return make_pair(false, vk_QueueFamily{}); }
    support = meetsRequiredQueueTypes(queueFamilies);
    if (!support) { return make_pair(false, vk_QueueFamily{}); }
    auto presentQueue = meetsRequiredSurfaceSupport(physicalDevice, surface, queueFamilies);
    return presentQueue;
}

vector<vk_QueueFamily> PhysicalDevice::getQueueFamilies(VkPhysicalDevice physicalDevice)
{
    vector<vk_QueueFamily> queueFamilies;
    uint32_t qfCount = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &qfCount, nullptr);
    vector<VkQueueFamilyProperties> queueFamilyProperties(qfCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &qfCount, queueFamilyProperties.data());
    for (uint32_t i = 0; i < queueFamilyProperties.size(); ++i) {
        queueFamilies.push_back(vk_QueueFamily { i, queueFamilyProperties[i] });
    }
    return queueFamilies;
}

bool PhysicalDevice::meetsRequiredQueueTypes(const vector<vk_QueueFamily> &queueFamilies)
{
    return findFirstGraphicsComputeQueueFamily(queueFamilies).first;
}

pair<bool, vk_QueueFamily> PhysicalDevice::findFirstGraphicsComputeQueueFamily(const vector<vk_QueueFamily> &queueFamilies)
{
    for (const auto& qf : queueFamilies) {
        if (qf.queueFamilyProperties.queueCount > 0 &&
                static_cast<bool>(qf.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
                static_cast<bool>(qf.queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT))
        {
            return make_pair(true, qf);
        }
    }
    return make_pair(false, vk_QueueFamily {});
}

pair<bool, vk_QueueFamily> PhysicalDevice::meetsRequiredSurfaceSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
                                            const vector<vk_QueueFamily> &queueFamilies)
{
    for (const auto& qf : queueFamilies) {
        if (qf.queueFamilyProperties.queueCount > 0 &&
            static_cast<bool>(qf.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
            static_cast<bool>(qf.queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT))
        {
            VkBool32 presentSupport = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, qf.queueFamilyIndex, surface, &presentSupport);
            if (presentSupport == VK_TRUE) {
                return make_pair(true, qf);
            }
        }
    }
    return make_pair(false, vk_QueueFamily {});
}
