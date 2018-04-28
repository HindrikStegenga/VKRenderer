//
// Created by hindrik on 25-11-17.
//

#ifndef VKRENDERER_SWAPCHAIN_H
#define VKRENDERER_SWAPCHAIN_H

#include "../Platform/VulkanPlatform.h"
#include "../Utilities/UtilityStructures.h"
#include "Fence.h"

class Swapchain final {
public:
    explicit Swapchain(SwapchainCreateInfo createInfo);
    ~Swapchain() = default;

    Swapchain(Swapchain&&)      = default;
    Swapchain(const Swapchain&) = delete;

    Swapchain& operator=(Swapchain&&) noexcept  = default;
    Swapchain& operator=(const Swapchain&)      = delete;
private:
    VKUH<VkSwapchainKHR>        swapchain               = {};
    vector<pair<Fence, bool>>   fences                  = {};
    vector<VkImage>             images;
    vector<VKUH<VkImageView>>   imageViews;

    vector<VKUH<VkSemaphore>>   imageAvailableSemaphores = {};
    vector<VKUH<VkSemaphore>>   renderFinishedSemaphores = {};

    VKUH<VkDeviceMemory>        depthStencilMemory      = {};
    VKUH<VkImage>               depthStencilImage       = {};
    VKUH<VkImageView>           depthStencilImageView   = {};

    VkDevice                device                      = VK_NULL_HANDLE;
    vk_Queue                presentQueue                = {};
    VkPhysicalDevice        physicalDevice              = VK_NULL_HANDLE;
    VkSurfaceKHR            surface                     = VK_NULL_HANDLE;
    vk_SwapchainSettings    settings                    = {};
    uint32_t                frameIndex                  = 0;

private:
    vk_SwapchainSettings    chooseSettings(uint32_t width, uint32_t height);
    void                    createSwapchain(vk_SwapchainSettings settings);
    void                    retrieveImages();
    void                    createFences();
    void                    createImageViews();
    void                    createDepthStencil();
    void                    createDepthStencilImage(VkFormat format);
    void                    allocateDepthStencilMemory();
    void                    createDepthStencilImageView(VkFormat format);
    void                    createSemaphores();

    static VkSurfaceFormatKHR chooseSurfaceFormat(const vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR choosePresentMode(const vector<VkPresentModeKHR>& availableModes);
    static VkExtent2D chooseExtent(uint32_t width, uint32_t height, VkSurfaceCapabilitiesKHR surfaceCaps);

    VkFormat chooseDepthStencilFormat(bool requiresStencil = false) const;
public:
    vk_RendermodeSwapchainInfo recreateSwapchain(uint32_t width, uint32_t height);
    vk_RendermodeSwapchainInfo getRendermodeSwapchainInfo() const;

    vk_PresentImageInfo     acquireNextImage();
    void                    presentImage(uint32_t imageIndex, bool &mustRecreateSwapchain) const;
};


#endif //VKRENDERER_SWAPCHAIN_H
