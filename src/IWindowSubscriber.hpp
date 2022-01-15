#pragma once
#include "WindowEventType.hpp"
namespace celer {
	class IWindowSubscriber {
	public:
		virtual void Update(WindowEventType type) = 0;
	};
}
