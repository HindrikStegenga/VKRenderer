//
// Created by Hindrik  Stegenga on 10/03/2018.
//

#include "ShaderModule.h"

ShaderModule::ShaderModule(VkDevice device, const string &fileName, ShaderModuleType shaderType) : device(device), shaderModuleType(shaderType)
{
    vector<char> data = readFile(fileName);

    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pNext    = nullptr;
    createInfo.codeSize = data.size();
    createInfo.pCode    = reinterpret_cast<const uint32_t*>(data.data());
    createInfo.flags    = {};

    VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, shaderModule.reset(device, vkDestroyShaderModule));

    handleResult(result, "Shader module creation has failed: " + fileName);
}

vector<char> ShaderModule::readFile(const string &fileName) {

    std::ifstream file(fileName, std::ios::ate | std::ios::binary);

    if(!file.is_open())
    {
        Logger::failure("Error when opening spir-V file!");
    }

    auto fileSize = static_cast<size_t >(file.tellg());
    vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    return buffer;
}

VkPipelineShaderStageCreateInfo ShaderModule::retrieveShaderStageInfo() {

    VkPipelineShaderStageCreateInfo createInfo  = {};
    createInfo.sType                            = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    createInfo.pNext                            = nullptr;
    createInfo.flags                            = {};
    createInfo.module                           = shaderModule.get();
    createInfo.pName                            = "main";
    createInfo.pSpecializationInfo              = nullptr;
    createInfo.stage                            = static_cast<VkShaderStageFlagBits>(shaderModuleType);

    return createInfo;
}
