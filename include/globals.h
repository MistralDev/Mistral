/*
 * globals.h
 *
 *  Created on: Nov 16, 2016
 *      Author: nullifiedcat
 */

#pragma once
#include <time.h>
#include <mathlib/vector.h>
#include "Constants.hpp"

class Vector;
class CUserCmd;
class ConVar;

// Amount of createmove ticks since cheat inject. This value ONLY GOES UP.
extern unsigned long tickcount;

extern ConVar *sv_client_min_interp_ratio, *sv_client_max_interp_ratio, *cl_interp_ratio, *cl_interp, *cl_interpolate, *cl_updaterate, *sv_maxupdaterate;

extern bool *bSendPackets;
extern bool need_name_change;
extern int last_cmd_number;

extern time_t time_injected;

class GlobalSettings
{
public:
    void Init();
    bool bInvalid{ true };
    bool is_create_move{ false };
};

bool isHackActive();

extern CUserCmd *current_user_cmd;
// Seperate user cmd used in the late createmove
extern CUserCmd *current_late_user_cmd;

extern GlobalSettings g_Settings;
