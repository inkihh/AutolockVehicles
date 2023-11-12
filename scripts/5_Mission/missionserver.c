modded class MissionServer extends MissionBase
{
    protected ref FOGAutolockVehicles_App m_App;

    override void OnInit()
    {
        super.OnInit();

        Print("[" + FOGAutolockVehicles_App.m_AppName + "] MissionServer.OnInit();");
		FOGAutolockVehicles_App m_App = FOGAutolockVehicles_App.GetInstance(); 
    }
}
