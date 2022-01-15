#pragma once
#include <vector>
#include "IGraphics.hpp"
#include "Vulkan/LogicalDevice.hpp"
#include <Vulkan/Instance.hpp>
#include <Vulkan/PhysicalDevice.hpp>
namespace celer {
	class VulkanGraphics : IGraphics{
	public:
		VulkanGraphics() {
			Init();
		}
		void Init() override;
		void Update() override;
		void Destroy() override;
	private:
		Instance VulkanInstance; 
		PhysicalDevice physicalDevice;
		LogicalDevice logicalDevice;
	};
}