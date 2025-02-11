class AutolockVehicles_RestCallback extends RestCallback
{
	AutolockVehicles_App m_App = AutolockVehicles_App.GetInstance();

	override void OnError(int errorCode)
	{
		m_App.m_Logger.Log("RestCallback OnError, code " + errorCode.ToString());
	}

	override void OnTimeout()
	{
		m_App.m_Logger.Log("RestCallback OnTimeout");
	}

	override void OnSuccess(string data, int dataSize)
	{
		m_App.m_Logger.Log("RestCallback OnSuccess size=" + dataSize.ToString());
	}

	override void OnFileCreated(string fileName, int dataSize)
	{
		m_App.m_Logger.Log("RestCallback OnFileCreated, file=" + fileName + " size=" + dataSize.ToString());
	}
}