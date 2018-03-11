//
// Created by hindrik on 25-11-17.
//

#ifndef VKRENDERER_SWAPCHAIN_H
#define VKRENDERER_SWAPCHAIN_H

#include "../Platform/VulkanPlatform.h"
#include "../Utilities/UtilityStructures.h"

class Swapchain final {
public:
    explicit Swapchain(SwapchainCreateInfo createInfo);
    ~Swapchain() = default;

    Swapchain(Swapchain&&)      = default;
    Swapchain(const Swapchain&) = delete;

    Swapchain& operator=(Swapchain&&) noexcept  = default;
    Swapchain& operator=(const Swapchain&)      = delete;
private:
    VKUH<VkSwapchainKHR>        swapchain               = VKUH<VkSwapchainKHR>(VK_NULL_HANDLE, VK_NULL_HANDLE, vkDestroySwapchainKHR);
    vector<VkImage>             images;
    vector<VKUH<VkImageView>>   imageViews;

    VKUH<VkSemaphore>           imageAvailableSemaphore = VKUH<VkSemaphore>(VK_NULL_HANDLE, VK_NULL_HANDLE, vkDestroySemaphore);
    VKUH<VkSemaphore>           renderFinishedSemaphore = VKUH<VkSemaphore>(VK_NULL_HANDLE, VK_NULL_HANDLE, vkDestroySemaphore);

    VKUH<VkDeviceMemory>        depthStencilMemory      = VKUH<VkDeviceMemory>(VK_NULL_HANDLE, VK_NULL_HANDLE, vkFreeMemory);
    VKUH<VkImage>               depthStencilImage       = VKUH<VkImage>(VK_NULL_HANDLE, VK_NULL_HANDLE, vkDestroyImage);
    VKUH<VkImageView>           depthStencilImageView   = VKUH<VkImageView>(VK_NULL_HANDLE, VK_NULL_HANDLE, vkDestroyImageView);

    VkDevice                device                      = VK_NULL_HANDLE;
    vk_Queue                presentQueue                = {};
    VkPhysicalDevice        physicalDevice              = VK_NULL_HANDLE;
    VkSurfaceKHR            surface                     = VK_NULL_HANDLE;
    vk_SwapchainSettings    settings                    = {};

private:
    vk_SwapchainSettings    chooseSettings(uint32_t width, uint32_t height);
    void                    createSwapchain(vk_SwapchainSettings settings);
    void                    retrieveImages();
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
    vk_RendermodeSwapchainInfo retrieveRendermodeSwapchainInfo() const;

    VkSemaphore retrieveImageAvailableSemaphore() const;
    VkSemaphore retrieveRenderingFinishedSemaphore() const;

    uint32_t    retrieveNextImageIndex(bool& mustRecreateSwapchain) const;
    void        presentImage(uint32_t imageIndex, bool& mustRecreateSwapchain);
};


#endif //VKRENDERER_SWAPCHAIN_H
