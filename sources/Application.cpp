//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Application.h"
#include "Utilities/ConfigFileReader.h"
#include "Serializables/ConfigTypes.h"

VulkanSettings readVulkanSettings() {

    std::ifstream file(PATH_CONFIG_FILES + "vulkan.json");
    if (!file.is_open()) {
        Logger::failure("Could not read vulkan settings file!");
    }

    std::stringstream vulkanSettingsBuffer;
    vulkanSettingsBuffer << file.rdbuf();

    auto graphicsSettingsJSON = json::parse(vulkanSettingsBuffer.str());

    VulkanSettings vulkanSettings = graphicsSettingsJSON.get<VulkanSettings>();
    file.close();

    return vulkanSettings;
}


Application::Application(ApplicationSettings applicationSettings, GraphicsSettings graphicsSettings) {

    Logger::log(applicationSettings.applicationName + " " + getVersionString(applicationSettings.applicationVersionMajor, applicationSettings.applicationVersionMinor, applicationSettings.applicationVersionPatch));
    Logger::log(applicationSettings.engineName + " " + getVersionString(applicationSettings.engineVersionMajor, applicationSettings.engineVersionMinor, applicationSettings.engineVersionPatch));

    VulkanSettings vulkanSettings = readVulkanSettings();

    renderWindows.emplace_back(graphicsSettings.resolutionX, graphicsSettings.resolutionY, true);

    RenderWindow& window = renderWindows.back();
    window.setApplicationPointer(this);

    vk_GeneralSettings settings = {};

    settings.applicationSettings = applicationSettings;
    settings.graphicsSettings = graphicsSettings;
    settings.vulkanSettings = vulkanSettings;

    renderer = VulkanRenderer(settings, renderWindows, &RenderWindow::processExtensions);
}

void Application::run() {

    while (!mustStop) {

        std::chrono::nanoseconds deltaTime = internalClock.getDeltaTime();

        bool eventsSucceeded = renderer.processEvents(deltaTime);
        if (!eventsSucceeded) {
            mustStop = true;
        }
        renderer.render();
    }
}

void Application::stop() {
    mustStop = true;
}

void Application::resizeWindow(uint32_t width, uint32_t height, RenderWindow* window) {
    renderer.resizeWindow(width, height, window);
}

string Application::getVersionString(uint32_t major, uint32_t minor, uint32_t patch) {
    using std::to_string;
    return to_string(major) + "." + to_string(minor) + "." + to_string(patch);
}
