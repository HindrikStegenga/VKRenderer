#include <iomanip>
#include "Core/Engine.h"
#include "Serializables/VulkanTypes.h"
#include "Core/ECS/Component.h"
#include "Math/Math.h"

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

ApplicationSettings readAppSettings() {

    std::ifstream file(PATH_CONFIG_FILES + "application.json");
    if (!file.is_open()) {
        Logger::failure("Could not read application settings file!");
    }

    std::stringstream appSettingsFileBuffer;
    appSettingsFileBuffer << file.rdbuf();

    auto appSettingsJSON = json::parse(appSettingsFileBuffer.str());

    ApplicationSettings applicationSettings = appSettingsJSON.get<ApplicationSettings>();
    file.close();

    return applicationSettings;
}

GraphicsSettings readGraphicsSettings() {


    std::ifstream file(PATH_CONFIG_FILES + "graphics.json");
    if (!file.is_open()) {
        Logger::failure("Could not read graphics settings file!");
    }

    std::stringstream graphicsSettingsBuffer;
    graphicsSettingsBuffer << file.rdbuf();

    auto graphicsSettingsJSON = json::parse(graphicsSettingsBuffer.str());

    GraphicsSettings graphicsSettings = graphicsSettingsJSON.get<GraphicsSettings>();
    file.close();

    return graphicsSettings;
}

int main() {

//    using namespace Math;
//
//    Matrix4x4f mat(1,2,3,4, 5,6,7,8, 9,54,6,3, 6,7,8,9);
//    Matrix4x4f mat2(6,6,7,8, 2,3,9,0, 1,2,6,1, 7,32,6,1);
//
//
//    json something;
//    something = multiply(mat, mat2);
//
//    std::cout << std::setw(4) << something << std::endl;

    auto applicationSettings = readAppSettings();
    auto graphicsSettings = readGraphicsSettings();

    Engine engine(applicationSettings, graphicsSettings);

    Logger::log(applicationSettings.applicationName + " " + Engine::getVersionString(applicationSettings.applicationVersionMajor, applicationSettings.applicationVersionMinor, applicationSettings.applicationVersionPatch));
    Logger::log(applicationSettings.engineName + " " + Engine::getVersionString(applicationSettings.engineVersionMajor, applicationSettings.engineVersionMinor, applicationSettings.engineVersionPatch));

    VulkanSettings vulkanSettings = readVulkanSettings();

    auto renderWindow = RenderWindow(graphicsSettings.resolutionX, graphicsSettings.resolutionY, true);

    engine.registerRenderWindow(renderWindow);

    vk_GeneralSettings settings = {};

    settings.applicationSettings = applicationSettings;
    settings.graphicsSettings = graphicsSettings;
    settings.vulkanSettings = vulkanSettings;

    EngineSystem* renderSystem = new VulkanRenderSystem(settings, engine.getRenderWindows(), &RenderWindow::processExtensions);

    engine.registerEngineSystem(*renderSystem);

    engine.run();

    return 0;
}