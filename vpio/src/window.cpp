#include "window.h"

#include <GLFW/glfw3.h>

#define GUP(w) glfwGetWindowUserPointer(w)
#define WINDOW reinterpret_cast<GLFWwindow*>(_BaseWindow)

namespace instances {
	Window* _Window;
}

namespace callbacks {
	auto WindowPositionCallback(GLFWwindow* win, int x, int y){
		static_cast<Window*>(GUP(win))->WindowPositionCallback(reinterpret_cast<IBaseWindowImpl*>(win), x, y);
	}
	
	auto WindowSizeCallback(GLFWwindow* win, int x, int y){
		static_cast<Window*>(GUP(win))->WindowSizeCallback(reinterpret_cast<IBaseWindowImpl*>(win), x, y);
	}
}
void Window::InitializeWindow(const std::string& name, int w, int h, int x, int y) {
	_Name = name; _Size = { w, h }; _Position = { x, y };

	if (!glfwInit())
		throw WindowError("Cannot initialize glfw", this);
	
	_BaseWindow = reinterpret_cast<IBaseWindowImpl*>(glfwCreateWindow(w, h, name.c_str(), nullptr, nullptr));
	glfwSetWindowUserPointer(reinterpret_cast<GLFWwindow*>(_BaseWindow), this);
	glfwSetWindowSizeCallback(WINDOW, callbacks::WindowSizeCallback);
	glfwSetWindowPosCallback(WINDOW, callbacks::WindowPositionCallback);
}

IBaseWindowImpl* Window::InitializeWindow(IBaseWindowImpl* win) {
	_BaseWindow = win;
	
	_Name = "Window was created for ll pointer, title is dead(";
	
	int w, h;
	glfwGetWindowSize(WINDOW, &w, &h);
	_Size = { w, h };

	int x, y;
	glfwGetWindowPos(WINDOW, &x, &y);
	_Position = { x, y };

	glfwSetWindowUserPointer(reinterpret_cast<GLFWwindow*>(_BaseWindow), this);
	glfwSetWindowSizeCallback(WINDOW, callbacks::WindowSizeCallback);
	glfwSetWindowPosCallback(WINDOW, callbacks::WindowPositionCallback);

	return 0;
}

void Window::WindowSizeCallback(IBaseWindowImpl* window, int w, int h) {
	// there EventSystem call "windowResized"
	this->_Size = { w, h };
}

void Window::WindowPositionCallback(IBaseWindowImpl* window, int x, int y) {
	// there EventSystem call "windowPositionChanged"
	this->_Position = {x, y};
}

void Window::Show() {
	glfwShowWindow(WINDOW);
}

void Window::Hide() {
	glfwHideWindow(WINDOW);
}

void Window::GetWindowSize(int& x, int& y) {
	x, y = _Size.first, _Size.second;
}

std::pair<int, int> Window::GetWindowSize() {
	return _Size;
}

void Window::GetWindowPosition(int& x, int& y) {
	x, y = _Position.first, _Position.second;
}

std::pair<int, int> Window::GetWindowPosition() {
	return _Position;
}

IBaseWindowId Window::GetWindowId() {
	return reinterpret_cast<IBaseWindowId>(_BaseWindow);
}

std::string Window::GetWindowName() {
	return _Name;
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose(WINDOW);
}

void Window::SetContextCurrent() {
	glfwMakeContextCurrent(WINDOW);
}

void Window::GetFrameBufferSize(int& w, int& h) {
	glfwGetFramebufferSize(WINDOW, &w, &h);
}

void Window::SwapBuffer() {
	glfwSwapBuffers(WINDOW);
}

VPIO_API IWindow* GetWindowForCurrentContext() {
	//return GetWindowInterface() glfwGetCurrentContext();
	return 0;
}

IWindow* GetWindowInterface() {
	return reinterpret_cast<IWindow*>(instances::_Window);
}

void InitializeWindowInterface() {
	if (!instances::_Window)
		instances::_Window = new Window();
}
