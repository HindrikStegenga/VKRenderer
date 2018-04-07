//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Application.h"
#include "Utilities/ConfigFileReader.h"

Application::Application() {

    auto cg = ConfigFileReader(true);
    cg.parseFile("config/application.cfg");

    applicationName = cg.map().at("name");
    auto debug = cg.map().at("debug");

    bool isDebug = debug == "true";

    string engineName = cg.map().at("engineName");

    Logger::log(applicationName);
    Logger::log(engineName);

    renderer.set(VulkanRenderer(applicationName, engineName, isDebug));
}

void Application::run() {

    while (!mustStop) {
        bool eventsSucceeded = renderer.get().processEvents();
        if (!eventsSucceeded) {
            mustStop = true;
        }
        renderer.get().render();
    }
}

void Application::stop() {
    mustStop = true;
}
