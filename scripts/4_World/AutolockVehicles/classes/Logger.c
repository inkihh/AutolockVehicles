class AutolockVehicles_Logger
{
	string m_AppName;
	string m_LogFile;

	void AutolockVehicles_Logger(string AppName)
	{
		m_LogFile = "$profile:" + AppName + ".log";
		m_AppName = AppName;
	}

	void Log(string message, AutolockVehicles_LogLevel MyLogLevel = AutolockVehicles_LogLevel.DEBUG)
	{
		if(AutolockVehicles_App.GetInstance().m_Settings.debug_log_level < MyLogLevel) return;

		FileHandle file = OpenFile(m_LogFile, FileMode.APPEND);

		if (file)
		{
			string timestamp = AutolockVehicles_Helper.GetTimestamp();
			FPrintln(file, "[" + timestamp + "] " + message.Trim());
			CloseFile(file);
		}
		else
		{
			Print("[" + m_AppName + "] Could not create logfile " + m_LogFile);
		}
	}
}
