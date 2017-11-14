//
// Created by hindrik on 12-11-17.
//

#include "VulkanRenderMode.h"

VulkanRenderMode::VulkanRenderMode(string renderModeName) : name(std::move(renderModeName)){

    Logger::log("Initialized rendermode: " + name);

}
