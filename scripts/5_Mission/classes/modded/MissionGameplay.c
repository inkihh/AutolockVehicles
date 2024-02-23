modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
        super.OnUpdate(timeslice);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if(!player) return;

        CarScript car = player.m_AutolockVehicles_CurrentUnlockedVehicle;
        if(!car) return;

        vector playerPosition = player.GetPosition();
        vector vehiclePosition = car.GetPosition();

		float distance = vector.Distance(playerPosition, vehiclePosition);

        int distanceBetweenOwnerAndVehicle = vector.Distance(playerPosition, vehiclePosition);
        bool wasProximityLocked = car.m_AutolockVehicles_WasProximityLocked;

        if(distanceBetweenOwnerAndVehicle > player.m_AutolockVehicles_ProximityLock_DistanceMeters && !wasProximityLocked)
        {
            car.m_AutolockVehicles_WasProximityLocked = true;
           
            Print("[AutolockVehicles.MissionGameplay] Leaving proximity, locking");
            player.RPCSingleParam(AutolockVehicles_RPC.LOCK_PROXIMITY, null, true);
        }

        if(distanceBetweenOwnerAndVehicle < player.m_AutolockVehicles_ProximityLock_DistanceMeters && wasProximityLocked)
        {
            player.m_AutolockVehicles_CurrentUnlockedVehicle.m_AutolockVehicles_WasProximityLocked = false;
            Print("[AutolockVehicles.MissionGameplay] Reentering proximity, enabling proximity watch");
        }
	}
}
