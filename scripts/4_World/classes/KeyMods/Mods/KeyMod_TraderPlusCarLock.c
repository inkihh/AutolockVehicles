#ifdef CarLock
#ifndef CARLOCKDISABLE
class AutolockVehicles_TraderPlusCarLock : AutolockVehicles_KeyModBase
{
    override string GetName() { return "TRADERPLUSCARLOCK"; }
    
    override AutolockVehicles_State GetVehicleState(Transport vehicle)
    {
        CarScript car;
        car = CarScript.Cast(vehicle);
        if(!car) return AutolockVehicles_State.ERROR;

        if(car.m_CarLockPassword == -1) return AutolockVehicles_State.UNASSIGNED;
        if(car.m_CarLock_IsLocked) return AutolockVehicles_State.LOCKED;
        return AutolockVehicles_State.UNLOCKED;
    }

    override void LockVehicle(Transport vehicle)
    {
        CarScript car;
        car = CarScript.Cast(vehicle);
        if(!car) return;

        car.SetSoundToPlay(1);
		car.SetCarLock(true);
    }
}

modded class ActionCarUnLock
{
    override void OnStartServer(ActionData action_data)
    {
        super.OnStartServer(action_data);

        PlayerBase player = action_data.m_Player;
        if(!player) return;

        CarScript car = CarScript.Cast(action_data.m_Target.GetObject());
		if(!car) return;

        AutolockVehicles_App.GetInstance().StartProximityWatcher(player, car);
    }
}
#endif
#endif
