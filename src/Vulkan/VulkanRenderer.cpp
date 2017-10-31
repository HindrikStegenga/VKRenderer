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
    initInstance(map);
    renderWindow.set(RenderWindow(800,600, false));
}

void VulkanRenderer::initInstance(const map<string, string> args) {

    string appName      = args.at("appName");
    string engineName   = args.at("engineName");
    bool debug          = args.at("debug") == "true";

    VkApplicationInfo applicationInfo   = {};

    applicationInfo.sType               = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pNext               = nullptr;
    applicationInfo.pApplicationName    = appName.c_str();
    applicationInfo.pEngineName         = appName.c_str();
    applicationInfo.engineVersion       = VK_MAKE_VERSION(1,0,0);
    applicationInfo.applicationVersion  = VK_MAKE_VERSION(1,0,0);
    applicationInfo.apiVersion          = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceCreateInfo     = {};

    instanceCreateInfo.sType                    = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext                    = nullptr;
    instanceCreateInfo.pApplicationInfo         = &applicationInfo;
    instanceCreateInfo.enabledExtensionCount    = 0;
    instanceCreateInfo.ppEnabledExtensionNames  = nullptr;

    if (debug) {
        instanceCreateInfo.enabledLayerCount        = 2;
        instanceCreateInfo.ppEnabledLayerNames      = debugLayers;
    }

    //instanceCreateInfo.enabledLayerCount        = 0;
    //instanceCreateInfo.ppEnabledLayerNames      = nullptr;

    auto result = vkCreateInstance(&instanceCreateInfo, nullptr, instance.reset());
    handleResult(result, "Instance creation failed!");
    Logger::succes("Vulkan instance creation succeeded!");
}

bool VulkanRenderer::processEvents() const {
    return renderWindow.get().pollWindowEvents();
}
