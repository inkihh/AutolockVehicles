#ifdef MuchCarKey
class AutolockVehicles_MuchCarKey : AutolockVehicles_KeyModBase
{
    override string GetName() { return "MUCHCARKEY"; }
    override AutolockVehicles_State GetVehicleState(Transport vehicle){}
    override void LockVehicle(Transport vehicle){}
}
#endif
