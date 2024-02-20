#ifdef LoggingTools_Server_Vehicles
#ifndef CARLOCKDISABLE
#ifdef CarLock
class FOGAutolockVehicles_Logger
{
    string m_LogFile;
    string m_AppName;

    void FOGAutolockVehicles_Logger(string AppName) {
        m_LogFile = "$profile:" + AppName + ".log";
        m_AppName = AppName;
    }

    void Log(string message)
    {
        FileHandle file = OpenFile(m_LogFile, FileMode.APPEND);

        if (file)
        {
            string timestamp = FOGAutolockVehicles_Helper.GetTimestamp();
            FPrintln(file, "[" + timestamp + "] " + message.Trim());
            CloseFile(file);
        }
        else
        {
            Print("[" + m_AppName + "] Could not create logfile " + m_LogFile);
        }
    }

    void DebugLog(string message)
    {
        if(!FOGAutolockVehicles_App.GetInstance().m_Settings.GetDoDebug())
            return;

        Log(message);
    }
}
#endif
#endif
#endif
