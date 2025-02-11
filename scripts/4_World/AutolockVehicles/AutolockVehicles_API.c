class AutolockVehicles_API
{
	protected static ref AutolockVehicles_API s_Instance;

	void AutolockVehicles_API()
	{
		s_Instance = this;
	}

	static AutolockVehicles_API GetInstance()
	{
		if (!s_Instance) new AutolockVehicles_API();
		return s_Instance;
	}

	void OnAutoLock(CarScript car){}
	void OnAutoUnlock(CarScript car){}
}
