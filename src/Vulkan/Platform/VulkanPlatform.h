//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_VULKANPLATFORM_H
#define VKRENDERER_VULKANPLATFORM_H

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "../../CommonInclude.h"
#include "../Utilities/VkUniqueHandle.h"

template<typename T>
using VKUH = VkUniqueHandle<T>;

inline string mapVkResult(VkResult result){

    switch (result) {

        case VK_SUCCESS : return string("VK_SUCCESS"); 
        case VK_NOT_READY : return string("VK_NOT_READY"); 
        case VK_TIMEOUT : return string("VK_TIMEOUT"); 
        case VK_EVENT_SET : return string("VK_EVENT_SET"); 
        case VK_EVENT_RESET : return string("VK_EVENT_RESET"); 
        case VK_INCOMPLETE : return string("VK_INCOMPLETE"); 
        case VK_ERROR_OUT_OF_HOST_MEMORY : return string("VK_ERROR_OUT_OF_HOST_MEMORY"); 
        case VK_ERROR_OUT_OF_DEVICE_MEMORY : return string("VK_ERROR_OUT_OF_DEVICE_MEMORY"); 
        case VK_ERROR_INITIALIZATION_FAILED : return string("VK_ERROR_INITIALIZATION_FAILED"); 
        case VK_ERROR_DEVICE_LOST : return string("VK_ERROR_DEVICE_LOST"); 
        case VK_ERROR_MEMORY_MAP_FAILED : return string("VK_ERROR_MEMORY_MAP_FAILED"); 
        case VK_ERROR_LAYER_NOT_PRESENT : return string("VK_ERROR_LAYER_NOT_PRESENT"); 
        case VK_ERROR_EXTENSION_NOT_PRESENT : return string("VK_ERROR_EXTENSION_NOT_PRESENT"); 
        case VK_ERROR_FEATURE_NOT_PRESENT : return string("VK_ERROR_FEATURE_NOT_PRESENT"); 
        case VK_ERROR_INCOMPATIBLE_DRIVER : return string("VK_ERROR_INCOMPATIBLE_DRIVER"); 
        case VK_ERROR_TOO_MANY_OBJECTS : return string("VK_ERROR_TOO_MANY_OBJECTS"); 
        case VK_ERROR_FORMAT_NOT_SUPPORTED : return string("VK_ERROR_FORMAT_NOT_SUPPORTED"); 
        case VK_ERROR_FRAGMENTED_POOL : return string("VK_ERROR_FRAGMENTED_POOL"); 

        case VK_ERROR_SURFACE_LOST_KHR: return string("VK_ERROR_SURFACE_LOST_KHR"); 
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return string("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"); 
        case VK_SUBOPTIMAL_KHR: return string("VK_SUBOPTIMAL_KHR"); 
        case VK_ERROR_OUT_OF_DATE_KHR: return string("VK_ERROR_OUT_OF_DATE_KHR"); 
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return string("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"); 
        case VK_ERROR_VALIDATION_FAILED_EXT: return string("VK_ERROR_VALIDATION_FAILED_EXT"); 
        case VK_ERROR_INVALID_SHADER_NV: return string("VK_ERROR_INVALID_SHADER_NV"); 
        case VK_ERROR_OUT_OF_POOL_MEMORY_KHR: return string("VK_ERROR_OUT_OF_POOL_MEMORY_KHR"); 
        case VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR: return string("VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR"); 
        case VK_RESULT_RANGE_SIZE: return string("VK_RESULT_RANGE_SIZE"); 
        case VK_RESULT_MAX_ENUM: return string("VK_RESULT_MAX_ENUM");

        default:
            return "VkResult value not natively supported. Please Check the error value itself!";

    }
}

inline void handleResult(VkResult result, string msg)
{
    if (result != VK_SUCCESS) {
        Logger::failure(msg + " Result: " + mapVkResult(result));
    }
}

#endif //VKRENDERER_VULKANPLATFORM_H
