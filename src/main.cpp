#include <iostream>
#include "Vulkan/VulkanPlatform.h"



int main() {

    VkUniqueHandle<VkInstance> handle(vkDestroyInstance);

    if (handle) {
        std::cout << "true!" << std::endl;
    } else {
        std::cout << "false!" << std::endl;
    }


    return 0;
}