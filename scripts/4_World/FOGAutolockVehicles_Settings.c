class FOGAutolockVehicles_Settings
{
	bool DoDebug = true;
	int AutolockDelay_Startup = 5;
	int AutolockDelay_PlayerDisconnect = 5;
	int AutolockDelay_EngineStop = 5;
	
	[NonSerialized()]
	private bool m_IsLoaded;

	void FOGAutolockVehicles_Settings(string AppName)
	{
		string ConfigPath = "$profile:FOG";
		MakeDirectory(ConfigPath);

		string FOGConfigFile = ConfigPath + "/" + AppName + ".json";
		this.m_IsLoaded = this.Load(FOGConfigFile) ;
	}

	bool Load(string FOGConfigFile)
	{
		if (FileExist(FOGConfigFile))
		{
			JsonFileLoader<FOGAutolockVehicles_Settings>.JsonLoadFile(FOGConfigFile, this);
			JsonFileLoader<FOGAutolockVehicles_Settings>.JsonSaveFile(FOGConfigFile, this);
			return true;
		}

		JsonFileLoader<FOGAutolockVehicles_Settings>.JsonSaveFile(FOGConfigFile, this);
		return false;
	}

	bool IsLoaded()
	{
		return this.m_IsLoaded;
	}

	// ------------------------------------------------------

	bool GetDoDebug()
	{
		return DoDebug;
	}
}
