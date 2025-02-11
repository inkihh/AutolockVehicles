#ifdef MuchCarKey
class AutolockVehicles_MuchCarKey : AutolockVehicles_KeyModBase
{
	override string GetName() { return "MUCHCARKEY"; }
	
	override AutolockVehicles_State GetVehicleState(Transport vehicle)
	{
		CarScript car;
		car = CarScript.Cast(vehicle);
		if(!car) return AutolockVehicles_State.ERROR;

		if(!car.MCK_HasKeyAssigned()) return AutolockVehicles_State.UNASSIGNED;
		if(car.MCK_IsLocked()) return AutolockVehicles_State.LOCKED;
		return AutolockVehicles_State.UNLOCKED;
	}

	override void LockVehicle(Transport vehicle)
	{
		if(!vehicle) return;

		MCK_Transport.ToggleLockTransport(vehicle);
	}

	override void UnlockVehicle(Transport vehicle)
	{
		if(!vehicle) return;

		MCK_Transport.ToggleLockTransport(vehicle);
	}
}

modded class ActionUnlockCar
{	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		super.OnFinishProgressServer(action_data);

		PlayerBase player = action_data.m_Player;
		if(!player) return;

		CarScript car = CarScript.Cast(action_data.m_Target.GetObject());
		if(!car) car = CarScript.Cast(action_data.m_Target.GetParent());
		if(!car) return;

		AutolockVehicles_App.GetInstance().StartProximityWatcher(player, car);
	}
};

/* modded class ActionMCKRemoteOpenClose
{
	override void OnExecuteServer( ActionData action_data )
	{
		super.OnExecuteServer( action_data )

		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
        MCK_CarKey_Base carKey = MCK_CarKey_Base.Cast(action_data.m_MainItem);
        
		if(!player || !carKey) return;
        
		Transport transport = carKey.FindNearbyTransport(player);
        if(!transport) return;

		CarScript car = CarScript.Cast(transport);
		if(!car) return;

		AutolockVehicles_App.GetInstance().StartProximityWatcher(player, car);
	}
}; */
#endif
