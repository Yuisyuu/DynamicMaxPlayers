#pragma comment(lib, "../SDK/lib/bedrock_server_api.lib")
#pragma comment(lib, "../SDK/lib/bedrock_server_var.lib")
#pragma comment(lib, "../SDK/lib/SymDBHelper.lib")
#pragma comment(lib, "../SDK/lib/LiteLoader.lib")

#include <llapi/HookAPI.h>
#include <llapi/mc/ServerNetworkHandler.hpp>
#include <llapi/mc/Types.hpp>

TInstanceHook(__int64, "?setMaxNumPlayers@ServerNetworkHandler@@QEAAHH@Z", ServerNetworkHandler, int a2)
{
    int ActiveAndInProgressPlayerCount = getActiveAndInProgressPlayerCount(mce::UUID::EMPTY);
    unsigned int v5 = 0;
    if (a2 <= INT_MAX)
    {
        if (a2 < ActiveAndInProgressPlayerCount)
        {
            a2 = ActiveAndInProgressPlayerCount;
            v5 = -1;
        }
    }
    else
    {
        a2 = INT_MAX;
        v5 = 1;
    }
    int v6 = *((unsigned long*)this + 192);
    *((unsigned long*)this + 192) = a2;
    if (v6 != a2)
    {
        updateServerAnnouncement();
        (*(void(__fastcall**)(unsigned long long, unsigned long long))(**((unsigned long long**)this + 56) + 40i64))(
            *((unsigned long long*)this + 56),
            *((unsigned int*)this + 192));
    }
    return v5;
}
