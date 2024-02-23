#ifdef EXPANSIONMODVEHICLE
class AutolockVehicles_Expansion : AutolockVehicles_KeyModBase
{
    override string GetName() { return "EXPANSION"; }
    
    override AutolockVehicles_State GetVehicleState(Transport vehicle)
    {
        CarScript car;
        car = CarScript.Cast(vehicle);
        if(!car) return AutolockVehicles_State.ERROR;

        if(!car.HasKey()) return AutolockVehicles_State.UNASSIGNED;
        if(car.IsLocked()) return AutolockVehicles_State.LOCKED;
        return AutolockVehicles_State.UNLOCKED;
    }

    override void LockVehicle(Transport vehicle)
    {
        CarScript car;
        car = CarScript.Cast(vehicle);
        if(!car) return;

        ExpansionCarAdminKey adminkey;
        car.LockCar(adminkey);
    }
}
#endif
