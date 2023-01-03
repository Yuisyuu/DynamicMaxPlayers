/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/LoggerAPI.h>

 // We recommend using the global logger.
extern Logger logger;

#include "llapi/EventAPI.h"
#include "llapi/GlobalServiceAPI.h"
#include "llapi/mc/ServerNetworkHandler.hpp"

void setMaxNumPlayers(int plus = 0)
{
    Global<ServerNetworkHandler>->setMaxNumPlayers(Global<ServerNetworkHandler>->getActiveAndInProgressPlayerCount(mce::UUID::EMPTY) + plus);
}

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit()
{
    Event::ServerStartedEvent::subscribe([](Event::ServerStartedEvent ev)
    {
        setMaxNumPlayers(1);
        return true;
    });
    Event::PlayerPreJoinEvent::subscribe([](Event::PlayerPreJoinEvent ev)
    {
        setMaxNumPlayers(1);
        return true;
    });
    Event::PlayerLeftEvent::subscribe([](Event::PlayerLeftEvent ev)
    {
        setMaxNumPlayers();
        return true;
    });
}

TInstanceHook(int, "?setMaxNumPlayers@ServerNetworkHandler@@QEAAHH@Z", ServerNetworkHandler, int a2)
{
    int ActiveAndInProgressPlayerCount = this->getActiveAndInProgressPlayerCount(mce::UUID::EMPTY);
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
        this->updateServerAnnouncement();
        (*(void(__fastcall**)(unsigned long long, unsigned long long))(**((unsigned long long**)this + 56) + 40i64))(
            *((unsigned long long*)this + 56),
            *((unsigned int*)this + 192));
    }
    return v5;
}