#include <thread>
#include <Windows.h>

#include "engine.h"

BOOL APIENTRY DllMain( HMODULE h_module, DWORD  ul_reason_for_call, LPVOID lp_reserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        InitializeEngineInstance();
        break;
    }
    return TRUE;
}