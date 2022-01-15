#include "PhysicalDevice.hpp"
#include "log.hpp"
#include <string>
namespace celer {
	void PhysicalDevice::initDevice()
	{
		enumeratePhysicalDevices();
		physicalDevice = selectMaxRatedDevice();
		findQueueFamilies();
	}
	VkPhysicalDevice* PhysicalDevice::getDeviceDescriptor()
	{
		return &physicalDevice;
	}
	VkPhysicalDeviceFeatures PhysicalDevice::getSupportedFeatures()
	{
		VkResult result = VK_SUCCESS;
		VkPhysicalDeviceFeatures supportedFeatures;
		vkGetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);
		return supportedFeatures;
	}
	RequiredQueueFamilies* PhysicalDevice::getReqQueueFamilies()
	{
		return &reqQueueFamilies;
	}
	void PhysicalDevice::findQueueFamilies()
	{
		reqQueueFamilies = {};
		uint32_t queueFamilyPropCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropCount, nullptr);
		queueFamilies.resize(queueFamilyPropCount);
		std::vector<VkQueueFamilyProperties> props;
		props.resize(queueFamilyPropCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropCount, props.data());
		unsigned int i = 0; 
		for (const auto& family : props) {
			QueueFamily fam{
				i,
				family.queueFlags,
				family.queueCount
			};
			queueFamilies.push_back(fam);
			if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				reqQueueFamilies.graphics = fam;
			}
			if (family.queueFlags & VK_QUEUE_COMPUTE_BIT) {
				reqQueueFamilies.compute = fam;
			}
			if (family.queueFlags & VK_QUEUE_TRANSFER_BIT) {
				reqQueueFamilies.transfer = fam;
			}
			VkBool32 presentSupport = false;
			//vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			if (presentSupport)
			{
				reqQueueFamilies.present = fam;
			}
		}
		i++;
	}
	void PhysicalDevice::enumeratePhysicalDevices()
	{
		uint32_t physDeviceCount = 0;
		vkEnumeratePhysicalDevices(*(instance->getVkInstance()), &physDeviceCount, nullptr);
		if (physDeviceCount < 0) { throw "Cannot find any vulkan device"; }
		devicesDescriptors.resize(physDeviceCount);
		vkEnumeratePhysicalDevices(*(instance->getVkInstance()), &physDeviceCount, &devicesDescriptors[0]);
		LOG_INFO(std::string("Devices count: ") + std::to_string(physDeviceCount));
	}
	VkPhysicalDevice PhysicalDevice::selectMaxRatedDevice()
	{
		int size = devicesDescriptors.size();
		int* scores = new int[size];
		int i = 0;
		for (const auto& device : devicesDescriptors) {
			if (!isDeviceSuitable(device)) { continue; }
			unsigned int score = 0;
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
				score += 1000;
			}
			score += deviceProperties.limits.maxImageDimension2D;
			score += deviceProperties.limits.maxViewports;
			score += deviceProperties.limits.maxViewportDimensions[0] + deviceProperties.limits.maxViewportDimensions[1];
			scores[i] = score;
			i++;
		}
		int max = scores[0];
		int maxInd = 0;
		for (int i = 0; i < size; i++) {
			if (scores[i] > max) {
				maxInd = i;
			}
		}
		LOG_INFO(std::string("Device rating: ") + std::to_string(max));
		return devicesDescriptors[maxInd];
		delete[] scores;
	}
	bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {
		return true;
	}
}