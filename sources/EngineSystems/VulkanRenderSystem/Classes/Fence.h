//
// Created by Hindrik  Stegenga on 06/04/2018.
//

#ifndef VKRENDERER_FENCE_H
#define VKRENDERER_FENCE_H

#include "../Platform/VulkanPlatform.h"
#include "../../../CommonInclude.h"

class Fence final {
private:
    VKUH<VkFence>   fence   = {};
    VkDevice        device  = VK_NULL_HANDLE;
public:
    explicit Fence(VkDevice device, bool signaled = false);
    ~Fence()                         = default;

    Fence(const Fence&) = delete;
    Fence(Fence&&)      = default;

    Fence& operator=(const Fence&)  = delete;
    Fence& operator=(Fence&&)       = default;
public:
    void wait();
    void reset();
    VkFence get();
    VkResult status();

    static void waitForFences(VkDevice device, vector<Fence> fences, bool waitAll = true);
    static void resetFences(VkDevice device, vector<Fence> fences);

};


#endif //VKRENDERER_FENCE_H
