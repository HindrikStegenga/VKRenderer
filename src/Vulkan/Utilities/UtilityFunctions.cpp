//
// Created by Hindrik Stegenga on 3-11-17.
//

#include "UtilityFunctions.h"

auto operator<<(ostream& o, VkPhysicalDeviceType& t) -> ostream&
{
    switch(t)
    {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            o << "Other";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            o << "Integrated GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            o << "Discrete GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            o << "Virtual GPU";
            break;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            o << "CPU";
            break;
        default:
            o << t;
            break;
    }
    return o;
}

auto operator<<(ostream& o, VkPhysicalDeviceProperties& p) -> ostream&
{

    string vendorName = std::to_string(p.vendorID);

    o << "---------------DEVICE---------------" << std::endl;

    o << "Name: "               << p.deviceName     << std::endl;
    o << "Type: "               << p.deviceType     << std::endl;
    o << "Vendor: "             << vendorName       << std::endl;
    o << "PresentDevice ID: "          << p.deviceID       << std::endl;
    o << "API Version: "        << p.apiVersion     << std::endl;
    o << "Driver Version: "     << p.driverVersion  << std::endl;

    o << "------------------------------------"     << std::endl;

    return o;
}

auto operator<<(ostream &o, VkQueueFamilyProperties p) -> ostream&
{

    o << "------------QUEUE_FAMILY------------" << std::endl;

    o << "Queue count: " << p.queueCount << std::endl;

    o << "------------------------------------" << std::endl;
    o << "Graphics: "               << (static_cast<bool>(p.queueFlags & VK_QUEUE_GRAPHICS_BIT) ? "Yes" : "No")          << std::endl;
    o << "Compute: "                << (static_cast<bool>(p.queueFlags & VK_QUEUE_COMPUTE_BIT)  ? "Yes" : "No")          << std::endl;
    o << "Transfer: "               << (static_cast<bool>(p.queueFlags & VK_QUEUE_TRANSFER_BIT) ? "Yes" : "No")          << std::endl;
    o << "Sparse binding: "         << (static_cast<bool>(p.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) ? "Yes" : "No")    << std::endl;

    o << "------------------------------------" << std::endl;

    return o;
}

auto operator<<(ostream &o, VkExtensionProperties p) -> ostream&
{

    o << "------------------------------EXTENSION PROPERTIES------------------------------" << std::endl;
    o << "Extension name: "         << p.extensionName  << std::endl;
    o << "Extension spec version: " << p.specVersion    << std::endl;
    o << "------------------------------------------------------------------------------" << std::endl;

    return o;
}

uint32_t deviceTypePriority(VkPhysicalDeviceType deviceType)
{
    switch (deviceType) {
        case VK_PHYSICAL_DEVICE_TYPE_RANGE_SIZE:
            return 0;
        case VK_PHYSICAL_DEVICE_TYPE_MAX_ENUM:
            return 1;
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return 2;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return 3;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return 4;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return 5;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return 6;
    }
}


