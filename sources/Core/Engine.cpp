#include <utility>

//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Engine.h"
#include "../Utilities/ConfigFileReader.h"
#include "../Serializables/ConfigTypes.h"

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


Engine::Engine(ApplicationSettings applicationSettings, GraphicsSettings graphicsSettings)
    : applicationSettings(std::move(applicationSettings)), graphicsSettings(graphicsSettings)
    {

    setupEngineSystems();
}

void Engine::run() {

    //Fixed update thread
    std::thread fixedUpdateThread([this](){

        while (!mustStop) {

            auto start = std::chrono::steady_clock::now();

            for(const auto& systemPtr : engineSystems) {
                if(!systemPtr->getSystemStatus()){
                    mustStop = true;
                }
                if(mustStop)
                    break;
                systemPtr->fixedUpdate();
            }

            auto delta = std::chrono::steady_clock::now() - start;
            auto sleepTime = std::chrono::milliseconds(20) - delta;

            if(sleepTime > nanoseconds(0))
            std::this_thread::sleep_for(sleepTime);
        }
    });

    //Current main thread
    while (!mustStop) {

        std::chrono::nanoseconds deltaTime = internalClock.getDeltaTime();

        for(const auto& systemPtr : engineSystems) {
            EngineSystem& system = *systemPtr;

            system.update(deltaTime);
        }
    }
    fixedUpdateThread.join();
}

void Engine::stop() {
    mustStop = true;
}

void Engine::windowHasResized(uint32_t width, uint32_t height, RenderWindow *window) {

    Logger::warn("windowHasResized has not been implemented!");

    //for(auto& system : engineSystems)
        //system.resizeWindow(width, height, window);
}

string Engine::getVersionString(uint32_t major, uint32_t minor, uint32_t patch) {
    using std::to_string;
    return to_string(major) + "." + to_string(minor) + "." + to_string(patch);
}

void Engine::setupEngineSystems() {

    Logger::log(applicationSettings.applicationName + " " + getVersionString(applicationSettings.applicationVersionMajor, applicationSettings.applicationVersionMinor, applicationSettings.applicationVersionPatch));
    Logger::log(applicationSettings.engineName + " " + getVersionString(applicationSettings.engineVersionMajor, applicationSettings.engineVersionMinor, applicationSettings.engineVersionPatch));

    VulkanSettings vulkanSettings = readVulkanSettings();

    renderWindows.emplace_back(graphicsSettings.resolutionX, graphicsSettings.resolutionY, true);

    RenderWindow& window = renderWindows.back();
    window.setEnginePointer(this);

    vk_GeneralSettings settings = {};

    settings.applicationSettings = applicationSettings;
    settings.graphicsSettings = graphicsSettings;
    settings.vulkanSettings = vulkanSettings;

    EngineSystem* renderSystem = new VulkanRenderSystem(settings, renderWindows, &RenderWindow::processExtensions);
    engineSystems.emplace_back(renderSystem);
}
