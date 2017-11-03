//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VULKANRENDERER_H
#define VKRENDERER_VULKANRENDERER_H

#include "Platform/VulkanPlatform.h"
#include "VulkanRequirements.h"
#include "Platform/RenderWindow.h"
#include "../Utilities/Nullable.h"
#include "Instance.h"
#include "PresentDevice.h"

class VulkanRenderer final {
public:
    explicit VulkanRenderer(string appName, string engineName, bool debugEnabled = false);
    ~VulkanRenderer() = default;

    VulkanRenderer(const VulkanRenderer&) = delete;
    VulkanRenderer(VulkanRenderer&&) = default;

    VulkanRenderer& operator= (const VulkanRenderer&) = delete;
    VulkanRenderer& operator= (VulkanRenderer&&) = default;
private:
    Nullable<RenderWindow>      renderWindow;
    Nullable<Instance>          instance;
    Nullable<PresentDevice>     device;
public:
    bool processEvents() const;

private:



};


#endif //VKRENDERER_VULKANRENDERER_H
