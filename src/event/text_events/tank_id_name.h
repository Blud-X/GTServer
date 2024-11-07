#pragma once
#include <event/event_pool.h>

namespace GrowtopiaServer::events {
    void tank_id_name(EventContext& ctx) {
        if (ctx.m_parser.Get("tankIDName").empty()) {
            ctx.m_player->v_sender.OnConsoleMessage("Where would you like to go?");

            // Send client to world menu
            std::string worldData = "default|START\n";
            worldData.append("add_filter\n");
            worldData.append("add_heading|Top Worlds\n");
            worldData.append("add_floater|START|0|0.7|655565\n");
            ctx.m_player->v_sender.OnRequestWorldSelectMenu(worldData);
        }
    }
}