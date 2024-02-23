class AutolockVehicles_Settings
{
	int debug_log_level = 1;
	int UseKeyMod = 0;
	int enableStartupAutolock = 0;
	int enableDisconnectAutolock = 0;
	int enableProximityAutolock = 0;
	int enableCloseDoors = 0;
	int lockOnlyWhenAllDoorsAreClosed = 1;
	int enableEngineOff = 0;
	int AutolockDelay_Startup = 2;
	int AutolockDelay_PlayerDisconnect = 1;
	int ProximityLock_DistanceMeters = 5;
	
	[NonSerialized()]
	private bool m_IsLoaded;

	void AutolockVehicles_Settings(string AppName)
	{
		if(!GetGame().IsServer()) return;

		string ConfigPath = "$profile:AutolockVehicles";
		MakeDirectory(ConfigPath);

		string inkihhConfigFile = ConfigPath + "/" + AppName + ".json";
		this.m_IsLoaded = this.Load(inkihhConfigFile) ;
	}

	bool Load(string inkihhConfigFile)
	{
		if(!GetGame().IsServer()) return false;

		if (FileExist(inkihhConfigFile))
		{
			JsonFileLoader<AutolockVehicles_Settings>.JsonLoadFile(inkihhConfigFile, this);
			JsonFileLoader<AutolockVehicles_Settings>.JsonSaveFile(inkihhConfigFile, this);
			return true;
		}

		JsonFileLoader<AutolockVehicles_Settings>.JsonSaveFile(inkihhConfigFile, this);
		return false;
	}

	bool IsLoaded()
	{
		return this.m_IsLoaded;
	}
}
