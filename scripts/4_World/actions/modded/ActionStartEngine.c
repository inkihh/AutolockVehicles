modded class ActionStartEngine : ActionContinuousBaseCB
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		AutolockVehicles_App.GetInstance().m_Logger.Log("[ActionStartEngine.OnFinishProgressServer] 1");

		if(!action_data.m_Player) return;
		if(!action_data.m_Target) return;

		AutolockVehicles_App.GetInstance().m_Logger.Log("[ActionStartEngine.OnFinishProgressServer] 2");

		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if(!player) return;

		AutolockVehicles_App.GetInstance().m_Logger.Log("[ActionStartEngine.OnFinishProgressServer] 3");

		Object targetObject = action_data.m_Target.GetObject();
		if(!targetObject) return;

		AutolockVehicles_App.GetInstance().m_Logger.Log("[ActionStartEngine.OnFinishProgressServer] 4");

		CarScript car = CarScript.Cast(targetObject);
		if(!car) return;

		player.m_AutolockVehicles_CurrentUnlockedVehicle = car;

		AutolockVehicles_App.GetInstance().m_Logger.Log("[ActionStartEngine.OnFinishProgressServer] Sending RPC");

		int lowBits;
		int highBits;
		car.GetNetworkID(lowBits, highBits );
		string networkId = lowBits.ToString() + highBits.ToString();

		Param2<string, int> carParam = new Param2<string, int>(networkId, AutolockVehicles_App.GetInstance().m_Settings.ProximityLock_DistanceMeters);
		GetGame().RPCSingleParam(player, AutolockVehicles_RPC.START_PROXIMITY, carParam, true, player.GetIdentity());
	}
}
