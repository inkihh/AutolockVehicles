## Donations welcome

If you like this mod, please consider donating!

[![PayPal](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b5/PayPal.svg/160px-PayPal.svg.png)](https://paypal.me/ingmarheinrich)

## Purpose

This mod automatically locks vehicles under certain conditions. It's compatible with the four main vehicle locking mechanisms:

- [MuchCarKey](https://steamcommunity.com/sharedfiles/filedetails/?id=2049002856)
- [TraderPlus's CarLock](https://steamcommunity.com/sharedfiles/filedetails/?id=2458896948)
- [Trader](https://steamcommunity.com/sharedfiles/filedetails/?id=1590841260)
- [Expansion Vehicles](https://steamcommunity.com/sharedfiles/filedetails/?id=2291785437)

## Description

There are a few situations when it can be practical that vehicles automatically get locked. For these situations, the mod can be configured so that it fits the specific server.

- Server crashes
- Players missing restarts
- Players getting disconnected
- Crowded area situations
- Players simply forgetting to lock

## Configuration

At first install, a configuration file with these default values will be created in `$profile:AutolockVehicles/AutolockVehicles.json`

```json
{
    "debug_log_level": 1,
    "use_key_mod": 0,
    "enable_startup_autolock_timer": 0,
    "enable_disconnect_autolock_timer": 0,
    "enable_proximity_autolock": 0,
    "enable_close_doors_on_autolock": 0,
    "enable_engine_off_on_autolock": 0,
    "lock_only_when_all_doors_are_closed": 1,
    "autolock_delay_startup_minutes": 2,
    "autolock_delay_player_disconnect_minutes": 1,
    "proximity_lock_distance_meters": 5
}
```

Ideally, you test and configure the mod on a test server, so that at the first time you start your live server with it, you can already have the perfectly configured file in place.

### debug_log_level
This setting can be used to control the level of verbosity the mod writes to the log with (`$profile:AutolockVerhicles.log`). 1 means only display critical errors, while 5 makes it very chatty - only use 5 to find possible reasons for malfunction, aka debugging, or on your test server.

Currently, only log levels 1 and 5 are used. In the future, the mod's output will be more fine tuned, so you can get a certain level of information on your live server without spamming the log file.

### use_key_mod
This determines the vehicle locking mechanism you want to use. Of course, the respective mod has to be installed and active.

| use_key_mod value | locking mechanism |
| --- | --- |
| 0 (default) | Custom mechanism (see below) |
| 1 | [MuchCarKey](https://steamcommunity.com/sharedfiles/filedetails/?id=2049002856) |
| 2 | [TraderPlus's CarLock](https://steamcommunity.com/sharedfiles/filedetails/?id=2458896948) |
| 3 | [Trader](https://steamcommunity.com/sharedfiles/filedetails/?id=1590841260) |
| 4 | [Expansion Vehicles](https://steamcommunity.com/sharedfiles/filedetails/?id=2291785437) |

### enable_startup_autolock_timer
Set this to 1 to enable automatic locking of vehicles whenever a vehicle is spawned. Spawning can be server startup, an admin spawning a vehicle, a player buying a vehicle from a trader, restoring a vehicle from a garage system, or other events.

If this feature is enabled, the mod will try to automatically lock the spawned vehicle after `autolock_delay_startup_minutes`.

### enable_disconnect_autolock_timer
This feature will try to lock a vehicle when a player disconnects. It will only work on the last vehicle the player has unlocked, and only if they were the last player to unlock it. The setting that delays this action is `autolock_delay_player_disconnect_minutes`.

### enable_proximity_autolock
This works like handsfree locking in real life: If a player unlocks a vehicle and then later moves farther away from it than defined by `proximity_lock_distance_meters`, the mod will try to lock it. Again, this only works if they were the last player to unlock it.

The constant distance measuring happens in the player's client, so it won't affect the server's performance.

### lock_only_when_all_doors_are_closed
Some locking mechanisms behave in an unexpoected way if the doors are being programmatically locked while one or more doors are open. With this setting, you can determine that autolocking will only happen if all doors are closed, including the trunk.

This can also be helpful for groups of players that work on a shared vehicle at a trader location, so that their vehicle doesn't get locked if the player that last locked it runs to sell.

### enable_engine_off_on_autolock
### enable_close_doors_on_autolock
These two settings determine if the mod should automatically shut down the vehicle's engine, or close its doors, on autolock. Please note that if `lock_only_when_all_doors_are_closed` is set, the doors won't get automatically closed.

## Custom key mod
If you want to use a vehicle locking mechanism that isn't supported by this mod, you can extend `GetVehicleState` and `LockVehicle` of the class [AutolockVehicles_Custom](https://github.com/inkihh/DZAutolockVehicles/blob/main/scripts/4_World/classes/KeyMods/KeyModCustom.c). See the [existing key mods](https://github.com/inkihh/DZAutolockVehicles/tree/main/scripts/4_World/classes/KeyMods/Mods) for reference.

You also have hook into the key mod's locking action to start the proximity process. Also, see the [existing key mods](https://github.com/inkihh/DZAutolockVehicles/tree/main/scripts/4_World/classes/KeyMods/Mods) for reference.

## Help
You can find me on the FOG FamilyOfGamers Discord or the Enfusion Modders Discord (see below in the Credits), or DM me on Discord (inkihh).

The code is public on [Github](https://github.com/inkihh/DZAutolockVehicles), where you can create an [issue](https://github.com/inkihh/DZAutolockVehicles/issues) or look at the [project board](https://github.com/users/inkihh/projects/2). Feature ideas welcome!

## Credits
Thanks to my "family" at FOG FamilyOfGamers, without their support I wouldn't have pushed through. Join [their Discord](https://discord.gg/familyofgamers) for the ultimative experience of how a DayZ community should be! Special thanks to `Prs7` who encouraged me to make this mod compatible to different locking mechanisms and publish it.

Special thanks to the [Enfusion Modders Discord](https://discord.gg/enfusionmodders) - without the constant help from these guys, I would have gone nowhere. Special thanks to Wardog, Tree, The Crimson Zamboni, Varyel, ◣▲▼▲, TrueDolphin, aff3nbart, Dmitri, LieutenantMaster and Helkhiana.

Extra special thanks to `AVcrazy21` for designing this awesome steam workshop page icon, despite my constant whining for changes <3

## Legalese
- The mod may NOT be repacked, aka used in a mod pack or server pack. Don't ask.
- The mod may be used on monetized servers, as long as Bohemia's monetization guidelines are followed
- The mod may only be uploaded to the Steam Workshop under my account name (inkihh)

Copyright 2024 inkihh

