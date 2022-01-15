#pragma once
namespace celer {
	enum WindowEventType {
		KeyCallback,
		CursorPosCallback,
		CursorEnterCallback,
		MouseButtonCallback,
		MouseScrollCallback,
		WindowCloseCallback,
		WindowSizeCallback,
		WindowPosCallback,
		WindowMaxSizeCallback,
		WindowMinSizeCallback,
		WindowFocusCallback,
		EventTypesCount
	};
}