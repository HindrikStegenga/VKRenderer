//
// Created by Hindrik  Stegenga on 10/03/2018.
//

#ifndef VKRENDERER_SHADERMODULE_H
#define VKRENDERER_SHADERMODULE_H

#include "../Platform/VulkanPlatform.h"
#include "../../CommonInclude.h"

enum class ShaderModuleType : uint8_t
{
    Null,
    Vertex = VK_SHADER_STAGE_VERTEX_BIT,
    Geometry = VK_SHADER_STAGE_GEOMETRY_BIT,
    Fragment = VK_SHADER_STAGE_FRAGMENT_BIT,

};

class ShaderModule final {
private:
    VKUH<VkShaderModule>    shaderModule        = {};
    ShaderModuleType        shaderModuleType    = ShaderModuleType::Null;
    VkDevice                device              = VK_NULL_HANDLE;
public:
    ShaderModule(VkDevice device, const string& fileName, ShaderModuleType shaderType);
    ~ShaderModule() = default;

    ShaderModule(const ShaderModule&)               = delete;
    ShaderModule(ShaderModule&&)                    = default;
    ShaderModule& operator=(const ShaderModule&)    = delete;
    ShaderModule& operator=(ShaderModule&&)         = default;

private:
    static vector<char> readFile(const string& fileName);
public:
    VkPipelineShaderStageCreateInfo retrieveShaderStageInfo();
};


#endif //VKRENDERER_SHADERMODULE_H
