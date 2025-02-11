class AutolockVehicles_Settings
{
	int debug_log_level = 1;
	int environment = 1;
	int use_key_mod = 0;
	int enable_proximity_autolock = 0;
	int enable_proximity_autounlock = 0;
	int enable_startup_autolock_timer = 0;
	int enable_disconnect_autolock_timer = 0;
	int enable_close_doors_on_autolock = 0;
	int enable_engine_off_on_autolock = 0;
	int lock_only_when_all_doors_are_closed = 1;
	int lock_only_when_no_players_inside = 0;
	int autolock_delay_startup_minutes = 2;
	int autolock_delay_player_disconnect_minutes = 1;
	int proximity_lock_distance_meters = 5;
	int proximity_unlock_distance_meters = 2;
	
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
