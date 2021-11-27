#include "../include/graphicdevice.h"

#include <iostream>

#include <logger.h>

#include <gl/glew.h>

GraphicDevice* _GraphicDevice;

GAPI_API IGraphicDevice* GetGraphicDevice(GraphicDeviceInitializatonData&& data) {
	if (_GraphicDevice == nullptr) _GraphicDevice = new GraphicDevice(data._Window);
	return _GraphicDevice;
}

GraphicDevice::GraphicDevice(IWindow* window) {
	if (window == nullptr) VPIO_LOG_CRITICAL("[GraphicDevice] Window is nullptr!");
	_Window = window;
}

void GraphicDevice::Initialize() {

}

void GraphicDevice::OnContextCreated() {
	glewExperimental = true;
	if (auto res = glewInit(); res != GLEW_OK) {
		VPIO_LOG_CRITICAL("[GraphicDevice] Cannot initialize internal api with error \"%s\"", glewGetErrorString(res));
	}
}

void GraphicDevice::Shutdown() {

}

void GraphicDevice::ProcessFrame() {
	int bufferSizeX, bufferSizeY; _Window->GetFrameBufferSize(bufferSizeX, bufferSizeY);
	glViewport(0, 0, bufferSizeX, bufferSizeY);

	glClearColor(0.f, 1.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	_Window->SwapBuffer();
}