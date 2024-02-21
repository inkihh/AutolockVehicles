modded class MissionServer extends MissionBase
{
    protected ref AutolockVehicles_App m_AutolockVehicles_App;

    override void OnInit()
    {
        super.OnInit();

        Print("[" + AutolockVehicles_App.m_AppName + "] MissionServer.OnInit();");
		AutolockVehicles_App m_AutolockVehicles_App = AutolockVehicles_App.GetInstance(); 
    }
}
