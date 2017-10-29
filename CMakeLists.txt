cmake_minimum_required(VERSION 3.8)
project(VKRenderer)

set(CMAKE_CXX_STANDARD 17)

include_directories($ENV{VULKAN_SDK}/include)
link_directories($ENV{VULKAN_SDK}/lib)

link_libraries(vulkan glfw pthread)

set(SOURCE_FILES src/main.cpp src/Vulkan/VulkanPlatform.h src/Vulkan/VulkanRenderer.cpp src/Vulkan/VulkanRenderer.h src/Vulkan/VkUniqueHandle.h src/Vulkan/CommonInclude.h)
add_executable(VKRenderer ${SOURCE_FILES})