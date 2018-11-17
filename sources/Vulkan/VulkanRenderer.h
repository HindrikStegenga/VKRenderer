//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VULKANRENDERER_H
#define VKRENDERER_VULKANRENDERER_H

#include "Platform/VulkanPlatform.h"
#include "VulkanRequirements.h"
#include "Instance.h"
#include "PresentDevice.h"
#include "Classes/WindowRenderTarget.h"

using std::chrono::nanoseconds;

typedef vector<const char*> (*ExtensionProcessingFunc)(const vector<const char*>& instanceExtensions);

class VulkanRenderer final {
private:
    Instance                        instance        = Instance();
    PresentDevice                   device          = PresentDevice();
    vector<WindowRenderTarget>      renderTargets   = {};

    nanoseconds                 accumulatedTime     = nanoseconds(0);
    uint64_t                    accumulatedFrames   = 0;

    VkDebugReportCallbackEXT    debugCallbackHandle = VK_NULL_HANDLE;
    VkBool32                    debugEnabled        = VK_FALSE;
public:
    VulkanRenderer() = default;
    explicit VulkanRenderer(string appName, string engineName, vector<RenderWindow>& renderWindows, ExtensionProcessingFunc extensionProcessingFunc, bool debugEnabled = false);
    ~VulkanRenderer();

    VulkanRenderer(const VulkanRenderer&)       = delete;
    VulkanRenderer(VulkanRenderer&&) noexcept   = default;

    VulkanRenderer& operator= (const VulkanRenderer&)       = delete;
    VulkanRenderer& operator= (VulkanRenderer&&) noexcept   = default;
public:
    bool processEvents(std::chrono::nanoseconds deltaTime);
    void render();
    void resizeWindow(uint32_t width, uint32_t height, WindowRenderTarget* renderTarget);
    void resizeWindow(uint32_t width, uint32_t height, RenderWindow* renderWindow);
private:
    VkDevice getDevice();
    void resizeWindow(bool mustResize, WindowRenderTarget* renderTarget);
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
