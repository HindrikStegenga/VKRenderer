//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Application.h"
#include "Utilities/ConfigFileReader.h"
#include "Serializables/ConfigTypes.h"

Application::Application(ApplicationSettings applicationSettings, GraphicsSettings graphicsSettings) {

    Logger::log(applicationSettings.applicationName);
    Logger::log(applicationSettings.engineName);

    renderWindows.emplace_back(graphicsSettings.resolutionX, graphicsSettings.resolutionY, true);

    RenderWindow& window = renderWindows.back();
    window.setApplicationPointer(this);

    renderer = VulkanRenderer(applicationName, applicationSettings.applicationName, renderWindows, &RenderWindow::processExtensions, applicationSettings.debugMode);
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
