enum AutolockVehicles_KeyMod
{
    CUSTOM = 0
    MUCHCARKEY = 1
    TRADERPLUSCARLOCK = 2
    TRADER = 3,
    EXPANSION = 4
}

enum AutolockVehicles_LogLevel
{
    CRITICAL    = 1,
    ERROR       = 2,
    WARNING     = 3,
    NOTICE      = 4,
    DEBUG       = 5
}

enum AutolockVehicles_TimerMode
{
    STARTUP = 0,
    ENGINESTOP = 1,
    PLAYERDISCONNECT = 3,
}

enum AutolockVehicles_State
{
    ERROR = 0,
    UNASSIGNED = 1,
    UNLOCKED = 2,
    LOCKED = 3
}
