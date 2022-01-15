#pragma once
#include "Vulkan/Instance.hpp"
#include <map>
#include "QueueFamily.hpp"
namespace celer {

	class PhysicalDevice {
	public:
		PhysicalDevice() {}
		PhysicalDevice(Instance* inst) :instance(inst) { initDevice(); }
		void initDevice();
		VkPhysicalDevice* getDeviceDescriptor();
		VkPhysicalDeviceFeatures getSupportedFeatures();
		RequiredQueueFamilies* getReqQueueFamilies();
	private:
		
		void findQueueFamilies();
		std::vector<VkPhysicalDevice> devicesDescriptors;
		VkPhysicalDevice physicalDevice;
		Instance* instance;
		void enumeratePhysicalDevices();
		VkPhysicalDevice selectMaxRatedDevice();
		bool isDeviceSuitable(VkPhysicalDevice device);
		VkPhysicalDevice device;
		std::vector<QueueFamily> queueFamilies;
		RequiredQueueFamilies reqQueueFamilies;
	};
}