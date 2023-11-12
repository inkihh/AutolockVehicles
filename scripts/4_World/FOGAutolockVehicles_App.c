class FOGAutolockVehicles_App
{
	protected static ref FOGAutolockVehicles_App s_Instance;
	static const string m_AppName = "FOGAutolockVehicles";

	ref FOGAutolockVehicles_Logger m_Logger;
	ref FOGAutolockVehicles_Settings m_Settings;
	    
	bool m_CratesInitialized;

	void FOGAutolockVehicles_App()
	{
		m_Logger = new FOGAutolockVehicles_Logger(m_AppName);
		m_Settings = new FOGAutolockVehicles_Settings(m_AppName);

		s_Instance = this;

		if (!m_Settings.IsLoaded())
		{
			Print("[" + m_AppName + "] Settings incomplete. Please check " + m_Logger.m_LogFile);
			Print("[" + m_AppName + "] If it didn't exist at all, an empty one was created right now.");
			return;
		}

		Print("[" + m_AppName + "] Ready. Logging commences in " + m_Logger.m_LogFile);
		FOGAutolockVehicles_App.GetInstance().m_Logger.Log("Ready.");

		if(m_CratesInitialized) return;
		m_CratesInitialized = true;

		FOGAutolockVehicles_App.GetInstance().m_Logger.Log("Starting CreateCrates timer");
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater( this.CreateCrates, 60000, false );
	}

	void CreateCrates()
	{
		array<FOGCrateConfiguration> crates = m_Settings.crates;
		FOGCrateConfiguration crate_configuration;
		FOGAutolockVehiclesMilitaryCrate crate;

		FOGAutolockVehicles_App.GetInstance().m_Logger.Log("Starting CreateCrates()");

		for (int i = 0; i < crates.Count(); i++)
		{
			crate_configuration = crates.Get(i);
			m_Logger.Log("Crate \"" + crate_configuration.name + "\" from config");
			m_Logger.Log("Position: " + crate_configuration.position);

			crate = FOGAutolockVehiclesMilitaryCrate.Cast(GetGame().CreateObject("FOGAutolockVehiclesMilitaryCrate", crate_configuration.position.ToVector()));
			crate.SetOrientation(crate_configuration.orientation.ToVector());
			crate.SetCrateConfiguration(crate_configuration);

			crate.Bury();
		}
	}

	static FOGAutolockVehicles_App GetInstance()
	{
		if (!s_Instance) new FOGAutolockVehicles_App();
		return s_Instance;
	}

	FOGAutolockVehicles_Logger GetLogger()
	{
		return m_Logger;
	}
	
	FOGAutolockVehicles_Settings GetSettings()
	{
		return m_Settings;
	}
}
