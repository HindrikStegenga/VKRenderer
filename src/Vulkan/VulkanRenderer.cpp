//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "VulkanRenderer.h"
#include "../Utilities/ConfigFileReader.h"
#include "RenderModes/ForwardRenderMode.h"
#include "RenderModes/DeferredRenderMode.h"

VulkanRenderer::VulkanRenderer(string appName, string engineName,  bool debugEnabled) : debugEnabled(debugEnabled ? VK_TRUE : VK_FALSE) {

    auto configReader = ConfigFileReader();

    configReader.parseFile("config/vulkan.cfg");

    auto map = configReader.map();

    map.insert(std::make_pair("appName",appName));
    map.insert(std::make_pair("engineName", engineName));

    map.insert(std::make_pair("debug", this->debugEnabled == VK_TRUE ? "true" : "false"));

    uint32_t width, height;
    width = static_cast<uint32_t>(std::stoi(map.at("width")));
    height = static_cast<uint32_t>(std::stoi(map.at("height")));

    renderWindow.set(RenderWindow(width, height, false));

    vector<const char*> extensions;
    for (auto instanceExtension : instanceExtensions) {
        extensions.push_back(instanceExtension);
    }
    vector<const char*> layers;
    for (auto instanceLayer : instanceLayers) {
        layers.push_back(instanceLayer);
    }
    vector<const char*> debugExtensions;
    for (auto instanceExtension : debugInstanceExtensions) {
        debugExtensions.push_back(instanceExtension);
    }
    vector<const char*> debugLayers;
    for (auto instanceLayer : debugInstanceLayers) {
        debugLayers.push_back(instanceLayer);
    }

    vector<const char*> dExtensions;
    for (auto extension : deviceExtensions) {
        dExtensions.push_back(extension);
    }

    vector<const char*> ddExtensions;
    for (auto extension : debugDeviceExtensions) {
        ddExtensions.push_back(extension);
    }

    auto processedExtensions = renderWindow.get().processExtensions(extensions);

    InstanceSupportDescription supportDescription { layers, processedExtensions, debugLayers, debugExtensions };

    instance.set(Instance(map, supportDescription));

    if (this->debugEnabled == VK_TRUE) {
        setupDebugCallback();
    }

    VkSurfaceKHR surface = renderWindow.getMutable().getWindowSurface(instance.getMutable().getHandle());

    DeviceSupportDescription deviceSupportDescription { dExtensions, ddExtensions, requiredDeviceFeatures, surface };

    device.set(PresentDevice(instance.get().getHandle(), map, deviceSupportDescription));


    const string renderMode = configReader.map().at("renderMode");
    if (renderMode == string("Forward")) {
        this->renderMode = std::make_unique<ForwardRenderMode>(device.getMutable().getDevice(), device.getMutable().getPhysicalDevice().physicalDevice,device.getMutable().getSurface());
    } else if (renderMode == string("Deferred")) {
        this->renderMode = std::make_unique<DeferredRenderMode>(device.getMutable().getDevice(), device.getMutable().getPhysicalDevice().physicalDevice,device.getMutable().getSurface());
    } else {
        Logger::error("Could not find appropriate renderMode!");
    }

}

bool VulkanRenderer::processEvents() const {
    return renderWindow.get().pollWindowEvents();
}

VkBool32 VulkanRenderer::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
                                       size_t location, int32_t code, const char *layerPrefix, const char *msg,
                                       void *userData)
{
    Logger::warn("Validation layer: " + string(msg));
    return VK_FALSE;
}

void VulkanRenderer::setupDebugCallback()
{
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType        = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.pNext        = nullptr;
    createInfo.flags        = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback  = debugCallback;
    createInfo.pUserData    = nullptr;

    VkResult result = createDebugReportCallbackEXT(instance.get().getHandle(), &createInfo, nullptr, &debugCallbackHandle);
    if (result != VK_SUCCESS) {
        Logger::warn("Debug callback is not enabled! Reason: " + mapVkResult(result));
        debugEnabled = VK_FALSE;
    }
    else {
        Logger::succes("Debug callback enabled!");
    }
}

VulkanRenderer::~VulkanRenderer()
{
    if (debugEnabled == VK_TRUE) {
        destroyDebugReportCallbackEXT(instance.get().getHandle(), debugCallbackHandle, nullptr);
    }
}

void VulkanRenderer::render() {
    renderMode->render();
}
