cmake_minimum_required(VERSION 3.8)
project(VKRenderer)

set(CMAKE_CXX_STANDARD 14)

include_directories($ENV{VULKAN_SDK}/include)
link_directories($ENV{VULKAN_SDK}/lib)

if (WIN32)

    include_directories("libraries/GLFW/include")
    
	if (MSVC)
		link_directories("libraries/GLFW/lib_msvc")

	endif()
	if (NOT MSVC)

		link_directories("libraries/GLFW/lib_mingw")

		set(CMAKE_SHARED_LINKER_FLAGS -static -static-libgcc -static-libstdc++)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")

	endif()

endif()

if (APPLE)
    include_directories("/usr/local/include")
    link_directories("/usr/local/lib/")
endif()


if (WIN32)
	if (NOT MSVC)
		link_libraries(vulkan-1 glfw3 pthread)
	elseif (MSVC)
		link_libraries(vulkan-1 glfw3)
	endif()
elseif(APPLE)
    link_libraries(glfw vulkan)
else()
    link_libraries(vulkan glfw pthread)
endif()

set(SOURCE_FILES src/main.cpp src/Vulkan/Platform/VulkanPlatform.h src/Vulkan/VulkanRenderer.cpp src/Vulkan/VulkanRenderer.h src/Vulkan/Utilities/VkUniqueHandle.h src/CommonInclude.h src/Application.cpp src/Application.h src/Utilities/Logger.cpp src/Utilities/Logger.h src/Utilities/ConfigFileReader.cpp src/Utilities/ConfigFileReader.h src/Utilities/Nullable.h src/Vulkan/Platform/RenderWindow.cpp src/Vulkan/Platform/RenderWindow.h src/Utilities/Macros.h src/Vulkan/Instance.cpp src/Vulkan/Instance.h src/Vulkan/Utilities/UtilityFunctions.cpp src/Vulkan/Utilities/UtilityFunctions.h src/Vulkan/PresentDevice.cpp src/Vulkan/PresentDevice.h src/Vulkan/VulkanRequirements.h src/Vulkan/Utilities/PhysicalDevice.cpp src/Vulkan/Utilities/PhysicalDevice.h src/Vulkan/Utilities/UtilityStructures.h src/Vulkan/Classes/VulkanRenderMode.cpp src/Vulkan/Classes/VulkanRenderMode.h src/Vulkan/RenderModes/ForwardRenderMode.cpp src/Vulkan/RenderModes/ForwardRenderMode.h src/Utilities/Threadpool.cpp src/Utilities/Threadpool.h src/Utilities/ThreadWorker.cpp src/Utilities/ThreadWorker.h src/Utilities/AwaitableTask.cpp src/Utilities/AwaitableTask.h src/Vulkan/Classes/Swapchain.cpp src/Vulkan/Classes/Swapchain.h src/Vulkan/VulkanCreateInfo.h src/Vulkan/RenderModes/VulkanRenderModeCreateInfo.h src/Utilities/TypeTraits.h src/Vulkan/Utilities/VkTypeTraits.h src/Vulkan/Classes/ShaderModule.cpp src/Vulkan/Classes/ShaderModule.h src/Vulkan/Utilities/VkEnums.h)

add_executable(VKRenderer ${SOURCE_FILES})