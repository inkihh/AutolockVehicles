class FOGAutolockVehicles_Settings
{
	bool DoDebug = false;
	int AutolockDelay = 5;

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

	int GetAutolockDelay()
	{
		return AutolockDelay;
	}

	bool GetDoDebug()
	{
		return DoDebug;
	}
}
