//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VULKANPLATFORM_H
#define VKRENDERER_VULKANPLATFORM_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../CommonInclude.h"
#include "VkUniqueHandle.h"

template<typename T>
using VKUH = VkUniqueHandle<T>;

inline void handleResult(VkResult result, string msg) {
    if (result != VK_SUCCESS) {
        Logger::failure(msg);
    }
}




#endif //VKRENDERER_VULKANPLATFORM_H
