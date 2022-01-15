#pragma once
#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include "Version.hpp"
namespace celer {
	class Instance {
	public:
		Instance() {}
		Instance(std::string appName, Version appVersion) : AppName(appName), AppVersion(appVersion) { createInstance(); }
		void createInstance();
		VkInstance* getVkInstance();
		void cleanup();
	private:
		VkInstance instance = VK_NULL_HANDLE;
		std::string AppName;
		Version AppVersion;
		std::vector<VkLayerProperties> instanceLayers;
		std::vector<VkExtensionProperties> instanceExtensions;
	};
}