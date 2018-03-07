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
    VKUH<VkSwapchainKHR>        swapchain;
    vector<VkImage>             images;
    vector<VKUH<VkImageView>>   imageViews;

    VkDevice                device;
    VkPhysicalDevice        physicalDevice;
    VkSurfaceKHR            surface;
    vk_SwapchainSettings    settings;

private:
    vk_SwapchainSettings chooseSettings(uint32_t width, uint32_t height);
    void createSwapchain(vk_SwapchainSettings settings);
    void retrieveImages();
    void createImageViews();

    static VkSurfaceFormatKHR chooseSurfaceFormat(const vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR choosePresentMode(const vector<VkPresentModeKHR>& availableModes);
    static VkExtent2D chooseExtent(uint32_t width, uint32_t height, VkSurfaceCapabilitiesKHR surfaceCaps);
};


#endif //VKRENDERER_SWAPCHAIN_H
