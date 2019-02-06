#include "Engine.h"
#include "Serializables/VulkanTypes.h"
#include "Serializables/GenericTypes.h"

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

    Engine app(readAppSettings(), readGraphicsSettings());
    app.run();

    return 0;
}