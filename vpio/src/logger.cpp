#include "logger.h"

#define LOGGER_NAME "VPIO"

namespace instances {
	VPLogger* _Logger;
}

void VPLogger::Initialize() {
	_Logger = spdlog::stdout_color_mt(LOGGER_NAME);
}

void VPLogger::Shutdown() {
	delete this;
}

IVPLogger* GetLoggerInterface() {
	return instances::_Logger;
}

void InitializeLoggerInstance() {
	if (!instances::_Logger) {
		instances::_Logger = new VPLogger();
		instances::_Logger->Initialize(); //TODO: REMEMBER ABOUT THIS!!!
	}
}

void VPLogger::LogInfo(const std::string& str) {
	_Logger->info(str);
}

void VPLogger::LogWarning(const std::string& str) {
	_Logger->warn(str);
}

void VPLogger::LogCritical(const std::string& str) {
	_Logger->critical(str);
}

void VPLogger::LogError(const std::string& str) {
	_Logger->error(str);
}

void VPLogger::LogTrace(const std::string& str) {
	_Logger->trace(str);
}

void VPLogger::EnableBacktrace(size_t messagesNum) {
	_Logger->enable_backtrace(messagesNum);
}

void VPLogger::DisableBacktrace() {
	_Logger->disable_backtrace();
}

void VPLogger::DumpBacktrace() {
	_Logger->dump_backtrace();
}

void* VPLogger::GetLogger() {
	return _Logger.get();
}

std::string VPLogger::Format(const char* fmt, ...) {
	std::array<char, 1024> out{};

	va_list args;
	va_start(args, fmt);
	vsprintf_s(out.data(), out.size(), fmt, args);
	va_end(args);

	return std::string(out.data());
}
