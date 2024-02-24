class AutolockVehicles_Custom : AutolockVehicles_KeyModBase
{
    override string GetName() { return "CUSTOM"; }
    override AutolockVehicles_State GetVehicleState(Transport vehicle){ return AutolockVehicles_State.ERROR; }
    override void LockVehicle(Transport vehicle){}
}

// need to override your custom ActionUnlockVehicle too