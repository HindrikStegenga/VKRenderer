//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Application.h"
#include "Utilities/ConfigFileReader.h"
#include "Serializables/ConfigTypes.h"

Application::Application() {

    ApplicationSettings applicationSettings;

    std::ifstream file(PATH_CONFIG_FILES + "application.json");
    if (!file.is_open()) {
        Logger::log(PATH_CONFIG_FILES + "application.json");
        Logger::failure("Could not read application settings file!");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    auto json_rep = json::parse(buffer.str());

    applicationSettings = json_rep.get<ApplicationSettings>();


    auto cg = ConfigFileReader(true);
    cg.parseFile("config/application.cfg");

    applicationName = cg.map().at("name");
    auto debug = cg.map().at("debug");

    bool isDebug = debug == "true";

    string engineName = cg.map().at("engineName");

    Logger::log(applicationName);
    Logger::log(engineName);

    renderWindows.push_back(RenderWindow(800,480, true));
    RenderWindow& window = renderWindows.back();
    window.setApplicationPointer(this);

    renderer = VulkanRenderer(applicationName, engineName, renderWindows, &RenderWindow::processExtensions, isDebug);
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
