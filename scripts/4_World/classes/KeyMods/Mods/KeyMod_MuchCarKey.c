#ifdef MuchCarKey
class AutolockVehicles_MuchCarKey : AutolockVehicles_KeyModBase
{
	override string GetName() { return "MUCHCARKEY"; }
	
	override AutolockVehicles_State GetVehicleState(Transport vehicle)
	{
		CarScript car;
		car = CarScript.Cast(vehicle);
		if(!car) return AutolockVehicles_State.ERROR;

		if(!car.m_HasCKAssigned) return AutolockVehicles_State.UNASSIGNED;
		if(car.m_IsCKLocked) return AutolockVehicles_State.LOCKED;
		return AutolockVehicles_State.UNLOCKED;
	}

	override void LockVehicle(Transport vehicle)
	{
		CarScript car;
		car = CarScript.Cast(vehicle);
		if(!car) return;

		car.m_IsCKLocked = true;
		car.SynchronizeValues();
		car.ResetLifetime();
	}

	override void unlockVehicle(Transport vehicle)
	{
		CarScript car;
		car = CarScript.Cast(vehicle);
		if(!car) return;

		car.m_IsCKLocked = false;
		car.SynchronizeValues();
		car.ResetLifetime();
	}
}

modded class ActionUnlockCar: ActionLockUnlockCar
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
#endif
