modded class ActionStartEngine : ActionContinuousBaseCB
{
	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);

		if(!action_data.m_Player) return;
		if(!action_data.m_Target) return;
		if(!AutolockVehicles_App.GetInstance().m_Settings.enableProximityAutolock) return;
		
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if(!player) return;

		Object targetObject = action_data.m_Target.GetObject();
		if(!targetObject) return;

		CarScript car = CarScript.Cast(targetObject);
		if(!car) return;

		player.m_AutolockVehicles_CurrentUnlockedVehicle = car;

		string networkId = AutolockVehicles_Helper.GetNetworkID(car);

		Param2<string, int> carParam = new Param2<string, int>(networkId, AutolockVehicles_App.GetInstance().m_Settings.ProximityLock_DistanceMeters);
		GetGame().RPCSingleParam(player, AutolockVehicles_RPC.START_PROXIMITY, carParam, true, player.GetIdentity());
	}
}
