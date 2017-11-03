//
// Created by Hindrik Stegenga on 2-11-17.
//

#ifndef VKRENDERER_VULKANINSTANCE_H
#define VKRENDERER_VULKANINSTANCE_H

#include "VulkanPlatform.h"

struct VulkanInstanceSupportDescription {

    const vector<const char*>& validationLayers;
    const vector<const char*>& extensions;
    const vector<const char*>& debugValidationLayers;
    const vector<const char*>& debugExtensions;
};

class VulkanInstance final {
public:
    VulkanInstance(const map<string, string>& params, const VulkanInstanceSupportDescription& instanceSupportDescription);
    ~VulkanInstance() = default;

    VulkanInstance(const VulkanInstance&)   = delete;
    VulkanInstance(VulkanInstance&&)        = default;

    VulkanInstance& operator=(const VulkanInstance&)    = delete;
    VulkanInstance& operator=(VulkanInstance&&)         = default;
private:
    VKUH<VkInstance> instance = VKUH<VkInstance>(vkDestroyInstance);
private:
    static void checkLayersAndExtensionsSupport(const vector<const char*>& validationLayers, const vector<const char*>& extensions);
    static pair<bool, string> checkValidationLayerSupport(const vector<const char*>& layers);
    static pair<bool, string> checkExtensionSupport(const vector<const char*>& validationLayers, const vector<const char*>& extensions);

};


#endif //VKRENDERER_VULKANINSTANCE_H
