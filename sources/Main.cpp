#include <iomanip>
#include "Core/Engine.h"
#include "Serializables/VulkanTypes.h"
#include "Core/ECS/Component.h"
#include "Math/Math.h"
#include "Utilities/JSONLoader.h"

int main() {

    auto applicationSettings = loadJSONFile<ApplicationSettings>(PATH_CONFIG_FILES + "application.json");
    auto graphicsSettings = loadJSONFile<GraphicsSettings>(PATH_CONFIG_FILES + "graphics.json");
    auto vulkanSettings = loadJSONFile<VulkanSettings>(PATH_CONFIG_FILES + "vulkan.json");

    Engine engine(applicationSettings, graphicsSettings);

    Logger::log(applicationSettings.applicationName + " " + Engine::getVersionString(applicationSettings.applicationVersionMajor, applicationSettings.applicationVersionMinor, applicationSettings.applicationVersionPatch));
    Logger::log(applicationSettings.engineName + " " + Engine::getVersionString(applicationSettings.engineVersionMajor, applicationSettings.engineVersionMinor, applicationSettings.engineVersionPatch));

    engine.registerRenderWindow(graphicsSettings.resolutionX, graphicsSettings.resolutionY, true);

    vk_GeneralSettings settings = {};

    settings.applicationSettings = applicationSettings;
    settings.graphicsSettings = graphicsSettings;
    settings.vulkanSettings = vulkanSettings;

    engine.registerEngineSystem<VulkanRenderSystem>(&engine, settings, &RenderWindow::processExtensions);

    engine.run();

    return 0;
}