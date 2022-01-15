#include "Vulkan/PhysicalDevice.hpp"
namespace celer {
	class LogicalDevice {
	public:
		LogicalDevice(PhysicalDevice* phDevice) : physicalDevice(phDevice) { createLogicalDevice(); }
		LogicalDevice() {}
	private:
		void createLogicalDevice();
		void destroyLogicalDevice();
		PhysicalDevice* physicalDevice;
		std::vector<VkLayerProperties> instanceLayers;
		std::vector<VkExtensionProperties> instanceExtensions;
		VkDevice device;
	};
}