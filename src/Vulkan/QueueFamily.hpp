#include "Vulkan/vulkan.h"
namespace celer {
	
	struct QueueFamily {
		unsigned int queueFamilyIndex;
		VkQueueFlags queueFamilyFlags;
		unsigned int queuesCount;
	};
	struct RequiredQueueFamilies {
		QueueFamily graphics;
		QueueFamily present;
		QueueFamily transfer;
		QueueFamily compute;
	};
}