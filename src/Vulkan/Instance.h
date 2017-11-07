//
// Created by Hindrik Stegenga on 2-11-17.
//

#ifndef VKRENDERER_VULKANINSTANCE_H
#define VKRENDERER_VULKANINSTANCE_H

#include "Platform/VulkanPlatform.h"


struct InstanceSupportDescription {

    const vector<const char*>& validationLayers;
    const vector<const char*>& extensions;
    const vector<const char*>& debugValidationLayers;
    const vector<const char*>& debugExtensions;
};

class Instance final {
public:
    Instance(const map<string, string>& params, const InstanceSupportDescription& supportDescription);
    ~Instance() = default;

    Instance(const Instance&)   = delete;
    Instance(Instance&&)        = default;

    Instance& operator=(const Instance&)    = delete;
    Instance& operator=(Instance&&)         = default;
private:
    VKUH<VkInstance> instance = VKUH<VkInstance>(vkDestroyInstance);
private:
    static void checkLayersAndExtensionsSupport(const vector<const char*>& validationLayers, const vector<const char*>& extensions);
    static pair<bool, string> checkValidationLayerSupport(const vector<const char*>& layers);
    static pair<bool, string> checkExtensionSupport(const vector<const char*>& validationLayers, const vector<const char*>& extensions);
public:
    VkInstance getHandle() const;
};


#endif //VKRENDERER_VULKANINSTANCE_H
