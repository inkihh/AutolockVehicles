class AutolockVehicles_Settings
{
	bool DoDebug = true;
	int UseKeyMod = 0;
	int AutolockDelay_Startup = 5;
	int AutolockDelay_PlayerDisconnect = 5;
	int ProximityLock_DistanceMeters = 10;
	
	[NonSerialized()]
	private bool m_IsLoaded;

	void AutolockVehicles_Settings(string AppName)
	{
		string ConfigPath = "$profile:AutolockVehicles";
		MakeDirectory(ConfigPath);

		string inkihhConfigFile = ConfigPath + "/" + AppName + ".json";
		this.m_IsLoaded = this.Load(inkihhConfigFile) ;
	}

	bool Load(string inkihhConfigFile)
	{
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

	bool GetDoDebug()
	{
		return DoDebug;
	}
}
