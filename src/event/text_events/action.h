#pragma once
#include <event/event_pool.h>

namespace GrowtopiaServer::events {
    void action(EventContext& ctx) {
        if (ctx.m_parser.Get("action").empty())
            return;
        const std::string& action = ctx.m_parser.Get("action", 1);
        if (!ctx.m_events->execute(EVENT_TYPE_ACTION, action, ctx)) {
            ctx.m_player->SendLog("unhandled events::generic_text::action: `waction`` -> `w{}``", action);
            return;
        }
    }
}