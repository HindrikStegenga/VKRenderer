//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "VulkanRenderer.h"
#include "../Utilities/ConfigFileReader.h"

VulkanRenderer::VulkanRenderer(string appName, bool debugEnabled) {

    auto configReader = ConfigFileReader();

    configReader.parseFile("config/vulkan.cfg");

    auto map = configReader.map();
    map.insert(std::make_pair("appName",appName));
    map.insert(std::make_pair("debug", debugEnabled ? "true" : "false"));
    renderWindow.set(RenderWindow(800,600, false));

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

    auto processedExtensions = renderWindow.get().processExtensions(extensions);

    VulkanInstanceSupportDescription supportDescription { layers, processedExtensions, debugLayers, debugExtensions };

    instance.set(VulkanInstance(map, supportDescription));
}

bool VulkanRenderer::processEvents() const {
    return renderWindow.get().pollWindowEvents();
}
