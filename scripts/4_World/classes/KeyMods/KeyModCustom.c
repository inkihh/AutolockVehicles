class AutolockVehicles_Custom : AutolockVehicles_KeyModBase
{
    override string GetName() { return "CUSTOM"; }
    override AutolockVehicles_State GetVehicleState(Transport vehicle){}
    override void LockVehicle(Transport vehicle){}
}
