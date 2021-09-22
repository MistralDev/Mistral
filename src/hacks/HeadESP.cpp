#include "config.h"
#if ENABLE_VISUALS
#include "common.hpp"

namespace hacks::headesp
{
static settings::Int mode{ "headesp.mode", "0" };
static settings::Float size_scaling{ "headesp.size-scaling", "2" };
static settings::Boolean teammates{ "headesp.teammates", "false" };

static Vector hitp[PLAYER_ARRAY_SIZE];
static Vector minp[PLAYER_ARRAY_SIZE];
static Vector maxp[PLAYER_ARRAY_SIZE];
static bool drawEsp[PLAYER_ARRAY_SIZE];

rgba_t HeadESPColor(CachedEntity *ent)
{
    if (!playerlist::IsDefault(ent))
    {
        return playerlist::Color(ent);
    }
    return colors::green;
}

static void cm()
{
    if (*mode == 0)
        return;
    for (int i = 1; i <= g_IEngine->GetMaxClients(); i++)
    {
        if (g_pLocalPlayer->entity_idx == i)
            continue;
        CachedEntity *pEntity = ENTITY(i);
        if (CE_BAD(pEntity) || !pEntity->m_bAlivePlayer())
        {
            drawEsp[i] = false;
            continue;
        }
        if (pEntity->m_iTeam() == LOCAL_E->m_iTeam() && playerlist::IsDefault(pEntity) && !*teammates)
        {
            drawEsp[i] = false;
            continue;
        }
        if (!pEntity->hitboxes.GetHitbox(0))
            continue;
        hitp[i]    = pEntity->hitboxes.GetHitbox(0)->center;
        minp[i]    = pEntity->hitboxes.GetHitbox(0)->min;
        maxp[i]    = pEntity->hitboxes.GetHitbox(0)->max;
        drawEsp[i] = true;
    }
}

static draw::Texture atlas{ paths::getDataPath("/textures/atlas.png") };

void draw()
{
    if (*mode == 0)
        return;
    for (int i = 1; i <= g_IEngine->GetMaxClients(); i++)
    {
        if (!drawEsp[i])
            continue;
        CachedEntity *pEntity = ENTITY(i);
        if (CE_BAD(pEntity) || !pEntity->m_bAlivePlayer())
            continue;
        if (pEntity == LOCAL_E)
            continue;
        Vector out;
        if (draw::WorldToScreen(hitp[i], out))
        {
            auto distance = pEntity->m_flDistance();
            switch (*mode)
            {
                case 1:
                {
                    float thickness = ((1250.0f * *size_scaling) / (distance + 10)) + 15;
                    draw::Circle(out.x, out.y, 1, hacks::headesp::HeadESPColor(pEntity), thickness, 100);
                    break;
                }
                default:
                {
                    float size = ((2500.0f * *size_scaling) / (distance + 10)) + 15;
                    switch (*mode)
                    {
                        case 2:
                        {
                            int emojiClass = CE_INT(pEntity, netvar.iClass) - 1;
                            draw::RectangleTextured(out.x - size / 2, out.y - size / 2, size, size, colors::white, atlas, emojiClass * 64, 5 * 64, 64, 64, 0);
                            break;
                        }
                        default:
                        {
                            draw::RectangleTextured(out.x - size / 2, out.y - size / 2, size, size, colors::white, atlas, (1 + *mode) * 64, 4 * 64, 64, 64, 0);
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

static InitRoutine init(
    []()
    {
        EC::Register(EC::CreateMove, cm, "cm_headesp", EC::average);
#if ENABLE_VISUALS
        EC::Register(EC::Draw, draw, "draw_headesp", EC::average);
#endif
    });

} // namespace hacks::headesp
#endif
