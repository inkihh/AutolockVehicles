enum AutolockVehicles_State
{
    ERROR,
    UNASSIGNED,
    UNLOCKED,
    LOCKED
}

enum AutolockVehicles_KeyMod
{
    CUSTOM,
    MUCHCARKEY,
    TRADERPLUSCARLOCK
}

class AutolockVehicles_KeyModBase
{
    string GetName() { return "UNSET"; }
    AutolockVehicles_State GetVehicleState(Transport vehicle){}
    void LockVehicle(Transport vehicle){}
}
