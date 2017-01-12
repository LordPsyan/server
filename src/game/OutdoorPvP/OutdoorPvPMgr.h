/**
 * MaNGOS is a full featured server for World of Warcraft, supporting
 * the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
 *
 * Copyright (C) 2005-2017  MaNGOS project <https://getmangos.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef WORLD_PVP_MGR_H
#define WORLD_PVP_MGR_H

#include "Common.h"
#include "Policies/Singleton.h"
#include "Timer.h"

/**
 * @brief
 *
 */
enum
{
    TIMER_OPVP_MGR_UPDATE           = MINUTE * IN_MILLISECONDS // 1 minute is enough for us but this might change with wintergrasp support
};

/**
 * @brief
 *
 */
enum OutdoorPvPTypes
{
    OPVP_ID_SI = 0,
    OPVP_ID_EP,
    OPVP_ID_HP,
    OPVP_ID_ZM,
    OPVP_ID_TF,
    OPVP_ID_NA,
    OPVP_ID_GH,

    MAX_OPVP_ID
};

/**
 * @brief
 *
 */
enum OutdoorPvPZones
{
    ZONE_ID_SILITHUS                = 1377,
    ZONE_ID_TEMPLE_OF_AQ            = 3428,
    ZONE_ID_RUINS_OF_AQ             = 3429,
    ZONE_ID_GATES_OF_AQ             = 3478,

    ZONE_ID_EASTERN_PLAGUELANDS     = 139,
    ZONE_ID_STRATHOLME              = 2017,
    ZONE_ID_SCHOLOMANCE             = 2057,

    ZONE_ID_HELLFIRE_PENINSULA      = 3483,
    ZONE_ID_HELLFIRE_RAMPARTS       = 3562,
    ZONE_ID_HELLFIRE_CITADEL        = 3563,
    ZONE_ID_BLOOD_FURNACE           = 3713,
    ZONE_ID_SHATTERED_HALLS         = 3714,
    ZONE_ID_MAGTHERIDON_LAIR        = 3836,

    ZONE_ID_ZANGARMARSH             = 3521,
    ZONE_ID_SERPENTSHRINE_CAVERN    = 3607,
    ZONE_ID_STREAMVAULT             = 3715,
    ZONE_ID_UNDERBOG                = 3716,
    ZONE_ID_SLAVE_PENS              = 3717,

    ZONE_ID_TEROKKAR_FOREST         = 3519,
    ZONE_ID_SHADOW_LABYRINTH        = 3789,
    ZONE_ID_AUCHENAI_CRYPTS         = 3790,
    ZONE_ID_SETHEKK_HALLS           = 3791,
    ZONE_ID_MANA_TOMBS              = 3792,

    ZONE_ID_NAGRAND                 = 3518,

    ZONE_ID_GRIZZLY_HILLS           = 394
};

struct CapturePointSlider
{
    CapturePointSlider() : Value(0.0f), IsLocked(false) {}
    CapturePointSlider(float value, bool isLocked) : Value(value), IsLocked(isLocked) {}

    float Value;
    bool IsLocked;
};

// forward declaration
class Player;
class GameObject;
class Creature;
class OutdoorPvP;

/**
 * @brief
 *
 */
typedef std::map<uint32 /*capture point entry*/, CapturePointSlider /*slider value and lock state*/> CapturePointSliderMap;

class OutdoorPvPMgr
{
    public:
        /**
         * @brief
         *
         */
        OutdoorPvPMgr();
        /**
         * @brief
         *
         */
        ~OutdoorPvPMgr();

        /**
         * @brief load all outdoor pvp scripts
         *
         */
        void InitOutdoorPvP();

        /**
         * @brief called when a player enters an outdoor pvp area
         *
         * @param player
         * @param zoneId
         */
        void HandlePlayerEnterZone(Player* player, uint32 zoneId);

        /**
         * @brief called when player leaves an outdoor pvp area
         *
         * @param player
         * @param zoneId
         */
        void HandlePlayerLeaveZone(Player* player, uint32 zoneId);

        /**
         * @brief return assigned outdoor pvp script
         *
         * @param zoneId
         * @return OutdoorPvP
         */
        OutdoorPvP* GetScript(uint32 zoneId);

        /**
         * @brief
         *
         * @param diff
         */
        void Update(uint32 diff);

        /**
         * Save and load capture point slider
         *
         * @param entry
         * @param value
         */
        CapturePointSliderMap const* GetCapturePointSliderMap() const { return &m_capturePointSlider; }
        void SetCapturePointSlider(uint32 entry, CapturePointSlider value) { m_capturePointSlider[entry] = value; }

    private:
        /**
         * @brief return assigned outdoor pvp script
         *
         * @param zoneId
         * @return OutdoorPvP
         */
        OutdoorPvP* GetScriptOfAffectedZone(uint32 zoneId);

        OutdoorPvP* m_scripts[MAX_OPVP_ID]; /**< contains all outdoor pvp scripts */

        /**
         * @brief
         *
         */
        CapturePointSliderMap m_capturePointSlider;

        ShortIntervalTimer m_updateTimer; /**< update interval */
};

#define sOutdoorPvPMgr MaNGOS::Singleton<OutdoorPvPMgr>::Instance()

#endif
