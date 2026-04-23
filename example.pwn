/*

    Example usage

*/

#include <open.mp>
#include <greenzones>

new greenzone_rectangle;
new greenzone_circle;

main() {}

public OnGameModeInit()
{
    greenzone_rectangle = greenzone_CreateRectangle(0.0, 0.0, 100.0, 100.0);
    greenzone_circle = greenzone_CreateCircle(0.0, 0.0, 100.0);

    return true;
}

public OnPlayerEnterGreenZone(const playerid, const greenzone_id)
{
    new
        string[64],
        player_name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, player_name);

    format(
        string,
        sizeof string,
        "Player %s [ID: %d] entered greenzone with ID: %d."
        player_name,
        playerid,
        greenzone_id
    );
    SendClientMessageToAll(-1, string);

    if (greenzone_rectangle == greenzone_id) {
        // ...
    }
    else if (greenzone_circle == greenzone_id) {
        // ...
    }

    return true;
}

public OnPlayerLeaveGreenZone(const playerid, const greenzone_id)
{
    new
        string[64],
        player_name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, player_name);

    format(
        string,
        sizeof string,
        "Player %s [ID: %d] leave greenzone with ID: %d."
        player_name,
        playerid,
        greenzone_id
    );
    SendClientMessageToAll(-1, string);

    if (greenzone_rectangle == greenzone_id) {
        // ...
    }
    else if (greenzone_circle == greenzone_id) {
        // ...
    }

    return true;
}

public OnPlayerPressFireKeyInGreenZone(const playerid)
{
    new
        string[128],
        player_name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, player_name);

    format(
        string,
        sizeof string,
        "Player %s [ID: %d] pressed the attack key in a greenzone."
        player_name,
        playerid
    );
    SendClientMessageToAll(-1, string);

    return true;
}