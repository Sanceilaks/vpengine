#include <engine.h>
#include <window.h>
#include <input_system.h>


#include <Windows.h>
#include <iostream>

auto main() -> int {
	setlocale(0, "");

	try {
		GetEngineInterface()->Initialize({ "MineGame" });
		GetEngineInterface()->Run();
	} catch (std::exception& e) {
		ShellExecute(0, 0, std::string("https://stackoverflow.com/search?q=").append(e.what()).c_str(), 0, 0, SW_SHOWNORMAL);
	}
}

