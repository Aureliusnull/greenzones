# greenzones

Creation and management of greenzones (safe zones) in SA:MP / open.mp
<p align="center">
  <img src="https://raw.githubusercontent.com/Aureliusnull/greenzones/main/preview.png" width="700">
</p>

## Features

* Automatic weapon removal inside green zones  
* Weapon restore on zone exit  
* Fire key detection inside zones  
* Support for rectangle and circle zones  
* Player counter inside zones

## Dependencies
* [streamer](https://github.com/samp-incognito/samp-streamer-plugin)
* [foreach](https://github.com/Open-GTO/foreach)

## Reference
* [Installation](#installation)
* [Example](#example)
* [Directives](#directives)
* [Callbacks](#callbacks)
* [Functions](#functions)

## Installation

Include in your code and begin using the library:
```pawn
#include <greenzones>
```

## Example
```pawn
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
```
## Directives

Directive | Default value | Note
----------|---------------|------------
INVALID_GREENZONE_ID | -1 |
MAX_GREENZONES_COUNT | 100
MAX_GREENZONE_WEAPON_SLOT | 12
GREENZONE_FIRE_KEY_TICK_DELAY | 3
GREENZONE_DEFAULT_COLOR | 0x33FF33FF

## Callbacks
<details> 
<summary>Click to expand the list</summary>
  
#### public OnPlayerEnterGreenZone(playerid, greenzone_id)
* Called when a player enters a greenzone
> * `playerid` - The ID of the player
> * `greenzone_id` - The ID of the greenzone

#### public OnPlayerLeaveGreenZone(playerid, greenzone_id)
* Called when a player leaves a greenzone
> * `playerid` - The ID of the player
> * `greenzone_id` - The ID of the greenzone

#### public OnPlayerPressFireKeyInGreenZone(playerid)
* Called when a player presses fire key inside a green zone
> * `playerid` - The ID of the player
</details>

## Functions
<details>
<summary>Click to expand the list</summary>

#### greenzone_CreateRectangle(Float:min_x, Float:min_y, Float:max_x, Float:max_y, virtual_world = -1, interior_id = -1)
> Create rectangle greenzone
> * `Float:min_x` - The min_x coordinate to create the rectangle
> * `Float:min_y` - The min_y coordinate to create the rectangle
> * `Float:max_x` - The max_x coordinate to create the rectangle
> * `Float:max_y` - The max_y coordinate to create the rectangle
> * `virtual_world` - The virtual world ID 
> * `interior_id` - The interior ID

#### greenzone_CreateCircle(Float:x, Float:y, Float:radius, virtual_world = -1, interior_id = -1)
> Create circle greenzone
> * `Float:x` - The x coordinate to create the greenzone
> * `Float:y` - The z coordinate to create the greenzone
> * `Float:radius` - The greenzone radius
> * `virtual_world` - The virtual world ID 
> * `interior_id` - The interior ID

#### greenzone_Destroy(greenzone_id)
> Remove greenzone
> * `greenzone_id` - The ID of the greenzone

#### greenzone_IsValidID(greenzone_id)
> Check if ID greenzone is valid
> * ` greenzone_id` - The ID of the greenzone

#### greenzone_GetAreaID(greenzone_id)
> Get dynamic area ID
> * ` greenzone_id` - The ID of the greenzone

#### greenzone_GetNumberOfPlayers(greenzone_id)
> Get number of players inside the zone
> * ` greenzone_id` - The ID of the greenzone

#### greenzone_ShowShapeForAll()
> Show all greenzone shapes for all players

#### greenzone_HideShapeForAll()
> Hide all greenzone shapes for all players

#### greenzone_GetPlayerAreaID(playerid)
> Get player's current greenzone ID
> * `playerid` - The ID of the player
 
</details>
