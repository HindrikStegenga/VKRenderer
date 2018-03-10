//
// Created by hindrik on 12-11-17.
//

#include "ForwardRenderMode.h"
#include "../Classes/ShaderModule.h"

ForwardRenderMode::ForwardRenderMode(const ForwardRenderModeCreateInfo &createInfo) : VulkanRenderMode({ "Forward", createInfo.deviceInfo, createInfo.surface })
{
    createCommandPool();
    createRenderMode(createInfo.swapchainInfo);
    createCommandBuffers(createInfo.swapchainInfo);
}

void ForwardRenderMode::windowHasResized(vk_RendermodeSwapchainInfo swapchainInfo)
{
    createRenderMode(swapchainInfo);
    VkResult result = vkResetCommandPool(device, commandPool.get(), VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);
    handleResult(result, "Could not reset the commandpool!");
    Logger::success("Succesfully resetted command pool.");

    createCommandBuffers(swapchainInfo);
}

void ForwardRenderMode::render(uint32_t imageIndex, VkSemaphore imageAvailable, VkSemaphore renderFinished) {

    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo submitInfo         = {};
    submitInfo.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pNext                = nullptr;
    submitInfo.pWaitDstStageMask    = &waitStage;
    submitInfo.pWaitSemaphores      = &imageAvailable;
    submitInfo.waitSemaphoreCount   = 1;
    submitInfo.commandBufferCount   = 1;
    submitInfo.pCommandBuffers      = &commandBuffers[imageIndex];
    submitInfo.pSignalSemaphores    = &renderFinished;
    submitInfo.signalSemaphoreCount = 1;

    VkResult result = vkQueueSubmit(presentQueue.queue, 1, &submitInfo, VK_NULL_HANDLE);
    handleResult(result, "Queue submission has failed!");
}

void ForwardRenderMode::createRenderMode(vk_RendermodeSwapchainInfo swapchainInfo) {

    ShaderModule vertexModule = ShaderModule(device, "shaders/vert.spv", ShaderModuleType::Vertex);
    ShaderModule fragmentModule = ShaderModule(device, "shaders/frag.spv", ShaderModuleType::Fragment);

    std::array<VkPipelineShaderStageCreateInfo, 2> shaderModules = { vertexModule.retrieveShaderStageInfo(), fragmentModule.retrieveShaderStageInfo() };


    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
    vertexInputStateCreateInfo.sType                                = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputStateCreateInfo.pNext                                = nullptr;
    vertexInputStateCreateInfo.vertexBindingDescriptionCount        = 0;
    vertexInputStateCreateInfo.pVertexBindingDescriptions           = nullptr;
    vertexInputStateCreateInfo.vertexAttributeDescriptionCount      = 0;
    vertexInputStateCreateInfo.pVertexAttributeDescriptions         = nullptr;

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
    inputAssemblyStateCreateInfo.sType                                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssemblyStateCreateInfo.pNext                                  = nullptr;
    inputAssemblyStateCreateInfo.topology                               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssemblyStateCreateInfo.primitiveRestartEnable                 = VK_FALSE;
    inputAssemblyStateCreateInfo.flags                                  = {};

    VkViewport viewport = {};
    viewport.x          = 0.0f;
    viewport.y          = 0.0f;
    viewport.maxDepth   = 1.0;
    viewport.minDepth   = 0.0f;
    viewport.width      = swapchainInfo.width;
    viewport.height     = swapchainInfo.height;

    VkRect2D scissor    = {};
    scissor.offset      = VkOffset2D { 0, 0 };
    scissor.extent      = VkExtent2D { swapchainInfo.width, swapchainInfo.height };

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo   = {};
    viewportStateCreateInfo.sType                               = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportStateCreateInfo.pNext                               = nullptr;
    viewportStateCreateInfo.viewportCount                       = 1;
    viewportStateCreateInfo.pViewports                          = &viewport;
    viewportStateCreateInfo.scissorCount                        = 1;
    viewportStateCreateInfo.pScissors                           = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
    rasterizationStateCreateInfo.sType                                  = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizationStateCreateInfo.pNext                                  = nullptr;
    rasterizationStateCreateInfo.depthClampEnable                       = VK_FALSE;
    rasterizationStateCreateInfo.rasterizerDiscardEnable                = VK_FALSE;
    rasterizationStateCreateInfo.polygonMode                            = VK_POLYGON_MODE_FILL;
    rasterizationStateCreateInfo.lineWidth                              = 1.0f;
    rasterizationStateCreateInfo.cullMode                               = VK_CULL_MODE_BACK_BIT;
    rasterizationStateCreateInfo.frontFace                              = VK_FRONT_FACE_CLOCKWISE;
    rasterizationStateCreateInfo.depthBiasEnable                        = VK_FALSE;
    rasterizationStateCreateInfo.depthBiasConstantFactor                = 0.0f;
    rasterizationStateCreateInfo.depthBiasClamp                         = 0.0f;
    rasterizationStateCreateInfo.depthBiasSlopeFactor                   = 0.0f;

    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
    multisampleStateCreateInfo.sType                                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampleStateCreateInfo.pNext                                = nullptr;
    multisampleStateCreateInfo.flags                                = {};
    multisampleStateCreateInfo.alphaToCoverageEnable                = VK_FALSE;
    multisampleStateCreateInfo.alphaToOneEnable                     = VK_FALSE;
    multisampleStateCreateInfo.sampleShadingEnable                  = VK_FALSE;
    multisampleStateCreateInfo.minSampleShading                     = 1.0f;
    multisampleStateCreateInfo.pSampleMask                          = nullptr;
    multisampleStateCreateInfo.rasterizationSamples                 = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachmentState   = {};
    colorBlendAttachmentState.colorWriteMask                        = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachmentState.blendEnable                           = VK_FALSE;
    colorBlendAttachmentState.srcColorBlendFactor                   = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachmentState.dstColorBlendFactor                   = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachmentState.colorBlendOp                          = VK_BLEND_OP_ADD;
    colorBlendAttachmentState.srcAlphaBlendFactor                   = VK_BLEND_FACTOR_ONE;
    colorBlendAttachmentState.dstAlphaBlendFactor                   = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachmentState.alphaBlendOp                          = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo   = {};
    colorBlendStateCreateInfo.sType                                 = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlendStateCreateInfo.pNext                                 = nullptr;
    colorBlendStateCreateInfo.flags                                 = {};
    colorBlendStateCreateInfo.logicOpEnable                         = VK_FALSE;
    colorBlendStateCreateInfo.logicOp                               = VK_LOGIC_OP_COPY;
    colorBlendStateCreateInfo.attachmentCount                       = 1;
    colorBlendStateCreateInfo.pAttachments                          = &colorBlendAttachmentState;
    colorBlendStateCreateInfo.blendConstants[0]                     = 0.0f;
    colorBlendStateCreateInfo.blendConstants[1]                     = 0.0f;
    colorBlendStateCreateInfo.blendConstants[2]                     = 0.0f;
    colorBlendStateCreateInfo.blendConstants[3]                     = 0.0f;

    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
    dynamicStateCreateInfo.sType                            = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicStateCreateInfo.pNext                            = nullptr;
    dynamicStateCreateInfo.flags                            = {};
    dynamicStateCreateInfo.dynamicStateCount                = 0;
    dynamicStateCreateInfo.pDynamicStates                   = nullptr;

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
    pipelineLayoutCreateInfo.sType                      = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutCreateInfo.pNext                      = nullptr;
    pipelineLayoutCreateInfo.flags                      = {};
    pipelineLayoutCreateInfo.pushConstantRangeCount     = 0;
    pipelineLayoutCreateInfo.pPushConstantRanges        = nullptr;
    pipelineLayoutCreateInfo.setLayoutCount             = 0;
    pipelineLayoutCreateInfo.pSetLayouts                = nullptr;


    pipelineLayouts.clear();
    pipelineLayouts.resize(1);

    VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, pipelineLayouts[0].reset(device, vkDestroyPipelineLayout));
    handleResult(result, "Pipeline layout creation has failed!");

    Logger::success("Pipeline layout creation has succeeded!");

    createRenderpassAndFramebuffers(swapchainInfo);

    VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
    graphicsPipelineCreateInfo.sType                        = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    graphicsPipelineCreateInfo.pNext                        = nullptr;
    graphicsPipelineCreateInfo.flags                        = {};
    graphicsPipelineCreateInfo.layout                       = pipelineLayouts.front().get();
    graphicsPipelineCreateInfo.basePipelineHandle           = VK_NULL_HANDLE;
    graphicsPipelineCreateInfo.basePipelineIndex            = -1;
    graphicsPipelineCreateInfo.pInputAssemblyState          = &inputAssemblyStateCreateInfo;
    graphicsPipelineCreateInfo.pVertexInputState            = &vertexInputStateCreateInfo;
    graphicsPipelineCreateInfo.pDepthStencilState           = nullptr; //No depth buffering
    graphicsPipelineCreateInfo.pViewportState               = &viewportStateCreateInfo;
    graphicsPipelineCreateInfo.pRasterizationState          = &rasterizationStateCreateInfo;
    graphicsPipelineCreateInfo.pMultisampleState            = &multisampleStateCreateInfo;
    graphicsPipelineCreateInfo.pColorBlendState             = &colorBlendStateCreateInfo;
    graphicsPipelineCreateInfo.pDynamicState                = nullptr;
    graphicsPipelineCreateInfo.renderPass                   = renderPasses.front().get();
    graphicsPipelineCreateInfo.subpass                      = 0;
    graphicsPipelineCreateInfo.stageCount                   = shaderModules.size();
    graphicsPipelineCreateInfo.pStages                      = shaderModules.data();

    pipelines.clear();
    pipelines.resize(1);
    result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, pipelines.front().reset(device, vkDestroyPipeline));
    handleResult(result, "Failed to create graphics pipeline!");
    Logger::success("Succeeded creating a pipeline!");
}

void ForwardRenderMode::createRenderpassAndFramebuffers(vk_RendermodeSwapchainInfo swapchainInfo) {

    VkAttachmentDescription colorAttachment = {};
    colorAttachment.flags                   = {};
    colorAttachment.format                  = swapchainInfo.format;
    colorAttachment.samples                 = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp                  = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp                 = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp           = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp          = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout             = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference   colorAttachmentReference = {};
    colorAttachmentReference.attachment              = 0;
    colorAttachmentReference.layout                  = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDescription = {};
    subpassDescription.flags                = {};
    subpassDescription.colorAttachmentCount = 1;
    subpassDescription.pColorAttachments    = &colorAttachmentReference;

    VkSubpassDependency subpassDependency   = {};
    subpassDependency.srcSubpass            = VK_SUBPASS_EXTERNAL;
    subpassDependency.dstSubpass            = 0;
    subpassDependency.srcStageMask          = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.srcAccessMask         = 0;
    subpassDependency.dstStageMask          = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.dstAccessMask         = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassCreateInfo = {};
    renderPassCreateInfo.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.pNext                  = nullptr;
    renderPassCreateInfo.attachmentCount        = 1;
    renderPassCreateInfo.pAttachments           = &colorAttachment;
    renderPassCreateInfo.subpassCount           = 1;
    renderPassCreateInfo.pSubpasses             = &subpassDescription;
    renderPassCreateInfo.dependencyCount        = 1;
    renderPassCreateInfo.pDependencies          = &subpassDependency;

    renderPasses.clear();
    renderPasses.resize(1);

    VkResult result = vkCreateRenderPass(device, &renderPassCreateInfo, nullptr, renderPasses.front().reset(device, vkDestroyRenderPass));
    handleResult(result, "Renderpass creation has failed.");

    Logger::success("Renderpass creation succeeded!");

    frameBuffers.clear();

    vector<VKUH<VkFramebuffer>> renderpassFrameBuffers = createFrameBuffersFromSwapchain(renderPasses.front().get(), swapchainInfo);

    frameBuffers.reserve(renderpassFrameBuffers.size());
    std::move(renderpassFrameBuffers.begin(), renderpassFrameBuffers.end(), std::back_inserter(frameBuffers));
}

void ForwardRenderMode::createCommandPool() {

    VkCommandPoolCreateInfo commandPoolCreateInfo = {};

    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.pNext = nullptr;
    commandPoolCreateInfo.flags = {};
    commandPoolCreateInfo.queueFamilyIndex = presentQueue.queueFamily.queueFamilyIndex;

    VkResult result = vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, commandPool.reset(device, vkDestroyCommandPool));
    handleResult(result, "Command pool creation failed!");

    Logger::success("Command pool creation succeeded!");
}

void ForwardRenderMode::createCommandBuffers(vk_RendermodeSwapchainInfo swapchainInfo) {

    commandBuffers.clear();
    commandBuffers.resize(swapchainInfo.colorImageViews.size());

    VkCommandBufferAllocateInfo allocateInfo    = {};
    allocateInfo.sType                          = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.pNext                          = nullptr;
    allocateInfo.commandPool                    = commandPool.get();
    allocateInfo.commandBufferCount             = static_cast<uint32_t >(commandBuffers.size());
    allocateInfo.level                          = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    VkResult result = vkAllocateCommandBuffers(device, &allocateInfo, commandBuffers.data());
    handleResult(result, "Failed allocating command buffers!");
    Logger::success("Succesfully allocated " + std::to_string(commandBuffers.size()) + " commandbuffers");

    for(size_t i = 0; i < commandBuffers.size(); ++i) {

        //Record buffers here!

        VkCommandBufferBeginInfo beginInfo  = {};
        beginInfo.sType                     = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.pNext                     = nullptr;
        beginInfo.flags                     = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        beginInfo.pInheritanceInfo          = nullptr;

        vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

        VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

        VkRenderPassBeginInfo passBeginInfo = {};
        passBeginInfo.sType                 = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        passBeginInfo.pNext                 = nullptr;
        passBeginInfo.renderPass            = renderPasses.front().get();
        passBeginInfo.framebuffer           = frameBuffers[i].get();
        passBeginInfo.clearValueCount       = 1;
        passBeginInfo.pClearValues          = &clearColor;
        passBeginInfo.renderArea.offset     = { 0, 0 };
        passBeginInfo.renderArea.extent     = VkExtent2D { swapchainInfo.width, swapchainInfo.height };

        vkCmdBeginRenderPass(commandBuffers[i], &passBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelines.front().get());

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        result = vkEndCommandBuffer(commandBuffers[i]);
        handleResult(result, "Failed to record command buffers!");
        Logger::success("Succesfully recorded command buffer.");
    }
}

