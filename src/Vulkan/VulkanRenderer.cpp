//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "VulkanRenderer.h"
#include "../Utilities/ConfigFileReader.h"

VulkanRenderer::VulkanRenderer(string appName, string engineName,  bool debugEnabled) {

    auto configReader = ConfigFileReader();

    configReader.parseFile("config/vulkan.cfg");

    auto map = configReader.map();

    map.insert(std::make_pair("appName",appName));
    map.insert(std::make_pair("engineName", engineName));
    map.insert(std::make_pair("debug", debugEnabled ? "true" : "false"));

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

    DeviceSupportDescription deviceSupportDescription { dExtensions, ddExtensions, requiredDeviceFeatures };

    device.set(PresentDevice(instance.get().getHandle(), map, deviceSupportDescription));
}

bool VulkanRenderer::processEvents() const {
    return renderWindow.get().pollWindowEvents();
}
