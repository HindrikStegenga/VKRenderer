cmake_minimum_required(VERSION 3.8)
project(VKRenderer)

set(CMAKE_CXX_STANDARD 14)

find_package(Vulkan REQUIRED)

if(Vulkan_FOUND)

	message("Vulkan include directory: " ${Vulkan_INCLUDE_DIRS})
	message("Vulkan libraries: " ${Vulkan_LIBRARIES})

	include_directories(${Vulkan_INCLUDE_DIRS})
else()
	include_directories($ENV{VULKAN_SDK}/include)
	link_directories($ENV{VULKAN_SDK}/lib)

	message("Vulkan include directory: " $ENV{VULKAN_SDK}/include)
	message("Vulkan library directory: " $ENV{VULKAN_SDK}/lib)

endif()


include_directories(libraries)

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
	link_libraries(glfw)
	if(Vulkan_FOUND)
		link_libraries(${Vulkan_LIBRARIES})
	else()
		link_libraries(vulkan)
	endif()
else()
    link_libraries(vulkan glfw pthread)
endif()

set(SOURCE_FILES sources/Main.cpp sources/Vulkan/Platform/VulkanPlatform.h sources/Vulkan/VulkanRenderer.cpp sources/Vulkan/VulkanRenderer.h sources/Vulkan/Utilities/VkUniqueHandle.h sources/CommonInclude.h sources/Application.cpp sources/Application.h sources/Utilities/Logger.cpp sources/Utilities/Logger.h sources/Utilities/ConfigFileReader.cpp sources/Utilities/ConfigFileReader.h sources/Utilities/Nullable.h sources/Vulkan/Platform/RenderWindow.cpp sources/Vulkan/Platform/RenderWindow.h sources/Utilities/Macros.h sources/Vulkan/Instance.cpp sources/Vulkan/Instance.h sources/Vulkan/Utilities/UtilityFunctions.cpp sources/Vulkan/Utilities/UtilityFunctions.h sources/Vulkan/PresentDevice.cpp sources/Vulkan/PresentDevice.h sources/Vulkan/VulkanRequirements.h sources/Vulkan/Utilities/PhysicalDevice.cpp sources/Vulkan/Utilities/PhysicalDevice.h sources/Vulkan/Utilities/UtilityStructures.h sources/Vulkan/Classes/VulkanRenderMode.cpp sources/Vulkan/Classes/VulkanRenderMode.h sources/Vulkan/RenderModes/ForwardRenderMode.cpp sources/Vulkan/RenderModes/ForwardRenderMode.h sources/Utilities/Threadpool.cpp sources/Utilities/Threadpool.h sources/Utilities/ThreadWorker.cpp sources/Utilities/ThreadWorker.h sources/Utilities/AwaitableTask.cpp sources/Utilities/AwaitableTask.h sources/Vulkan/Classes/Swapchain.cpp sources/Vulkan/Classes/Swapchain.h sources/Vulkan/VulkanCreateInfo.h sources/Vulkan/RenderModes/VulkanRenderModeCreateInfo.h sources/Utilities/TypeTraits.h sources/Vulkan/Utilities/VkTypeTraits.h sources/Vulkan/Classes/ShaderModule.cpp sources/Vulkan/Classes/ShaderModule.h sources/Vulkan/Utilities/VkEnums.h sources/Vulkan/Utilities/Parsable/VertexLayout.cpp sources/Vulkan/Utilities/Parsable/VertexLayout.h sources/Vulkan/Utilities/Parsable/VertexAttribute.cpp sources/Vulkan/Utilities/Parsable/VertexAttribute.h sources/Vulkan/Utilities/Parsable/VertexBinding.cpp sources/Vulkan/Utilities/Parsable/VertexBinding.h sources/Vulkan/Classes/Fence.cpp sources/Vulkan/Classes/Fence.h sources/Utilities/Clock.cpp sources/Utilities/Clock.h sources/Utilities/BasicVectorTypes.h sources/Vulkan/Classes/DeviceMemoryManager.cpp sources/Vulkan/Classes/DeviceMemoryManager.h sources/DataStorage/StaticStack.h sources/DataStorage/Handle.h sources/Vulkan/Classes/DeviceMemorySubsystem.cpp sources/Vulkan/Classes/DeviceMemorySubsystem.h sources/DataStorage/StaticReusablePool.h sources/DataStorage/ReusablePoolItem.h sources/Vulkan/Classes/WindowRenderTarget.cpp sources/Vulkan/Classes/WindowRenderTarget.h sources/DataStorage/Exceptions/NoMoreItemsException.cpp sources/DataStorage/Exceptions/NoMoreItemsException.h sources/Serializables/SerializeMacro.h sources/Serializables/VulkanTypes.h sources/Serializables/ConfigTypes.h sources/Paths.h sources/Generic/SceneManager.cpp sources/Generic/SceneManager.h sources/Generic/GameObject.cpp sources/Generic/GameObject.h sources/Generic/Transform.cpp sources/Generic/Transform.h sources/Serializables/Vectors.h sources/Serializables/GenericTypes.h sources/Math/Vector2f.h sources/Math/Vector3f.h sources/Math/Vector4f.h sources/Math/Vector2f.cpp sources/Math/Vector3f.cpp sources/Math/Vector4f.cpp)

add_executable(VKRenderer ${SOURCE_FILES})