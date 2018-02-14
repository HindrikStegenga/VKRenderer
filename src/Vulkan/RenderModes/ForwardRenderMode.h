//
// Created by hindrik on 12-11-17.
//

#ifndef VKRENDERER_FORWARDRENDERMODE_H
#define VKRENDERER_FORWARDRENDERMODE_H


#include "../Classes/VulkanRenderMode.h"
#include "VulkanRenderModeCreateInfo.h"

class ForwardRenderMode : public VulkanRenderMode {
public:
    ForwardRenderMode(const ForwardRenderModeCreateInfo& createInfo);
public:
    void render() override;

    void windowHasResized(uint32_t width, uint32_t height) override;

};


#endif //VKRENDERER_FORWARDRENDERMODE_H
