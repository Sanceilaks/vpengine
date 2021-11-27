#pragma once
#include <array>

#include "window.h"

#ifdef VPIO_EXPORTS
#define VPIO_API __declspec(dllexport)
#else
#define VPIO_API __declspec(dllimport)
#endif

class IInputSystem {
public:
	virtual void Initialize(IWindow* window) = 0;
	virtual uint64_t GetCurrentInputFrame() = 0;
	virtual void PollEvents() = 0;
};

#ifdef VPIO_EXPORTS
inline constexpr uint32_t mouse_buttons_offset = 1024;
inline constexpr uint32_t total_keys_array_size = 1032;

class InputSystem : public IInputSystem {
	Window* _Window = nullptr;

	std::array<bool, total_keys_array_size> _Keys;
	std::array<uint64_t, total_keys_array_size> _Frames;
	uint64_t _CurrentFrame = 0;

public:
	void Initialize(IWindow* window) override;
	uint64_t GetCurrentInputFrame() override;
	void PollEvents() override;
};

#endif

extern "C" VPIO_API IInputSystem * GetInputSystemInterface();

#ifdef VPIO_EXPORTS
extern void InitializeInputSystemInterface();
#endif