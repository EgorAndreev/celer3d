#include "VulkanGraphics.hpp"
#include "Win32/Win32VulkanWindow.hpp"
#include "log.hpp"
namespace celer {

	void VulkanGraphics::Init()
	{
		Win32VulkanWindow wnd;
		wnd.CreateAppWindow(800, 600, "testwnd");
		wnd.DestroyAppWindow();
		Version appVer = Version(1, 0, 0);
		VulkanInstance = Instance("Test", appVer);
		physicalDevice = PhysicalDevice(&VulkanInstance);
		logicalDevice = LogicalDevice(&physicalDevice);
	}
	void VulkanGraphics::Destroy()
	{

	}
	void VulkanGraphics::Update() {

	}

}