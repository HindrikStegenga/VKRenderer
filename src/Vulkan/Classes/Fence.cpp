//
// Created by Hindrik  Stegenga on 06/04/2018.
//

#include "Fence.h"

Fence::Fence(VkDevice device, bool signaled) : device(device)
{

    VkFenceCreateInfo createInfo    = {};
    createInfo.sType                = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    createInfo.pNext                = nullptr;
    createInfo.flags                = signaled ? VK_FENCE_CREATE_SIGNALED_BIT : VkFenceCreateFlagBits{};

    VkResult result = vkCreateFence(device, &createInfo, nullptr, fence.reset(device, vkDestroyFence));
    handleResult(result, "Fence creation has failed!");
}

void Fence::wait()
{
    VkFence f = fence.get();
    vkWaitForFences(device, 1, &f, VK_TRUE, std::numeric_limits<uint64_t>::max());
}

void Fence::reset()
{
    vkResetFences(device, 1, fence.getPointer());
}

void Fence::waitForFences(VkDevice device, vector<Fence> fences, bool waitAll)
{
    vector<VkFence> pointers(fences.size());
    for(size_t i = 0; i < pointers.size(); ++i)
    {
        pointers[i] = fences[i].fence.get();
    }
    vkWaitForFences(device, static_cast<uint32_t>(pointers.size()), pointers.data(), waitAll ? VK_TRUE : VK_FALSE, std::numeric_limits<uint64_t >::max());
}

void Fence::resetFences(VkDevice device, vector<Fence> fences)
{
    vector<VkFence> pointers(fences.size());
    for(size_t i = 0; i < pointers.size(); ++i)
    {
        pointers[i] = fences[i].fence.get();
    }
    vkResetFences(device, static_cast<uint32_t>(pointers.size()), pointers.data());
}

VkFence Fence::get() {
    return fence.get();
}

VkResult Fence::status() {
    return vkGetFenceStatus(device, fence.get());
}
