class FOGAutolockVehicles_App
{
	protected static ref FOGAutolockVehicles_App s_Instance;
	static const string m_AppName = "FOGAutolockVehicles";

	ref FOGAutolockVehicles_Logger m_Logger;
	ref FOGAutolockVehicles_Settings m_Settings;
	    
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
