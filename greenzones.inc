/*

	About: greenzones (safe zones) in SA:MP / open.mp
	Author: aureliusnull

*/

/*
    include guard
*/

#if defined _greenzones_included
  #endinput
#endif
#define _greenzones_included

/*
    definitions
*/

#if !defined _streamer_included
    #error greenzones.inc requires streamer.inc to work.
#endif

#if !defined _FOREACH_LOCAL_VERSION
    #error greenzones.inc requires foreach.inc to work.
#endif

#if !defined _INC_open_mp
	#if !defined KEY
		#define KEY: _:
	#endif
    #if !defined WEAPON_SLOT
        #define WEAPON_SLOT: _:
    #endif
     #if !defined WEAPON
        #define WEAPON: _:
    #endif
#endif

#if !defined MAX_GREENZONES_COUNT
    #define MAX_GREENZONES_COUNT 100
#endif

#if !defined MAX_GREENZONE_WEAPON_SLOT
    #define MAX_GREENZONE_WEAPON_SLOT 12
#endif

#if !defined GREENZONE_FIRE_KEY_TICK_DELAY
    #define GREENZONE_FIRE_KEY_TICK_DELAY 3
#endif

#if !defined GREENZONE_DEFAULT_COLOR
    #define GREENZONE_DEFAULT_COLOR 0x33FF33FF
#endif

#if !defined PRESSED
	#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#endif

#define INVALID_GREENZONE_ID -1

/*
    enums
*/

#if defined _INC_open_mp
    static enum e_greenzone_info
#else
    enum e_greenzone_info
#endif
{
    gz_area_id,
    gz_shape_id[MAX_GANG_ZONES],
    gz_number_of_players
};

#if defined _INC_open_mp
    static enum e_player_greenzone_info
#else
    enum e_player_greenzone_info
#endif
{
    pgz_area_id,
    pgz_weapon[MAX_GREENZONE_WEAPON_SLOT],
    pgz_weapon_ammo[MAX_GREENZONE_WEAPON_SLOT],
    pgz_fire_key_tick
};

/*
    vars
*/

static Iterator:g_greenzone_iterator<MAX_GREENZONES_COUNT>;

static g_greenzone_info[MAX_GREENZONES_COUNT][e_greenzone_info] = {
    {
        -1,
        INVALID_GANG_ZONE,
        0
    },
    ...
};

static g_player_greenzone_info[MAX_PLAYERS][e_player_greenzone_info];

static g_greenzone_available;

/*
	forwards
*/

forward OnPlayerEnterGreenZone(const playerid, const greenzone_id);
forward OnPlayerLeaveGreenZone(const playerid, const greenzone_id);
forward OnPlayerPressFireKeyInGreenZone(const playerid);

/*
	hook OnPlayerDisconnect
*/

public OnPlayerDisconnect(playerid, reason)
{
	for(new i = 0; i < MAX_GREENZONE_WEAPON_SLOT; i++) {
		g_player_greenzone_info[playerid][pgz_weapon][i] = 0;
		g_player_greenzone_info[playerid][pgz_weapon_ammo][i] = 0;
	}

    g_player_greenzone_info[playerid][pgz_area_id] = INVALID_GREENZONE_ID;
    g_player_greenzone_info[playerid][pgz_fire_key_tick] = 0;

    #if defined greenzone_OnPlayerDisconnect
        return greenzone_OnPlayerDisconnect(playerid, reason);
    #else
        return true;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect greenzone_OnPlayerDisconnect
#if defined greenzone_OnPlayerDisconnect
	forward greenzone_OnPlayerDisconnect(playerid, reason);
#endif

/*
    hook OnPlayerSpawn
*/

public OnPlayerSpawn(playerid)
{
    greenzone_ShowShapeForAll();

	#if defined greenzone_OnPlayerSpawn
        return greenzone_OnPlayerSpawn(playerid);
	#else
		return true;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn greenzone_OnPlayerSpawn
#if defined greenzone_OnPlayerSpawn
	forward greenzone_OnPlayerSpawn(playerid);
#endif

/*
	hook OnPlayerEnterDynamicArea
*/

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach (new greenzone_id : g_greenzone_iterator) {
        if (g_greenzone_info[greenzone_id][gz_area_id] == areaid) {
            g_player_greenzone_info[playerid][pgz_area_id] = greenzone_id;
            g_greenzone_info[greenzone_id][gz_number_of_players]++;

            for (new i = 0; i < MAX_GREENZONE_WEAPON_SLOT; i++) {
                GetPlayerWeaponData(
                    playerid,
                    WEAPON_SLOT:i,
                    WEAPON:g_player_greenzone_info[playerid][pgz_weapon][i],
                    WEAPON:g_player_greenzone_info[playerid][pgz_weapon_ammo][i]
                );
            }
		    ResetPlayerWeapons(playerid);

            CallRemoteFunction(
                "OnPlayerEnterGreenZone",
                "dd",
                playerid,
                greenzone_id
            );
            break;
        }
    }

    #if defined greenzone_OnPlayerEnterDynamicA
        return greenzone_OnPlayerEnterDynamicA(playerid, STREAMER_TAG_AREA:areaid);
    #else
        return true;
    #endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif

#define OnPlayerEnterDynamicArea greenzone_OnPlayerEnterDynamicA
#if defined greenzone_OnPlayerEnterDynamicA
	forward greenzone_OnPlayerEnterDynamicA(playerid, STREAMER_TAG_AREA:areaid);
#endif

/*
	hook OnPlayerLeaveDynamicArea
*/

public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach (new greenzone_id : g_greenzone_iterator) {
        if (g_greenzone_info[greenzone_id][gz_area_id] == areaid) {
            for(new i = 0; i < MAX_GREENZONE_WEAPON_SLOT; i++) {
                if (g_player_greenzone_info[playerid][pgz_weapon][i] != _:WEAPON_FIST &&
                    g_player_greenzone_info[playerid][pgz_weapon_ammo][i] > 0) {
                    GivePlayerWeapon(
                        playerid,
                        WEAPON:g_player_greenzone_info[playerid][pgz_weapon][i],
                        WEAPON:g_player_greenzone_info[playerid][pgz_weapon_ammo][i]
                    );
                }

                g_player_greenzone_info[playerid][pgz_weapon][i] = 0;
                g_player_greenzone_info[playerid][pgz_weapon_ammo][i] = 0;
            }

            g_player_greenzone_info[playerid][pgz_area_id] = INVALID_GREENZONE_ID;
            g_greenzone_info[greenzone_id][gz_number_of_players]--;

            CallRemoteFunction(
                "OnPlayerLeaveGreenZone",
                "dd",
                playerid,
                greenzone_id
            );
            break;
        }
    }

    #if defined greenzone_OnPlayerLeaveDynamicA
	    return greenzone_OnPlayerLeaveDynamicA(playerid, STREAMER_TAG_AREA:areaid);
    #else
        return true;
    #endif
}
#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif

#define OnPlayerLeaveDynamicArea greenzone_OnPlayerLeaveDynamicA
#if defined greenzone_OnPlayerLeaveDynamicA
	forward greenzone_OnPlayerLeaveDynamicA(playerid, STREAMER_TAG_AREA:areaid);
#endif

/*
    hook OnPlayerKeyStateChange
*/

public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys)
{
    if (PRESSED(KEY_FIRE)) {
        if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) {
            return true;
        }

        if (g_player_greenzone_info[playerid][pgz_area_id] != INVALID_GREENZONE_ID) {
            if (gettime() - g_player_greenzone_info[playerid][pgz_fire_key_tick] < GREENZONE_FIRE_KEY_TICK_DELAY) {
                return true;
            }

            g_player_greenzone_info[playerid][pgz_fire_key_tick] = gettime();

            CallRemoteFunction(
                "OnPlayerPressFireKeyInGreenZone",
                "d",
                playerid
            );
        }
    }

    #if defined greenzone_OnPlayerKeyStateChang
	    return greenzone_OnPlayerKeyStateChang(playerid, KEY:newkeys, KEY:oldkeys);
    #else
        return true;
    #endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange greenzone_OnPlayerKeyStateChang
#if defined greenzone_OnPlayerKeyStateChang
    forward greenzone_OnPlayerKeyStateChang(playerid, KEY:newkeys, KEY:oldkeys);
#endif

/*
    functions
*/

stock greenzone_CreateRectangle(
    const Float: min_x,
    const Float: min_y,
    const Float: max_x,
    const Float: max_y,
    const virtual_world = -1,
    const interior_id = -1
)
{
    new greenzone_id = Iter_Free(g_greenzone_iterator);

    if (greenzone_id == ITER_NONE) {
        return INVALID_GREENZONE_ID;
    }

    new
        area_id = CreateDynamicRectangle(min_x, min_y, max_x, max_y, virtual_world, interior_id),
        shape_id = GangZoneCreate(min_x, min_y, max_x, max_y);

    g_greenzone_info[greenzone_id][gz_area_id] = area_id;
    g_greenzone_info[greenzone_id][gz_shape_id][0] = shape_id;
    g_greenzone_available++;

    Iter_Add(g_greenzone_iterator, greenzone_id);
    return greenzone_id;
}

stock greenzone_CreateCircle(
    const Float: x,
    const Float: y,
    const Float: radius,
    const virtual_world = -1,
    const interior_id = -1
)
{
    new greenzone_id = Iter_Free(g_greenzone_iterator);

    if (greenzone_id == ITER_NONE) {
        return INVALID_GREENZONE_ID;
    }

    g_greenzone_info[greenzone_id][gz_area_id] = CreateDynamicCircle(
        x,
        y,
        radius,
        virtual_world,
        interior_id
    );

    new
        squares,
        auto_squares = floatround((radius * 512.0) / 750.0),
        free_squares = MAX_GANG_ZONES - g_greenzone_available;

    if (auto_squares <= free_squares) {
        squares = auto_squares;
    } else {
        squares = free_squares;
    }

    if (squares <= 1) {
        return false;
    }

    new
        Float: temp_x,
        Float: next_x,
        Float: temp_y,
        Float: min_ang = 0.0,
        Float: max_ang = 360.0,
        Float: temp_diff,
        Float: diff = (max_ang - min_ang) / float(squares);

    for (new i = 0; i < squares; i++) {
        temp_diff = min_ang + (diff * float(i));

        temp_x = radius * floatcos(temp_diff, degrees);
        temp_y = radius * floatsin(temp_diff, degrees);
        next_x = radius * floatcos((min_ang + (diff * float(i + 1))), degrees);

        if (0.0 <= temp_diff <= 180.0) {
            g_greenzone_info[greenzone_id][gz_shape_id][i] = GangZoneCreate(
                (x + next_x),
                y,
                (x + temp_x),
                (y + temp_y)
            );
        } else {
            g_greenzone_info[greenzone_id][gz_shape_id][i] = GangZoneCreate(
                (x + temp_x),
                (y + temp_y),
                (x + next_x),
                y
            );
        }
    }

    g_greenzone_available += squares;

    Iter_Add(g_greenzone_iterator, greenzone_id);
    return greenzone_id;
}

stock greenzone_Destroy(const greenzone_id)
{
    if (!greenzone_IsValidID(greenzone_id)) {
        return false;
    }

    DestroyDynamicArea(g_greenzone_info[greenzone_id][gz_area_id]);

    for (new i = 0; i < MAX_GANG_ZONES; i++) {
        if (g_greenzone_info[greenzone_id][gz_shape_id][i] == INVALID_GANG_ZONE) {
            continue;
        }

        GangZoneDestroy(g_greenzone_info[greenzone_id][gz_shape_id][i]);
    }

    Iter_Remove(g_greenzone_iterator, greenzone_id);
    return true;
}

stock greenzone_GetAreaID(const greenzone_id)
{
    if (!greenzone_IsValidID(greenzone_id)) {
        return false;
    }

    return g_greenzone_info[greenzone_id][gz_area_id];
}

stock greenzone_GetNumberOfPlayers(const greenzone_id)
{
    if (!greenzone_IsValidID(greenzone_id)) {
        return false;
    }

    return g_greenzone_info[greenzone_id][gz_number_of_players];
}

stock greenzone_GetPlayerAreaID(const playerid)
{
    return g_player_greenzone_info[playerid][pgz_area_id];
}

stock greenzone_IsValidID(const greenzone_id)
{
	return Iter_Contains(g_greenzone_iterator, greenzone_id);
}

/*
	static functions
*/

static stock greenzone_ShowShapeForAll()
{
    foreach (new greenzone_id : g_greenzone_iterator) {
        if (!greenzone_IsValidID(greenzone_id)) {
            return false;
        }

        for (new i = 0; i < MAX_GANG_ZONES; i++) {
            if (g_greenzone_info[greenzone_id][gz_shape_id][i] == INVALID_GANG_ZONE) {
                continue;
            }

            GangZoneShowForAll(g_greenzone_info[greenzone_id][gz_shape_id][i], GREENZONE_DEFAULT_COLOR);
        }
    }

	return true;
}

static stock greenzone_HideShapeForAll()
{
    foreach (new greenzone_id : g_greenzone_iterator) {
        if (!greenzone_IsValidID(greenzone_id)) {
            return false;
        }

        for (new i = 0; i < MAX_GANG_ZONES; i++) {
            if (g_greenzone_info[greenzone_id][gz_shape_id][i] == INVALID_GANG_ZONE) {
                continue;
            }

            GangZoneHideForAll(g_greenzone_info[greenzone_id][gz_shape_id][i]);
        }
    }

	return true;
}