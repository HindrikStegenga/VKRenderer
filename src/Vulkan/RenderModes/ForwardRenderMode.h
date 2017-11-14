//
// Created by hindrik on 12-11-17.
//

#ifndef VKRENDERER_FORWARDRENDERMODE_H
#define VKRENDERER_FORWARDRENDERMODE_H


#include "../Classes/VulkanRenderMode.h"

class ForwardRenderMode : public VulkanRenderMode {
public:
    ForwardRenderMode();
public:
    void render() override;


};


#endif //VKRENDERER_FORWARDRENDERMODE_H
