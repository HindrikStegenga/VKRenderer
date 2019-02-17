//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "VulkanRenderSystem.h"
#include "../../Utilities/ConfigFileReader.h"
#include "RenderModes/ForwardRenderMode.h"
#include "Utilities/Parsable/VertexLayout.h"
#include "../../Core/Engine.h"


VulkanRenderSystem::VulkanRenderSystem(Engine* engine, vk_GeneralSettings settings, ExtensionProcessingFunc extensionProcessingFunc) : EngineSystem(engine), debugEnabled(settings.applicationSettings.debugMode ? VK_TRUE : VK_FALSE)
{
    vector<const char*> extensions;
	vector<const char*> layers;
	vector<const char*> debugExtensions;
	vector<const char*> debugLayers;
	vector<const char*> dExtensions;
	vector<const char*> ddExtensions;

#ifdef USE_INSTANCE_EXT
    for (auto instanceExtension : instanceExtensions) {
        extensions.push_back(instanceExtension);
    }
#endif
#ifdef USE_INSTANCE_LAYERS
    for (auto instanceLayer : instanceLayers) {
        layers.push_back(instanceLayer);
    }
#endif
#ifdef USE_DEBUG_INSTANCE_EXT
    for (auto instanceExtension : debugInstanceExtensions) {
        debugExtensions.push_back(instanceExtension);
    }
#endif
#ifdef USE_DEBUG_INSTANCE_LAYERS
    for (auto instanceLayer : debugInstanceLayers) {
        debugLayers.push_back(instanceLayer);
    }
#endif
#ifdef USE_DEVICE_EXT
    for (auto extension : deviceExtensions) {
        dExtensions.push_back(extension);
    }
#endif
#ifdef USE_DEBUG_DEVICE_EXT
    for (auto extension : debugDeviceExtensions) {
        ddExtensions.push_back(extension);
    }
#endif

    auto processedExtensions = extensionProcessingFunc != nullptr ? extensionProcessingFunc(extensions) : extensions;

    VulkanInstanceCreateInfo supportDescription { layers, processedExtensions, debugLayers, debugExtensions };

    instance = Instance(settings, supportDescription);

    if (this->debugEnabled == VK_TRUE) {
        setupDebugCallback();
    }

    vector<RenderWindow>& renderWindows = engine->getRenderWindows();

    vector<VkSurfaceKHR> surfaces(renderWindows.size());
    for (size_t i = 0; i < renderWindows.size(); ++i) {
        auto& window = renderWindows[i];
        surfaces[i] = (window.getWindowSurface(instance.getHandle()));
    }


    PresentDeviceCreateInfo deviceSupportDescription { dExtensions, ddExtensions, surfaces, requiredDeviceFeatures };

    device = PresentDevice(instance.getHandle(), settings, deviceSupportDescription);

    for (size_t i = 0; i < renderWindows.size(); ++i) {

        auto& renderWindow = renderWindows[i];

        WindowRenderTarget target = {};
        target.renderWindow = &renderWindow;
        target.surface = VKUH<VkSurfaceKHR>(surfaces[i], instance.getHandle(), vkDestroySurfaceKHR);

        SwapchainCreateInfo swapchainCreateInfo = {};

        swapchainCreateInfo.deviceInfo              = device.getPresentDeviceInfo();
        swapchainCreateInfo.surface                 = target.surface;
        swapchainCreateInfo.width                   = settings.graphicsSettings.resolutionX;
        swapchainCreateInfo.height                  = settings.graphicsSettings.resolutionY;
        swapchainCreateInfo.preferredFramesInFlight = settings.vulkanSettings.preferredFramesInFlight;
        swapchainCreateInfo.limitFrameRate          = settings.graphicsSettings.limitFrameRate;
        swapchainCreateInfo.preventTearing          = settings.graphicsSettings.preventTearing;

        target.swapchain = Swapchain(swapchainCreateInfo);

        if (settings.vulkanSettings.renderMode == string("forward")) {

            ForwardRenderModeCreateInfo createInfo = {};

            createInfo.deviceInfo       = device.getPresentDeviceInfo();
            createInfo.surface          = target.surface;
            createInfo.swapchainInfo    = target.swapchain.getRendermodeSwapchainInfo();

            target.renderMode = std::make_unique<ForwardRenderMode>(createInfo);
        }
        else
        {
            Logger::error("Could not find appropriate renderMode!");
        }

        windowRenderTargets.emplace_back(std::move(target));
    }
}

VkBool32 VulkanRenderSystem::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
                                       size_t location, int32_t code, const char *layerPrefix, const char *msg,
                                       void *userData)
{
    Logger::warn("Validation layer: " + string(msg));
    return VK_FALSE;
}

void VulkanRenderSystem::resizeWindow(uint32_t width, uint32_t height, WindowRenderTarget* renderTarget) {

    if(width == 0 && height == 0)
        return;

    Logger::log("Window will be resized: " + std::to_string(width) + " - " + std::to_string(height));

    vk_RendermodeSwapchainInfo swapchainInfo = renderTarget->swapchain.recreateSwapchain(width, height, renderTarget->swapchain.preferredFramesInFlight(), renderTarget->swapchain.preferredTearingSetting(), renderTarget->swapchain.preferredFrameLimitingSetting());

    renderTarget->renderMode->windowHasResized(swapchainInfo);
}

void VulkanRenderSystem::resizeWindow(bool mustResize, WindowRenderTarget* renderTarget) {

    if(mustResize)
    {
        uint32_t width, height;
        renderTarget->renderWindow->getCurrentSize(width, height);
        resizeWindow(width, height, renderTarget);
    }
}

void VulkanRenderSystem::setupDebugCallback()
{
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType        = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.pNext        = nullptr;
    createInfo.flags        = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback  = debugCallback;
    createInfo.pUserData    = nullptr;

    VkResult result = createDebugReportCallbackEXT(instance.getHandle(), &createInfo, nullptr, &debugCallbackHandle);
    if (result != VK_SUCCESS) {
        Logger::warn("Debug callback is not enabled! Reason: " + mapVkResult(result));
        debugEnabled = VK_FALSE;
    }
    else {
        Logger::success("Debug callback enabled!");
    }
}

VulkanRenderSystem::~VulkanRenderSystem()
{
    if (instance.getHandle() != VK_NULL_HANDLE) {
        Logger::log("Shutting down the Vulkan renderer.");
        vkDeviceWaitIdle(getDevice());
    }

    if (debugEnabled == VK_TRUE) {
        destroyDebugReportCallbackEXT(instance.getHandle(), debugCallbackHandle, nullptr);
    }
}

VkDevice VulkanRenderSystem::getDevice() {
    return device.getPresentDeviceInfo().logical;
}

void VulkanRenderSystem::windowHasResized(uint32_t width, uint32_t height, RenderWindow* renderWindow) {

    for (auto& target : windowRenderTargets) {
        if (target.renderWindow == renderWindow) {
            resizeWindow(width, height, &target);
        }
    }
}

bool VulkanRenderSystem::update(std::chrono::nanoseconds deltaTime) {

    bool canContinue = processWindowEvents(deltaTime);

    if(!canContinue)
        return false;

    render();

    return true;
}

bool VulkanRenderSystem::processWindowEvents(nanoseconds deltaTime) {
    latestDeltaTime = deltaTime;
    accumulatedTime += latestDeltaTime;
    accumulatedFrames += 1;

    for(auto& target : windowRenderTargets) {

        if (!target.renderWindow->pollWindowEvents())
            return false;
    }

    int64_t fps = 0;
    bool mustSetFPS = false;

    if (accumulatedTime > std::chrono::milliseconds(500)) {

        nanoseconds averagePerFrame = accumulatedTime / accumulatedFrames;

        nanoseconds second = std::chrono::duration_cast<nanoseconds>(std::chrono::seconds(1));

        if (averagePerFrame.count() > 0) {
            fps = second.count() / averagePerFrame.count();

            mustSetFPS = true;
            accumulatedFrames = 0;
            accumulatedTime = nanoseconds(0);
        }
    }

    for (auto& target : windowRenderTargets) {

        if (mustSetFPS) {
            target.renderWindow->setWindowTitle("VKRenderer " + std::to_string(fps) + " FPS");
        }
    }
    return true;
}

void VulkanRenderSystem::render() {

    for (auto& target : windowRenderTargets) {

        vk_PresentImageInfo presentImageInfo = target.swapchain.acquireNextImage();

        resizeWindow(presentImageInfo.mustRecreateSwapchain, &target);

        if(presentImageInfo.imageIndex == std::numeric_limits<uint32_t>::max())
            continue;

        target.renderMode->render(presentImageInfo);

        bool mustResize = false;
        target.swapchain.presentImage(presentImageInfo.imageIndex, mustResize);

        resizeWindow(mustResize, &target);
    }
}
