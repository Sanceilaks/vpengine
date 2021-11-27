#include "input_system.h"

#include <GLFW/glfw3.h>

namespace instances {
	InputSystem* _InputSystem;
}

void InputSystem::Initialize(IWindow* window) {
	if (!window)
		throw std::exception("Cannot initialize InputSystem!");
	_Window = reinterpret_cast<Window*>(window);
}

uint64_t InputSystem::GetCurrentInputFrame() {
	return _CurrentFrame;
}

void InputSystem::PollEvents() {
	_Keys.fill(0);
	_Frames.fill(0);
	_CurrentFrame++;

	glfwPollEvents();
}

IInputSystem* GetInputSystemInterface() {
	return instances::_InputSystem;
}

void InitializeInputSystemInterface() {
	if (!instances::_InputSystem)
		instances::_InputSystem = new InputSystem();
}
