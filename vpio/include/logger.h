#pragma once

#ifdef VPIO_EXPORTS
#define VPIO_API __declspec(dllexport)
#else
#define VPIO_API __declspec(dllimport)
#endif

#include <string>

class IVPLogger {
public:
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void LogInfo(const std::string& str) = 0;
	virtual void LogWarning(const std::string& str) = 0;
	virtual void LogError(const std::string& str) = 0;
	virtual void LogCritical(const std::string& str) = 0;
	virtual void LogTrace(const std::string& str) = 0;
	virtual void EnableBacktrace(size_t messagesNum) = 0;
	virtual void DisableBacktrace() = 0;
	virtual void DumpBacktrace() = 0;
	virtual void* GetLogger() = 0;
	virtual std::string Format(const char* fmt, ...) = 0;
};

#ifdef VPIO_EXPORTS

#include <spdlog/sinks/stdout_color_sinks.h>

class VPLogger : public IVPLogger {
	std::shared_ptr<spdlog::logger> _Logger;
public:
	void Initialize() override;
	void Shutdown() override;
	void LogInfo(const std::string& str) override;
	void LogWarning(const std::string& str) override;
	void LogCritical(const std::string& str) override;
	void LogError(const std::string& str) override;
	void LogTrace(const std::string& str) override;
	void EnableBacktrace(size_t messagesNum) override;
	void DisableBacktrace() override;
	void DumpBacktrace() override;
	void* GetLogger() override;
	std::string Format(const char* fmt, ...) override;
};

#endif

extern "C" VPIO_API IVPLogger * GetLoggerInterface();

#ifdef VPIO_EXPORTS
extern void InitializeLoggerInstance();
#endif

#define VPIO_LOG_INFO(fmt, ...) GetLoggerInterface()->LogInfo(GetLoggerInterface()->Format(fmt, __VA_ARGS__))
#define VPIO_LOG_ERROR(fmt, ...) GetLoggerInterface()->LogError(GetLoggerInterface()->Format(fmt, __VA_ARGS__))
#define VPIO_LOG_CRITICAL(fmt, ...) GetLoggerInterface()->LogCritical(GetLoggerInterface()->Format(fmt, __VA_ARGS__))
#define VPIO_LOG_WARNING(fmt, ...) GetLoggerInterface()->LogWarning(GetLoggerInterface()->Format(fmt, __VA_ARGS__))
#define VPIO_LOG_TRACE(fmt, ...) GetLoggerInterface()->LogTrace(GetLoggerInterface()->Format(fmt, __VA_ARGS__))