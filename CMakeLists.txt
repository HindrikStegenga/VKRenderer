cmake_minimum_required(VERSION 3.8)
project(VKRenderer)

set(CMAKE_CXX_STANDARD 14)

include_directories($ENV{VULKAN_SDK}/include)
link_directories($ENV{VULKAN_SDK}/lib)

link_libraries(vulkan glfw pthread)

set(SOURCE_FILES src/main.cpp src/Vulkan/Platform/VulkanPlatform.h src/Vulkan/VulkanRenderer.cpp src/Vulkan/VulkanRenderer.h src/Vulkan/Utilities/VkUniqueHandle.h src/CommonInclude.h src/Application.cpp src/Application.h src/Utilities/Logger.cpp src/Utilities/Logger.h src/Utilities/ConfigFileReader.cpp src/Utilities/ConfigFileReader.h src/Utilities/Nullable.h src/Vulkan/Platform/RenderWindow.cpp src/Vulkan/Platform/RenderWindow.h src/Utilities/Macros.h src/Vulkan/Instance.cpp src/Vulkan/Instance.h src/Vulkan/Utilities/UtilityFunctions.cpp src/Vulkan/Utilities/UtilityFunctions.h src/Vulkan/PresentDevice.cpp src/Vulkan/PresentDevice.h src/Vulkan/VulkanRequirements.h src/Vulkan/Utilities/PhysicalDevice.cpp src/Vulkan/Utilities/PhysicalDevice.h src/Vulkan/Utilities/UtilityStructrues.h src/Vulkan/Classes/VulkanRenderMode.cpp src/Vulkan/Classes/VulkanRenderMode.h src/Vulkan/RenderModes/ForwardRenderMode.cpp src/Vulkan/RenderModes/ForwardRenderMode.h src/Vulkan/RenderModes/DeferredRenderMode.cpp src/Vulkan/RenderModes/DeferredRenderMode.h src/Utilities/Threadpool.cpp src/Utilities/Threadpool.h src/Utilities/ThreadWorker.cpp src/Utilities/ThreadWorker.h src/Utilities/AwaitableTask.cpp src/Utilities/AwaitableTask.h src/Vulkan/Classes/Swapchain.cpp src/Vulkan/Classes/Swapchain.h)
add_executable(VKRenderer ${SOURCE_FILES})