#include "LogicalDevice.hpp"
#include <set>
namespace celer {
	void LogicalDevice::createLogicalDevice()
	{
		VkPhysicalDeviceFeatures requiredFeatures = {};
		VkPhysicalDeviceFeatures supportedFeatures = physicalDevice->getSupportedFeatures();
		requiredFeatures.multiDrawIndirect = supportedFeatures.multiDrawIndirect;
		requiredFeatures.tessellationShader = VK_TRUE;
		requiredFeatures.geometryShader = VK_TRUE;
		RequiredQueueFamilies* reqFam = physicalDevice->getReqQueueFamilies();
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = {
			reqFam->graphics.queueFamilyIndex,
			reqFam->compute.queueFamilyIndex,
			reqFam->transfer.queueFamilyIndex,
			reqFam->present.queueFamilyIndex
		};
		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pNext = nullptr;
		deviceCreateInfo.flags = 0;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.enabledLayerCount = 0;
		deviceCreateInfo.ppEnabledLayerNames = nullptr;
		deviceCreateInfo.enabledExtensionCount = 0;
		deviceCreateInfo.ppEnabledExtensionNames = nullptr;
		deviceCreateInfo.pEnabledFeatures = &requiredFeatures;
		VkResult result = vkCreateDevice(*(physicalDevice->getDeviceDescriptor()), &deviceCreateInfo, nullptr, &device);
		if (result != VK_SUCCESS) { throw "Cannot create logical device!"; }
	}
	void LogicalDevice::destroyLogicalDevice()
	{
	}
}