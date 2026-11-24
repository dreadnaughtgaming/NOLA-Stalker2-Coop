#pragma once
#include <string_view>

namespace s2m_quest_pickup
{
    inline bool native_inventory(std::string_view sid)
    {
        return sid == "E07_PsyEmitter";
    }

    inline bool host_ground(double x, double y, double z, std::string_view cls, std::string_view mesh)
    {
        if (cls != "BP_StaticItemContainer_C") return false;
        // Stock quest pickups identified in #92. The rifle mesh is also used
        // by ordinary weapons, so require the original placement as well.
        auto near = [=](double px, double py, double pz) {
            double dx = x - px, dy = y - py, dz = z - pz;
            return dx * dx + dy * dy + dz * dz <= 30 * 30;
        };
        return (mesh == "SM_mar" && near(405569, 547157, 502)) ||
               (mesh == "SM_que_emitter_01" && near(492067, 512052, 1128));
    }
}
