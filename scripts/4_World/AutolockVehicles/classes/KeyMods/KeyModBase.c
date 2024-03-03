class AutolockVehicles_KeyModBase
{
	string GetName() { return "CUSTOM"; }
	AutolockVehicles_State GetVehicleState(Transport vehicle){}
	void LockVehicle(Transport vehicle){}
	void UnlockVehicle(Transport vehicle){}
}
