class AutolockVehicles_ServerInformation
{
	private ref map<string, string> m_ConfigVariables;
	private string m_ConfigPath;

	void AutolockVehicles_ServerInformation()
	{
		m_ConfigVariables = new map<string, string>();

		SetConfigPath();
		ParseConfig();
	}

	private void SetConfigPath()
	{
		string cliParam;
		string path = "serverDZ.cfg";

		if (GetCLIParam("config", cliParam)) path = cliParam;

		m_ConfigPath = "$CurrentDir:" + path;
	}

	private void ParseConfig()
	{
		ParseHandle handle = BeginParse(m_ConfigPath);

		if (handle == 0) return;

		const int count = 100;
		string str[count];

		int index = 0;
		
		array<string> varParts;
		
		string varName = "";
		string varValue = "";
		
		string configLine = "";
		
		while (true)
		{
			int parsed = ParseLine(handle, index, str);
			index++;
		
			if (parsed <= 0) break;

			varParts = new array<string>();
			configLine = "";

			for (int i = 0; i < parsed; i++)
			{
				configLine += str[i];
			}

			AutolockVehicles_App.GetInstance().m_Logger.Log("Config line: " + configLine);

			if(!configLine.Contains("=")) continue;
		
			configLine.Split("=", varParts);

			varName = varParts[0].Trim();
			varName.ToLower();

			varValue = varParts[1];
			varValue = varValue.SubstringUtf8(0, varValue.Length() - 1 );
			varValue.TrimInPlace();

			m_ConfigVariables.Set(varName, varValue)

			AutolockVehicles_App.GetInstance().m_Logger.Log("varName:" + varName + " varValue:" + varValue);
			
		}

		EndParse(handle);
	}

	string GetHostName()
	{
		string hostname = m_ConfigVariables.Get("hostname");
		if(!hostname) hostname = "UNKNOWN";

		AutolockVehicles_App.GetInstance().m_Logger.Log("GetHostName() returning " + hostname);
		return hostname;
	}
}
