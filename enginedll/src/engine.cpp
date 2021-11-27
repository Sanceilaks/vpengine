#include "engine.h"

#include "input_system.h"
#include "logger.h"

#include "graphicdevice.h"

namespace instances {
	Engine* _EngineInstance;

	IWindow* _Window;
	IInputSystem* _InputSystem;
	IVPLogger* _Logger;
	IGraphicDevice* _GraphicDevice;
}

using namespace instances;

IEngine* GetEngineInterface() {
	return reinterpret_cast<IEngine*>(_EngineInstance);
}

void Engine::Initialize(EngineInitializationData&& data) {
	VPIO_LOG_INFO("Initializing engine for app \"%s\"", data.AppName.c_str());

	_Logger = GetLoggerInterface();

	_Window = GetWindowInterface();
	_InputSystem = GetInputSystemInterface();

	_Window->InitializeWindow(data.AppName, data.WindowSize.w, data.WindowSize.h, data.WindowPosition.x, data.WindowPosition.y);
	_InputSystem->Initialize(GetWindowInterface());

	_GraphicDevice = GetGraphicDevice({_Window});
	_GraphicDevice->Initialize();
}

void Engine::Shutdown() {
	
}

void Engine::Run() {
	_IsRunned = true;

	_Window->SetContextCurrent();
	_GraphicDevice->OnContextCreated();

	while (IsRunned()) {
		_InputSystem->PollEvents();
		_IsRunned = !_Window->ShouldClose();

		_GraphicDevice->ProcessFrame();
	}
}

bool Engine::IsRunned() {
	return _IsRunned;
}

void InitializeEngineInstance() {
	if (!_EngineInstance)
		_EngineInstance = new Engine();
}
