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
#include "../../Serializables/ConfigTypes.h"
#include "../../Core/ECS/EngineSystem.h"

using std::chrono::nanoseconds;

typedef vector<const char*> (*ExtensionProcessingFunc)(const vector<const char*>& instanceExtensions);

class VulkanRenderSystem : public EngineSystem {
private:
    Instance                        instance        = Instance();
    PresentDevice                   device          = PresentDevice();
    vector<WindowRenderTarget>      renderTargets   = {};

    nanoseconds                 accumulatedTime     = nanoseconds(0);
    nanoseconds                 latestDeltaTime     = nanoseconds(0);
    uint64_t                    accumulatedFrames   = 0;

    VkDebugReportCallbackEXT    debugCallbackHandle = VK_NULL_HANDLE;
    VkBool32                    debugEnabled        = VK_FALSE;
public:
    explicit VulkanRenderSystem(Engine* engine, vk_GeneralSettings settings, ExtensionProcessingFunc extensionProcessingFunc);
    ~VulkanRenderSystem() override;

    VulkanRenderSystem(const VulkanRenderSystem&)                   = delete;
    VulkanRenderSystem& operator= (const VulkanRenderSystem&)       = delete;
public:
    void resizeWindow(uint32_t width, uint32_t height, WindowRenderTarget* renderTarget);
    void windowHasResized(uint32_t width, uint32_t height, RenderWindow* renderWindow) override;

    void update(std::chrono::nanoseconds deltaTime) override;
    bool fixedUpdate() override;
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
