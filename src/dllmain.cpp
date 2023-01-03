/**
 * @file DLLMain.cpp
 * @note DO NOT modify or remove this file!
 */

#include <llapi/LoggerAPI.h>
#include <llapi/ServerAPI.h>

#include "version.hpp"

#pragma comment(lib, "../SDK/lib/bedrock_server_api.lib")
#pragma comment(lib, "../SDK/lib/bedrock_server_var.lib")
#pragma comment(lib, "../SDK/lib/SymDBHelper.lib")
#pragma comment(lib, "../SDK/lib/LiteLoader.lib")

void PluginInit();

Logger logger(PLUGIN_NAME);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return false;
    ll::registerPlugin(
        PLUGIN_NAME,
        PLUGIN_INTRODUCTION,
        ll::Version(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_REVISION, PLUGIN_LLVERSION_STATUS),
        std::map<std::string, std::string>{
            {"Author", PLUGIN_AUTHOR},
    });
    return true;
}

extern "C"
{
    _declspec(dllexport) void onPostInit()
    {
        PluginInit();
    }
}
