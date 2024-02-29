modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if(!player) return;

		CarScript car = player.m_AutolockVehicles_LastUnlockedVehicle;
		if(!car) return;

		if(!car.m_AutolockVehicles_LastPlayerUnlocked || player.GetID() != car.m_AutolockVehicles_LastPlayerUnlocked.GetID()) return;

		vector playerPosition = player.GetPosition();
		vector vehiclePosition = car.GetPosition();

		float distance = vector.Distance(playerPosition, vehiclePosition);

		int distanceBetweenOwnerAndVehicle = vector.Distance(playerPosition, vehiclePosition);
		bool wasProximityLocked = car.m_AutolockVehicles_WasProximityLocked;

		if(distanceBetweenOwnerAndVehicle > player.m_AutolockVehicles_proximity_lock_distance_meters && !wasProximityLocked)
		{
			car.m_AutolockVehicles_WasProximityLocked = true;
		   
			Print("[AutolockVehicles.MissionGameplay] Leaving proximity, locking");
			player.RPCSingleParam(AutolockVehicles_RPC.LOCK_PROXIMITY, null, true);
		}

		if(distanceBetweenOwnerAndVehicle < player.m_AutolockVehicles_proximity_unlock_distance_meters && wasProximityLocked)
		{
			car.m_AutolockVehicles_WasProximityLocked = false;
		   
			Print("[AutolockVehicles.MissionGameplay] Entering proximity, unlocking");
			player.RPCSingleParam(AutolockVehicles_RPC.UNLOCK_PROXIMITY, null, true);
		}
	}
}
