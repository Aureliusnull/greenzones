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
```

```
## Directives
<details> <summary>Click to expand the list</summary>
#define MAX_GREENZONES_COUNT 100
#define INVALID_GREENZONE_ID -1
#define MAX_GREENZONE_WEAPON_SLOT 12
#define GREENZONE_FIRE_KEY_TICK_DELAY 3
#define GREENZONE_DEFAULT_COLOR 0x33FF33FF
</details>
Callbacks
<details> <summary>Click to expand the list</summary>
public OnPlayerEnterGreenZone(const playerid, const greenzone_id)

Called when a player enters a green zone

playerid - Player ID
greenzone_id - Green zone ID
public OnPlayerLeaveGreenZone(const playerid, const greenzone_id)

Called when a player leaves a green zone

playerid - Player ID
greenzone_id - Green zone ID
public OnPlayerPressFireKeyInGreenZone(const playerid)

Called when a player presses fire key inside a green zone

playerid - Player ID
</details>
Functions
<details> <summary>Click to expand the list</summary>
greenzone_CreateRectangle(Float:min_x, Float:min_y, Float:max_x, Float:max_y, virtual_world = -1, interior_id = -1)

Create rectangular green zone

Returns: greenzone_id or INVALID_GREENZONE_ID
greenzone_CreateCircle(Float:x, Float:y, Float:radius, virtual_world = -1, interior_id = -1)

Create circular green zone

Returns: greenzone_id or INVALID_GREENZONE_ID
greenzone_Destroy(greenzone_id)

Remove green zone

Returns: true/false
greenzone_ShowShapeForAll(color)

Show all green zone shapes for all players

greenzone_HideShapeForAll()

Hide all green zone shapes

greenzone_GetAreaID(greenzone_id)

Get dynamic area ID

greenzone_GetNumberOfPlayers(greenzone_id)

Get number of players inside the zone

greenzone_GetPlayerAreaID(playerid)

Get player's current green zone ID

greenzone_IsValidID(greenzone_id)

Check if ID is valid
</details>
