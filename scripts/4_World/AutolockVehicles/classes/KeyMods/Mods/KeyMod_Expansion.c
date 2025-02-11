#ifdef DZ_Expansion_Vehicles
class AutolockVehicles_Expansion : AutolockVehicles_KeyModBase
{
	override string GetName() { return "EXPANSION"; }
	
	override AutolockVehicles_State GetVehicleState(Transport vehicle)
	{
		CarScript car;
		car = CarScript.Cast(vehicle);
		if(!car) return AutolockVehicles_State.ERROR;

		if(!car.GetExpansionVehicle().HasKey()) return AutolockVehicles_State.UNASSIGNED;
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

	override void UnlockVehicle(Transport vehicle)
	{
		CarScript car;
		car = CarScript.Cast(vehicle);
		if(!car) return;

		ExpansionCarAdminKey adminkey;
		car.UnlockCar(adminkey);
	}
}

modded class ExpansionActionUnlockVehicle: ActionInteractBase
{
	override void OnStartServer( ActionData action_data )
	{
		super.OnStartServer( action_data );
		
		AutolockVehicles_App.GetInstance().m_Logger.Log("[ExpansionVehicleActionUnlockVehicle.OnStartServer]");

		PlayerBase player = action_data.m_Player;
		if(!player) {
			AutolockVehicles_App.GetInstance().m_Logger.Log("[ExpansionVehicleActionUnlockVehicle.OnStartServer] no player");
			return;
		}

		CarScript car = CarScript.Cast( action_data.m_Target.GetParentOrObject() );
		if(!car) 
		{
			AutolockVehicles_App.GetInstance().m_Logger.Log("[ExpansionVehicleActionUnlockVehicle.OnStartServer] no car");
			return;
		}

		AutolockVehicles_App.GetInstance().StartProximityWatcher(player, car);
	}
};
#endif
