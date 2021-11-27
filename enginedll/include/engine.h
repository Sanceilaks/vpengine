#pragma once
#include <memory>
#include <string>

#ifdef ENGINEDLL_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif

struct EngineInitializationData {
	std::string AppName;
	struct { int w, h; } WindowSize = {800, 600};
	struct { int x, y; } WindowPosition = {100, 100};
};

class IEngine {
public:
	virtual void Initialize(EngineInitializationData&& data) = 0;
	virtual void Shutdown() = 0;

	virtual void Run() = 0;
	virtual bool IsRunned() = 0;
};

#ifdef ENGINEDLL_EXPORTS
class Engine : IEngine {
	bool _IsRunned = false;
public:
	void Initialize(EngineInitializationData&& data) override;
	void Shutdown() override;
	void Run() override;
	bool IsRunned() override;
};
#endif

extern "C" ENGINEDLL_API IEngine * GetEngineInterface();

#ifdef ENGINEDLL_EXPORTS
void InitializeEngineInstance();
#endif