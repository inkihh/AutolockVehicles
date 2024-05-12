modded class MissionServer extends MissionBase
{
	protected ref AutolockVehicles_App m_AutolockVehicles_App;

	override void OnInit()
	{
		super.OnInit();

		Print("[AutolockVehicles] MissionServer.OnInit();");
		Print("[AutolockVehicles] If you're happy, please donate to https://paypal.me/ingmarheinrich <3");
		
		if(!m_AutolockVehicles_App) m_AutolockVehicles_App = AutolockVehicles_App.GetInstance(); 
	}
}
