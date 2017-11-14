//
// Created by hindrik on 14-11-17.
//

#ifndef VKRENDERER_DEFERREDRENDERMODE_H
#define VKRENDERER_DEFERREDRENDERMODE_H


#include "../Classes/VulkanRenderMode.h"

class DeferredRenderMode : public VulkanRenderMode {

public:
    DeferredRenderMode();
    ~DeferredRenderMode() override = default;
    void render() override;
};


#endif //VKRENDERER_DEFERREDRENDERMODE_H
