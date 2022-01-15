#pragma once
namespace celer{
	class IGraphics {
	public:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;
	};
}