#include "Instance.hpp"
namespace celer {
	void Instance::createInstance()
	{
		VkResult result = VK_SUCCESS;
		VkApplicationInfo appInfo = {};
		VkInstanceCreateInfo instanceCreateInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = AppName.c_str();
		appInfo.applicationVersion = VK_MAKE_VERSION(AppVersion.major, AppVersion.minor, AppVersion.micro);
		appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
		if (result != VK_SUCCESS) {
			throw "Cannot create instance!";
		}

	}
	VkInstance* Instance::getVkInstance()
	{
		return &instance;
	}
	void Instance::cleanup()
	{
	}
}