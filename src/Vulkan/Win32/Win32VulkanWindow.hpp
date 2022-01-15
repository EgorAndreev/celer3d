#pragma once
#include "IWindow.hpp"
#include "../VulkanSurface.hpp"
#include "vulkan/vulkan.h"
#include "windows.h"
#include <thread>
namespace celer {
	class Win32VulkanWindow : IWindow {
	public:
		Win32VulkanWindow()  {}
		void CreateAppWindow(const unsigned int width, const unsigned int height, const std::string title, Instance* instance) override;
		void DestroyAppWindow() override;
		ISurface* GetWindowSurface() override;
	private:
		static void initWin32Wnd(unsigned int width, unsigned int height, std::string title, VkInstance* instance);
		static LRESULT WindowProc(
			HWND hwnd,
			UINT uMsg,
			WPARAM wParam,
			LPARAM lParam
		);
		static VulkanSurface surface;
		static bool wndShouldClose;
		static HWND wndHndl;
		static HINSTANCE win32Inst;
		std::thread win32thread;
	};
}