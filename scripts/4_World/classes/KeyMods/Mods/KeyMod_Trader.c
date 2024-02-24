#ifdef Trader
class AutolockVehicles_Trader : AutolockVehicles_KeyModBase
{
    override string GetName() { return "TRADER"; }
    
    override AutolockVehicles_State GetVehicleState(Transport vehicle)
    {
        CarScript car;
        car = CarScript.Cast(vehicle);
        if(!car) return AutolockVehicles_State.ERROR;

        if(!car.m_Trader_HasKey) return AutolockVehicles_State.UNASSIGNED;
        if(car.m_Trader_Locked) return AutolockVehicles_State.LOCKED;
        return AutolockVehicles_State.UNLOCKED;
    }

    override void LockVehicle(Transport vehicle)
    {
        CarScript car;
        car = CarScript.Cast(vehicle);
        if(!car) return;

        car.m_Trader_Locked = true;
        car.SynchronizeValues();
    }
}

modded class ActionUnlockVehicle
{	
	override void OnFinishProgressServer(ActionData action_data)
	{	
        super.OnFinishProgressServer(action_data);

        PlayerBase player = action_data.m_Player;
        if(!player) return;

        CarScript car = CarScript.Cast(action_data.m_Target.GetParent());
		if(!car) return;

        AutolockVehicles_App.GetInstance().StartProximityWatcher(player, car);
	}
};
#endif
