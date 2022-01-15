#pragma once 
#include <string>
#include "ISurface.hpp"
#include "Vulkan/Instance.hpp"
namespace celer {
	class IWindow {
	public:
		virtual void CreateAppWindow(const unsigned int width, const unsigned int height, const std::string title, Instance* instance) = 0;
		virtual void DestroyAppWindow() = 0;
		virtual ISurface* GetWindowSurface() = 0;
	};
}