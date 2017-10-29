//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Application.h"
#include "Utilities/ConfigFileReader.h"

Application::Application() {

    auto cg = ConfigFileReader();
    cg.parseFile("config/application.cfg");

    applicationName = cg.map().at("name");
    Logger::log(applicationName);

}

void Application::run() {

    while (!mustStop) {

        Logger::log("Loop");

    }
}

void Application::stop() {
    mustStop = true;
}
