/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include "llapi/EventAPI.h"
#include "llapi/GlobalServiceAPI.h"
#include "llapi/mc/ServerNetworkHandler.hpp"
#include "llapi/mc/Types.hpp"

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *
 */
void PluginInit()
{
    Event::ServerStartedEvent::subscribe([](Event::ServerStartedEvent ev)
    {
        Global<ServerNetworkHandler>->setMaxNumPlayers(Global<ServerNetworkHandler>->getActiveAndInProgressPlayerCount(mce::UUID::EMPTY) + 1);
        return true;
    });
    Event::PlayerPreJoinEvent::subscribe([](Event::PlayerPreJoinEvent ev)
    {
        Global<ServerNetworkHandler>->setMaxNumPlayers(Global<ServerNetworkHandler>->getActiveAndInProgressPlayerCount(mce::UUID::EMPTY) + 1);
        return true;
    });
    Event::PlayerLeftEvent::subscribe([](Event::PlayerLeftEvent ev)
    {
        Global<ServerNetworkHandler>->setMaxNumPlayers(Global<ServerNetworkHandler>->getActiveAndInProgressPlayerCount(mce::UUID::EMPTY) + 1);
        return true;
    });
}

#include "llapi/HookAPI.h"

THook(int, "?NetworkDefaultMaxConnections@SharedConstants@@3HB") {
    return 2147483647;
}
