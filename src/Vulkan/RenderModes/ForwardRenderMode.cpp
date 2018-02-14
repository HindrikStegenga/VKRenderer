//
// Created by hindrik on 12-11-17.
//

#include "ForwardRenderMode.h"

ForwardRenderMode::ForwardRenderMode(const ForwardRenderModeCreateInfo &createInfo) : VulkanRenderMode({ "Forward", createInfo.deviceInfo, createInfo.surface })
{

}

void ForwardRenderMode::windowHasResized(uint32_t width, uint32_t height)
{

}

void ForwardRenderMode::render() {

}