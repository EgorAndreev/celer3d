#include "Win32VulkanWindow.hpp"
#include <thread>
#include <iostream>
#include "log.hpp"
#define VK_USE_PLATFORM_WIN32_KHR
#include "vulkan/vulkan.h"

namespace celer {
    HINSTANCE Win32VulkanWindow::win32Inst;
    HWND Win32VulkanWindow::wndHndl;
    bool Win32VulkanWindow::wndShouldClose;

	void Win32VulkanWindow::CreateAppWindow(unsigned int width, unsigned int height, std::string title, Instance* instance)
	{
        LOG_INFO("Starting window thread...");
        win32thread = std::thread(&initWin32Wnd, width, height, title, instance->getVkInstance());
	}
	void Win32VulkanWindow::DestroyAppWindow()
	{
        LOG_INFO("Manual destroy window");
        wndShouldClose = true;
        win32thread.join();
	}
	ISurface* Win32VulkanWindow::GetWindowSurface()
	{
		return (ISurface*)&surface;
	}
	void Win32VulkanWindow::initWin32Wnd(const unsigned int width, const unsigned int height, const std::string title, VkInstance* instance)
	{
        win32Inst = GetModuleHandle(NULL);
        const TCHAR  CLASS_NAME[] = "Window Class";
        WNDCLASS wc = { };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = win32Inst;
        wc.lpszClassName = CLASS_NAME;
        RegisterClass(&wc);
        wndHndl = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            title.c_str(),    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style
            width, height,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,       // Parent window    
            NULL,       // Menu
            win32Inst,  // Instance handle
            NULL        // Additional application data
        );
        if (wndHndl == NULL) {
            throw "Cannot create window!";
        }

        ShowWindow(wndHndl, SW_NORMAL);
        VkWin32SurfaceCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;
        createInfo.hinstance = win32Inst;
        createInfo.hwnd = wndHndl;
        
        vkCreateWin32SurfaceKHR(*instance, &createInfo, nullptr, surface);
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            if (wndShouldClose){
                DestroyWindow(wndHndl);
                PostQuitMessage(0);
                return;
            }
            LOG_INFO("Disp. messages");
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return;
	}
    LRESULT Win32VulkanWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            LOG_INFO("WM_DESTROY called");
            PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            LOG_INFO("WM_CLOSE called");
            DestroyWindow(hwnd);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
            break;
        }

        return 0;
    }
}