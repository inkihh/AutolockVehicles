class AutolockVehicles_Custom : AutolockVehicles_KeyModBase
{
	override AutolockVehicles_State GetVehicleState(Transport vehicle){ return AutolockVehicles_State.ERROR; }
	override void LockVehicle(Transport vehicle){}
}

// need to override your custom ActionUnlockVehicle too