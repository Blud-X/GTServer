#pragma once 
#include <enet/enet.h>
#include <proton/packet.h>
#include <proton/variant.h>
#include <proton/utils/text_scanner.h>
#include <player/additional/packet_sender.h>

namespace GrowtopiaServer {
    class VariantListSender : public PacketSender{
    public:
        VariantListSender(ENetPeer* peer) : 
            m_peer(peer),
            PacketSender{ peer } {
        }
        ~VariantListSender() = default;

        void OnSuperMainStart(
            const uint32_t& items_dat, 
            const std::string& cdn_host, 
            const std::string& cdn_cache, 
            const std::string& blocked, 
            const std::string& settings, 
            const uint32_t& player_tribute)
        {
            this->SendVariant({ 
                "OnSuperMainStartAcceptLogonHrdxs47254722215a",
                items_dat,
                cdn_host,
                cdn_cache,
                blocked,
                settings,
                player_tribute
            });
        }
        void OnDialogRequest(const std::string& data, int32_t delay = 0) {
            this->SendVariant({
                "OnDialogRequest",
                data
            }, delay);
        }
        void OnConsoleMessage(const std::string& message, uint32_t delay = 0) {
            this->SendVariant({ 
                "OnConsoleMessage",
                message
            }, delay);
        }
        void OnTextOverlay(const std::string& message, uint32_t delay = 0) {
            this->SendVariant({ 
                "OnTextOverlay",
                message
            }, delay);
        }
        void OnAddNotification(const std::string& message, const std::string& rttex, const std::string& audio) {
            this->SendVariant({
                "OnAddNotification",
                rttex,
                message,
                audio
                });
        }
        void OnTalkBubble(const uint32_t& net_id, const std::string& message, const bool& append = false, uint32_t delay = 0) {
            this->SendVariant({ 
                "OnTalkBubble",
                net_id,
                message,
                0,
                append
            }, delay);
        }
        void OnAction(const uint32_t& net_id, const std::string& actionthing) {
            this->SendVariant({
                "OnAction",
                net_id,
                actionthing
                });
        }
        void OnRequestWorldSelectMenu(const std::string& data, int32_t delay = 0) {
            this->SendVariant({
                "OnRequestWorldSelectMenu",
                data
            }, delay);
        }
        void OnFailedToEnterWorld(const bool& val) {
            this->SendVariant({
                "OnFailedToEnterWorld",
                val ? 1 : 0
            });
        }
        void OnSpawn(const TextScanner& data) {
            this->SendVariant({
                "OnSpawn",
                data.get_all_raw()
            }, -1);
        }
        void OnRemove(const TextScanner& data) {
            this->SendVariant({
                "OnRemove",
                data.get_all_raw()
            });
        }
        void OnInvis(const int32_t& net_id, const int32_t& delay, int active) {
            this->SendVariant({
                "OnInvis",
                active,
                }, delay, net_id);
        }
        void OnStoreRequest(const std::string& text) {
            this->SendVariant({
                "OnStoreRequest",
                text,
                });
        }
        
        void OnKilled(const int32_t& net_id, const int32_t& delay) {
            this->SendVariant({
                "OnKilled",
                1
            }, delay, net_id);
        }
        void OnZoomCamera(const float& size, const int32_t& speedMS, const int32_t& delay = 0) {
            this->SendVariant({ 
                "OnZoomCamera",
                size,
                speedMS
            }, delay);
        }
        void OnCountryState(const int32_t& user_id, const std::string& country) {
            this->SendVariant({
                "OnCountryState",
                user_id,
                country
                });
        }
        void OnSetFreezeState(const int32_t& net_id, const int32_t& state, const int32_t& delay = 0) {
            this->SendVariant({
                "OnSetFreezeState",
                state
            }, delay, net_id);
        }
        void OnNameChanged(const int32_t& net_id, const std::string& name, const int32_t& delay = 0) {
            this->SendVariant({
                "OnNameChanged",
                name
            }, delay, net_id);
        }
        void OnSetPos(const int32_t& net_id, const CL_Vec2f& position, const int32_t& delay = 0) {
            this->SendVariant({
                "OnSetPos",
                position
            }, delay, net_id);
        }
        void OnPlayPositioned(const std::string& sound, const uint32_t& net_id, const int32_t& delay = 0) {
            this->SendVariant({
                "OnPlayPositioned",
                fmt::format("audio/{}.wav", sound)
            }, delay, net_id);
        }
        void SetHasGrowID(const bool& active, const std::string& tankIDName, const std::string& tankIDPass) {
            this->SendVariant({
                "SetHasGrowID",
                active ? 1 : 0,
                tankIDName,
                tankIDPass
            });
        }
        void SetRespawnPos(const uint32_t& net_id, const int32_t& tile_index, const int32_t& delay = 0) {
            this->SendVariant({
                "SetRespawnPos",
                tile_index
            }, delay, net_id);
        }
        void OnParticleEffect(const int32_t& particle_id, const CL_Vec2f& position, const int32_t& delay = 0) {
            this->SendVariant({
                "OnParticleEffect",
                particle_id,
                position
            }, delay);
        }
        void OnSetBux(const int32_t& gems, const int32_t& ranks) {
            this->SendVariant({
                "OnSetBux",
                gems,
                2,
                ranks
            });
        }
        void OnSetCurrentWeather(const int32_t& weather) {
            this->SendVariant({
                "OnSetCurrentWeather",
                weather
            });
        }
    private:
        ENetPeer* m_peer;
    };
}