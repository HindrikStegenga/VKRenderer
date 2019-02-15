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

set(SOURCE_FILES sources/Main.cpp sources/EngineSystems/VulkanRenderSystem/Platform/VulkanPlatform.h sources/EngineSystems/VulkanRenderSystem/VulkanRenderSystem.cpp sources/EngineSystems/VulkanRenderSystem/VulkanRenderSystem.h sources/EngineSystems/VulkanRenderSystem/Utilities/VkUniqueHandle.h sources/CommonInclude.h sources/Core/Engine.cpp sources/Core/Engine.h sources/Utilities/Logger.cpp sources/Utilities/Logger.h sources/Utilities/ConfigFileReader.cpp sources/Utilities/ConfigFileReader.h sources/Utilities/Nullable.h sources/EngineSystems/VulkanRenderSystem/Platform/RenderWindow.cpp sources/EngineSystems/VulkanRenderSystem/Platform/RenderWindow.h sources/Utilities/Macros.h sources/EngineSystems/VulkanRenderSystem/Instance.cpp sources/EngineSystems/VulkanRenderSystem/Instance.h sources/EngineSystems/VulkanRenderSystem/Utilities/UtilityFunctions.cpp sources/EngineSystems/VulkanRenderSystem/Utilities/UtilityFunctions.h sources/EngineSystems/VulkanRenderSystem/PresentDevice.cpp sources/EngineSystems/VulkanRenderSystem/PresentDevice.h sources/EngineSystems/VulkanRenderSystem/VulkanRequirements.h sources/EngineSystems/VulkanRenderSystem/Utilities/PhysicalDevice.cpp sources/EngineSystems/VulkanRenderSystem/Utilities/PhysicalDevice.h sources/EngineSystems/VulkanRenderSystem/Utilities/UtilityStructures.h sources/EngineSystems/VulkanRenderSystem/Classes/VulkanRenderMode.cpp sources/EngineSystems/VulkanRenderSystem/Classes/VulkanRenderMode.h sources/EngineSystems/VulkanRenderSystem/RenderModes/ForwardRenderMode.cpp sources/EngineSystems/VulkanRenderSystem/RenderModes/ForwardRenderMode.h sources/EngineSystems/VulkanRenderSystem/Classes/Swapchain.cpp sources/EngineSystems/VulkanRenderSystem/Classes/Swapchain.h sources/EngineSystems/VulkanRenderSystem/VulkanCreateInfo.h sources/EngineSystems/VulkanRenderSystem/RenderModes/VulkanRenderModeCreateInfo.h sources/Utilities/TypeTraits.h sources/EngineSystems/VulkanRenderSystem/Utilities/VkTypeTraits.h sources/EngineSystems/VulkanRenderSystem/Classes/ShaderModule.cpp sources/EngineSystems/VulkanRenderSystem/Classes/ShaderModule.h sources/EngineSystems/VulkanRenderSystem/Utilities/VkEnums.h sources/EngineSystems/VulkanRenderSystem/Utilities/Parsable/VertexLayout.cpp sources/EngineSystems/VulkanRenderSystem/Utilities/Parsable/VertexLayout.h sources/EngineSystems/VulkanRenderSystem/Utilities/Parsable/VertexAttribute.cpp sources/EngineSystems/VulkanRenderSystem/Utilities/Parsable/VertexAttribute.h sources/EngineSystems/VulkanRenderSystem/Utilities/Parsable/VertexBinding.cpp sources/EngineSystems/VulkanRenderSystem/Utilities/Parsable/VertexBinding.h sources/EngineSystems/VulkanRenderSystem/Classes/Fence.cpp sources/EngineSystems/VulkanRenderSystem/Classes/Fence.h sources/Utilities/Clock.cpp sources/Utilities/Clock.h sources/EngineSystems/VulkanRenderSystem/Classes/DeviceMemoryManager.cpp sources/EngineSystems/VulkanRenderSystem/Classes/DeviceMemoryManager.h sources/DataStorage/StaticStack.h sources/DataStorage/Handle.h sources/EngineSystems/VulkanRenderSystem/Classes/DeviceMemorySubsystem.cpp sources/EngineSystems/VulkanRenderSystem/Classes/DeviceMemorySubsystem.h sources/DataStorage/StaticReusablePool.h sources/DataStorage/ReusablePoolItem.h sources/EngineSystems/VulkanRenderSystem/Classes/WindowRenderTarget.cpp sources/EngineSystems/VulkanRenderSystem/Classes/WindowRenderTarget.h sources/DataStorage/Exceptions/NoMoreItemsException.cpp sources/DataStorage/Exceptions/NoMoreItemsException.h sources/Serializables/SerializeMacro.h sources/Serializables/VulkanTypes.h sources/Serializables/ConfigTypes.h sources/Paths.h sources/Core/SceneManager.cpp sources/Core/SceneManager.h sources/Core/Transform.cpp sources/Core/Transform.h sources/Math/Vectors/Vector2f.h sources/Math/Vectors/Vector3f.h sources/Math/Vectors/Vector4f.h sources/Math/Vectors/Vector2f.cpp sources/Math/Vectors/Vector3f.cpp sources/Math/Vectors/Vector4f.cpp sources/Core/ECS/EngineSystem.h sources/Core/ECS/EngineSystem.cpp sources/Core/ECS/Entity.cpp sources/Core/ECS/Entity.h sources/Core/ECS/Component.cpp sources/Core/ECS/Component.h sources/Core/ECS/TypeID.h sources/Core/ECS/TypeID.cpp sources/Math/Math.h sources/Math/Matrices/Matrix2x2f.cpp sources/Math/Matrices/Matrix2x2f.h sources/Math/Matrices/Matrix3x3f.cpp sources/Math/Matrices/Matrix3x3f.h sources/Math/Matrices/Matrix4x4f.cpp sources/Math/Matrices/Matrix4x4f.h sources/Math/MathSerialization.h sources/Core/Threading/Threadpool.h sources/Core/Threading/Threadpool.cpp sources/Core/Threading/ThreadWorker.h sources/Core/Threading/ThreadWorker.cpp sources/Core/Threading/AwaitableTask.h sources/Core/Threading/AwaitableTask.cpp sources/Core/Scene.cpp sources/Core/Scene.h sources/DataStorage/LinearStaticReusablePool.h sources/DataStorage/LinearPoolItem.h sources/Core/Threading/EngineSystemThreadingContainer.h sources/Core/Threading/EngineSystemThreadingContainer.cpp)

add_executable(VKRenderer ${SOURCE_FILES})