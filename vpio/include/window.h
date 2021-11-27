#pragma once
#include <string>

#ifdef VPIO_EXPORTS
#define VPIO_API __declspec(dllexport)
#else
#define VPIO_API __declspec(dllimport)
#endif


using IBaseWindowImpl = uint32_t;
using IBaseWindowId = uint32_t;
using Size = struct { int w, h; };

class IWindow {
public:
	IWindow() = default;
	virtual void InitializeWindow(const std::string& name, int w, int h, int x = 100, int y = 100) = 0;
	virtual IBaseWindowImpl* InitializeWindow(IBaseWindowImpl* win) = 0;

	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void GetWindowSize(int& x, int& y) = 0;
	virtual std::pair<int, int> GetWindowSize() = 0;
	virtual void GetWindowPosition(int& x, int& y) = 0;
	virtual std::pair<int, int> GetWindowPosition() = 0;
	virtual IBaseWindowId GetWindowId() = 0;
	virtual std::string GetWindowName() = 0;
	virtual bool ShouldClose() = 0;
	virtual void SetContextCurrent() = 0;
	virtual void GetFrameBufferSize(int& w, int& h) = 0;
	virtual void SwapBuffer() = 0;
};

extern "C" VPIO_API IWindow * GetWindowForCurrentContext();

class WindowError : public std::exception {
	std::string _WindowName;
	IBaseWindowId _WindowId;
public:
	WindowError(const std::string& what, IWindow* window) : std::exception(what.c_str()) {
		_WindowName = window->GetWindowName();
		_WindowId = window->GetWindowId();
	}

	IBaseWindowId GetWindowId() const {
		return _WindowId;
	}

	std::string GetWindowName() const {
		return _WindowName;
	}
};

#if defined(VPIO_EXPORTS)
class Window : public IWindow {
	IBaseWindowImpl* _BaseWindow = nullptr;
	
	std::string _Name;
	std::pair<int, int> _Size;
	std::pair<int, int> _Position;
public:
	void InitializeWindow(const std::string& name, int w, int h, int x, int y) override;

	// Not working
	IBaseWindowImpl* InitializeWindow(IBaseWindowImpl* win) override;

	void WindowSizeCallback(IBaseWindowImpl* window, int w, int h);
	void WindowPositionCallback(IBaseWindowImpl* window, int x, int y);
	void Show() override;
	void Hide() override;
	void GetWindowSize(int& x, int& y) override;
	std::pair<int, int> GetWindowSize() override;
	void GetWindowPosition(int& x, int& y) override;
	std::pair<int, int> GetWindowPosition() override;
	IBaseWindowId GetWindowId() override;
	std::string GetWindowName() override;
	bool ShouldClose() override;
	void SetContextCurrent() override;
	void GetFrameBufferSize(int& w, int& h) override;
	void SwapBuffer() override;
};
#endif

extern "C" VPIO_API IWindow * GetWindowInterface();

#ifdef VPIO_EXPORTS
extern void InitializeWindowInterface();
#endif