#pragma once

#include "window.h"

#ifdef GAPI_EXPORT
#define GAPI_API __declspec(dllexport)
#else
#define GAPI_API __declspec(dllimport)
#endif

class IGraphicDevice {
public:
	virtual void ProcessFrame() = 0;

	virtual void Initialize() = 0;
	virtual void OnContextCreated() = 0;
	virtual void Shutdown() = 0;
};

struct GraphicDeviceInitializatonData {
	IWindow* _Window;
};

extern "C" GAPI_API IGraphicDevice * GetGraphicDevice(GraphicDeviceInitializatonData && data = {});

#ifdef GAPI_EXPORT
class GraphicDevice : public IGraphicDevice {
	IWindow* _Window;
	uint64_t _FrameNumber;
public:
	GraphicDevice(IWindow* window);

	void ProcessFrame() override;

	void Initialize() override;
	void OnContextCreated() override;

	void Shutdown() override;
};
#endif