//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VULKANRENDERER_H
#define VKRENDERER_VULKANRENDERER_H

#include "Platform/VulkanPlatform.h"
#include "VulkanRequirements.h"
#include "Platform/RenderWindow.h"
#include "../Utilities/Nullable.h"
#include "Instance.h"
#include "PresentDevice.h"
#include "Classes/VulkanRenderMode.h"

class VulkanRenderer final {
public:
    explicit VulkanRenderer(string appName, string engineName, bool debugEnabled = false);
    ~VulkanRenderer();

    VulkanRenderer(const VulkanRenderer&)       = delete;
    VulkanRenderer(VulkanRenderer&&) noexcept   = default;

    VulkanRenderer& operator= (const VulkanRenderer&)       = delete;
    VulkanRenderer& operator= (VulkanRenderer&&) noexcept   = default;
private:
    Nullable<Instance>              instance;
    Nullable<RenderWindow>          renderWindow;
    VkDebugReportCallbackEXT        debugCallbackHandle;
    VkBool32                        debugEnabled = VK_FALSE;
    Nullable<PresentDevice>         device;
    Nullable<Swapchain>             swapchain;
    unique_ptr<VulkanRenderMode>    renderMode = nullptr;
public:
    bool processEvents();
    void render();
    void resizeWindow(uint32_t width, uint32_t height);
private:
    VkDevice getDevice();
    void resizeWindow(bool mustResize);
    void setupDebugCallback();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags,
                                                        VkDebugReportObjectTypeEXT objType,
                                                        uint64_t obj,
                                                        size_t location,
                                                        int32_t code,
                                                        const char* layerPrefix,
                                                        const char* msg,
                                                        void* userData);


};

inline VkResult createDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                                      const VkAllocationCallbacks *pAllocator, VkDebugReportCallbackEXT *pCallback) {
    auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pCallback);
    }
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

inline void destroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback,
                                          const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr) {
        func(instance, callback, pAllocator);
    }
}

#endif //VKRENDERER_VULKANRENDERER_H
